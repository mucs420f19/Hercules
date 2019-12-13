#include "../Command.h"

#include "catch2/catch.hpp"

TEST_CASE("Commands work")
{
	Model * test = new Model;
	Command::setModelInstance(test);
	SECTION("Add Class Command")
	{
		std::string Name("Name");
		std::make_unique<AddClassCommand>("Name");
		REQUIRE(modelInstance->findClass(Name) != nullptr);
	}

	SECTION("Attribute can have name change")
	{
	}
}