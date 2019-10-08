#define CATCH_CONFIG_MAIN
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
		REQUIRE(holder->UMLObjectReturnTitles()[0] == "Car");
	}
}

TEST_CASE("Edit a class", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();
	UMLObject* a = holder->CreateNewClass("Car");
	SECTION("Class Constructor", "0")
	{
		REQUIRE(holder->UMLObjectReturnTitles()[0] == "Car");
	}

	holder->EditClassTitle("Vehicle", "Car");

	SECTION("Class Rename", "0")
	{
		REQUIRE(holder->UMLObjectReturnTitles()[0] == "Vehicle");
	}

	UMLObject* b = holder->CreateNewClass("Vehicle");

	SECTION("Class Creation Duplicate", "0")
	{
		REQUIRE(b == NULL);
		REQUIRE(holder->Size() == 1);
	}

}


TEST_CASE("Add multiple classes", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	UMLObject* c = holder->CreateNewClass("Vehicle");
	UMLObject* a = holder->CreateNewClass("Tire");

	SECTION("Class Multiples", "0")
	{
		REQUIRE(a != NULL);
		REQUIRE(c != NULL);
		REQUIRE(holder->Size() == 2);
		REQUIRE(holder->UMLObjectReturnTitles()[0] == "Vehicle");
		REQUIRE(holder->UMLObjectReturnTitles()[1] == "Tire");
	}
}

TEST_CASE("Add relationship between classes", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	UMLObject* c = holder->CreateNewClass("Vehicle");
	UMLObject* a = holder->CreateNewClass("Tire");

	SECTION("Create classes", "0")
	{
		REQUIRE(holder->Size() == 2);
		REQUIRE(holder->UMLObjectReturnTitles()[0] == "Vehicle");
		REQUIRE(holder->UMLObjectReturnTitles()[1] == "Tire");
	}

	holder->AddRelationship("Vehicle", "Tire", RelationshipComposition);

	SECTION("Verify relationship", "0")
	{
		REQUIRE(holder->ReturnPtrToVector()[0]->ReturnRelationships() == "{ type: 6, object: Tire, parent: 1}, ");
		REQUIRE(holder->ReturnPtrToVector()[1]->ReturnRelationships() == "{ type: 6, object: Vehicle, parent: 0}, ");
	}

}