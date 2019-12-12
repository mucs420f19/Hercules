#include "../Class.h"

#include "catch2/catch.hpp"

TEST_CASE("Classes work")
{
	std::string newName("newName");
	std::string name("test");
	Class a(name);
	REQUIRE(a.name() == name);
	bool equal = false;

	SECTION("Classes can have names changed")
	{
		a.rename(newName);
		REQUIRE(a.name() == newName);
	}

	SECTION("Classes rawNames work")
	{
		if (strcmp(a.rawName(), name.c_str()) == 0)
		{
			equal = true;
		}
		REQUIRE(equal == true);
	}
}
