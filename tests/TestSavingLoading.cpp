#include "../ConsoleView.h"
#include "../Command.h"
#include "../CommandFactory.h"

#include "catch2/catch.hpp"

std::vector<std::string>
split(const std::string& line)
{

	std::vector<std::string> tokenized;
	const char* WS = "\t ";
	auto wordStart = line.find_first_not_of(WS);
	while (wordStart != std::string::npos)
	{
		auto wordEnd = line.find_first_of(WS, wordStart);
		if (wordEnd == std::string::npos)
		{
			wordEnd = line.size();
		}
		tokenized.emplace_back(line.begin() + wordStart, line.begin() + wordEnd);
		wordStart = line.find_first_not_of(WS, wordEnd);
	}
	return tokenized;
}

void SendCommand(std::string in)
{
	make_command(std::cout, split(in))->execute();
}

TEST_CASE("Test Saving Loading All Items", "0")
{
	Model* holder = new Model;
	Command::setModelInstance(holder);

	//create some stuff in the model
	SendCommand("add_class test1");
	SendCommand("add_class test2");
	SendCommand("add_class test3");
	SendCommand("add_field test1 field1 int public");
	SendCommand("add_field test2 field2 float private");
	SendCommand("add_field test3 field3 double protected");
	SendCommand("add_method test1 method1 int public");
	SendCommand("add_method test2 method2 float private");
	SendCommand("add_method test3 method3 double protected");
	SendCommand("add_parameter test1 method1 param1 int");
	SendCommand("add_parameter test2 method2 param2 float");
	SendCommand("add_parameter test3 method3 param3 double");
	SendCommand("add_relationship test1 test2 aggregation");
	SendCommand("add_relationship test1 test3 composition");
	SendCommand("add_relationship test2 test3 dependency");
	//SendCommand("list");
	
	//save it
	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "tempfile.txt", true) == SaveSuccess);

	//load it in a different model
	Model* holder2 = new Model;
	Command::setModelInstance(holder2);
	REQUIRE(SavingLoadingIO::LoadProject(holder2, "tempfile.txt") == true);

	//compare them
	const std::list<Class> * class_list1 = holder->ReturnClasses();
	const std::list<Class> * class_list2 = holder2->ReturnClasses();
	REQUIRE(class_list1->size() == 3);
	REQUIRE(class_list2->size() == 3);

	const std::list<Relationship>* relationship_list1 = holder->ReturnRelationships();
	const std::list<Relationship>* relationship_list2 = holder2->ReturnRelationships();
	REQUIRE(relationship_list1->size() == 3);
	REQUIRE(relationship_list2->size() == 3);


	//save the second model
	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder2, "tempfile2.txt", true) == SaveSuccess);


	//compare the save files
	std::ifstream in("tempfile.txt");

	//gather the lines from both files
	std::string line;
	std::vector<std::string> lines1, lines2;
	while (std::getline(in, line))
	{
		lines1.push_back(line);
	}
	in.close();


	std::ifstream in2("tempfile2.txt");

	while (std::getline(in2, line))
	{
		lines2.push_back(line);
	}
	in2.close();

	SECTION("Verify Identical files", "0")
	{
		REQUIRE(lines1.size() != 0);
		REQUIRE(lines1.size() == lines2.size());
		for (size_t i = 0; i < lines1.size(); i++)
		{
			REQUIRE(lines1[i] == lines2[i]);
		}
	}

	delete holder;
	delete holder2;
}

TEST_CASE("Test Saving Overwriting", "0")
{
	Model* holder = new Model;

	//save a file
	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "do_not_overwrite_me.txt", true) == SaveSuccess);

	//load it
	REQUIRE(SavingLoadingIO::LoadProject(holder, "do_not_overwrite_me.txt") == true);

	//try to save it again, without overwrite
	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "do_not_overwrite_me.txt") == SaveAlreadyExists);

	//save it again with overwrite
	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "do_not_overwrite_me.txt", true) == SaveSuccess);

	delete holder;
}

TEST_CASE("Test Invalid Loading", "0")
{

	std::string randfilename = "does_not_exist";
	srand((unsigned int)time(0));
	for (size_t i = 0; i < 10; i++)
	{
		randfilename += std::to_string(rand() % 10);
	}
	randfilename += ".txt";

	Model* holder = new Model;

	//load file that should not exist
	REQUIRE(SavingLoadingIO::LoadProject(holder, randfilename) == false);

	//save it
	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, randfilename, true) == SaveSuccess);

	//load should succeed now
	REQUIRE(SavingLoadingIO::LoadProject(holder, randfilename) == true);

	delete holder;
}

TEST_CASE("Test Invalid Saving", "0")
{
	Model* holder = new Model;

	//verify that file cannot be opened if it has no name
	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "", false) == SaveError);

	//should still fail, even if we want to overwrite
	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "", true) == SaveError);

	delete holder;
}