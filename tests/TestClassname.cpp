#include "../Class.h"

#include "catch2/catch.hpp"

TEST_CASE("Classes work")
{
	std::string name("test");
	Class a(name);
	REQUIRE(a.name() == name);

	SECTION("Classes can have names changed")
	{
		std::string newName("newName");
		a.rename(newName);
		REQUIRE(a.name() == newName);
	}
}
