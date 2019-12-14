#include "../ConsoleView.h"
#include "../Command.h"
#include "../CommandFactory.h"

#include "catch2/catch.hpp"

std::vector<std::string>
split2(const std::string& line)
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

void SendCommand2(std::string in)
{
	make_command(std::cout, split2(in))->execute();
}

TEST_CASE("Commands work")
{
	Model* holder2 = new Model;
	Command::setModelInstance(holder2);

	SendCommand2("help");
	SendCommand2("list");
	SendCommand2("help_for add_class");
	SendCommand2("help_for add_method");
	SendCommand2("help_for add_field");
	SendCommand2("add_class test1");
	SendCommand2("add_class test2");
	SendCommand2("add_class test3");
	SendCommand2("add_field test1 field1 int public");
	SendCommand2("add_field test2 field2 float private");
	SendCommand2("add_field test3 field3 double protected");
	SendCommand2("add_method test1 method1 int public");
	SendCommand2("add_method test2 method2 float private");
	SendCommand2("add_method test3 method3 double protected");
	SendCommand2("add_parameter test1 method1 param1 int");
	SendCommand2("add_parameter test2 method2 param2 float");
	SendCommand2("add_parameter test3 method3 param3 double");
	SendCommand2("add_relationship test1 test2 aggregation");
	SendCommand2("add_relationship test1 test3 composition");
	SendCommand2("add_relationship test2 test3 dependency");


	SECTION("Edit Class Command")
	{
		std::string editName("test4");
		SendCommand2("edit_class test1 test4");
		REQUIRE(holder2->findClass(editName) != nullptr);
	}

	SECTION("Delete Class Command")
	{
		std::string deleteName("test1");
		SendCommand2("delete_class test1");
		REQUIRE(holder2->findClass(deleteName) == nullptr);
	}

	SECTION("Delete Field Command")
	{
		std::string className("test1");
		std::string deleteField("test3");
		SendCommand2("delete_field test1 test3");
		REQUIRE(holder2->findField(className, deleteField) == nullptr);
	}

	SECTION("Delete Method Command")
	{
		std::string className("test1");
		std::string deleteMethod("test3");
		SendCommand2("delete_method test1 test3");
		REQUIRE(holder2->findMethod(className, deleteMethod) == nullptr);
	}

	SECTION("Delete Parameter")
	{
		std::string className("test1");
		std::string deleteParamName("test2");
		std::string methodName("test3");
		SendCommand2("delete_parameter test1 test3 test2");
		REQUIRE(holder2->findParameter(className, methodName, deleteParamName) == nullptr);
	}

	SECTION("DeleteRelationShip")
	{
		std::string classOne("test1");
		std::string classTwo("test2");
		SendCommand2("delete_relationship test1 test2");
		REQUIRE(holder2->findRelationship(classOne, classTwo) == nullptr);
	}

	SECTION("Edit Field")
	{
		std::string className("test1");
		std::string editName("test2");
		std::string fieldName("test3");
		std::string attr("test4");
		SendCommand2("edit_field test4 test1 test3 test2");
		REQUIRE(holder2->findField(className, editName) == nullptr);
	}

	SECTION("Edit Method")
	{
		std::string className("test1");
		std::string editName("test2");
		std::string methodName("test3");
		std::string attr("test4");
		SendCommand2("edit_method test4 test1 test3 test2");
		REQUIRE(holder2->findMethod(className, editName) == nullptr);
	}

	SECTION("Edit Parameter")
	{
		std::string attr("test1");
		std::string className("test2");
		std::string methodName("test3");
		std::string paramName("test4");
		std::string editName("test5");
		SendCommand2("edit_parameter test1 test2 test3 test4 test5");
		REQUIRE(holder2->findParameter(className, methodName, editName) == nullptr);
	}

	SECTION("Edit Relationship")
	{
		std::string classOne("test1");
		std::string classTwo("test2");
		std::string newType("test3");
		SendCommand2("edit_relationship test1 test2 test3");
		REQUIRE(holder2->findRelationship(classOne, classTwo) != nullptr);
	}
}