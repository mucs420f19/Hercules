#include "../ConsoleView.h"
#include "../Command.h"
#include "../CommandFactory.h"

#include "catch2/catch.hpp"

void SendCommand(std::string in)
{
	make_command(std::cout, split(in))->execute();
}

TEST_CASE("Commands work")
{
	Model* holder = new Model;
	Command::setModelInstance(holder);

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

	SECTION("Edit Class Command")
	{
		std::string editName("test4");
		SendCommand("edit_class test1 test4");
		REQUIRE(holder->findClass(editName) != nullptr);
	}

	SECTION("Delete Class Command")
	{
		std::string deleteName("test1");
		SendCommand("delete_class test1");
		REQUIRE(holder->findClass(deleteName) == nullptr);
	}
}