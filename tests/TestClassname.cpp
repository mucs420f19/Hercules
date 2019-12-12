#include "../Class.h"

#include "catch2/catch.hpp"

TEST_CASE("Classes work")
{
	std::string newName("newName");
	std::string name("test");
	Class a(name);
	REQUIRE(a.name() == name);

	SECTION("Classes can have names changed")
	{
		a.rename(newName);
		REQUIRE(a.name() == newName);
	}

	SECTION("Classes rawNames work")
	{
		REQUIRE(strcmp(a.rawName(), name.c_str() == 0);
	}
}
