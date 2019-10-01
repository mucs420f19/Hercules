#define CATCH_CONFIG_RUNNER
#include "Catch2.hpp"

#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h" 

TEST_CASE("Create a Class", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();
	holder->CreateNewClass("Car");
	UMLObject* a = NULL;
	a = holder->ReturnPtrToVector()[0];
	SECTION("Class Constructor", "0")
	{
		REQUIRE(holder->UMLObjectReturnTitles() == "Car");
	}
}