#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h"
#include "REPL.h"

TEST_CASE("Create a Class", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();
	holder->CreateNewClass("Car");
	UMLObject* a = NULL;
	a = holder->ReturnPtrToVector()[0];
	SECTION("Class Constructor", "0")
	{
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Car");
	}
}

TEST_CASE("Edit a class", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();
	UMLObject* a = holder->CreateNewClass("Car");
	SECTION("Class Constructor", "0")
	{
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Car");
	}

	holder->EditClassTitle("Vehicle", "Car");

	SECTION("Class Rename", "0")
	{
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Vehicle");
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
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Vehicle");
		REQUIRE(holder->UMLObjectReturnTitlesString()[1] == "Tire");
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
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Vehicle");
		REQUIRE(holder->UMLObjectReturnTitlesString()[1] == "Tire");
	}

	holder->AddRelationship("Vehicle", "Tire", RelationshipComposition);

	SECTION("Verify relationship", "0")
	{
		REQUIRE(holder->ReturnPtrToVector()[0]->ReturnRelationships() == "{{Type: 6, Parent of: Tire}, }");
		REQUIRE(holder->ReturnPtrToVector()[1]->ReturnRelationships() == "{{Type: 6, Child of: Vehicle}, }");
	}

}

TEST_CASE("Test Saving Loading All Items", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();
	UMLObject* a = NULL, * b = NULL;

	if (holder->CreateNewClass("Car"))
	{
		a = holder->ReturnPtrToVector()[0];
		std::vector<UMLParameter> testVec;
		a->AddField(UMLField("Color", "string", UMLFieldVisibilityPublic));
		a->AddField(UMLField("Make", "string", UMLFieldVisibilityPublic));
		a->AddMethod(UMLMethod("Drive()", "void", testVec, UMLFieldVisibilityPrivate));
	}

	if (holder->CreateNewClass("Wheel"))
	{
		b = holder->ReturnPtrToVector()[1];
		std::vector<UMLParameter> testVec;
		testVec.push_back(UMLParameter("int", "Dummy param 1"));
		testVec.push_back(UMLParameter("float", "Dummy param 2", "true", "0.0f"));
		b->AddField(UMLField("Manufacturer", "string", UMLFieldVisibilityPublic));
		b->AddField(UMLField("Diameter", "unsigned int", UMLFieldVisibilityPublic));
		b->AddMethod(UMLMethod("Rotate()", "unsigned int", testVec, UMLFieldVisibilityPrivate));
	}

	holder->EditClassTitle("Tire", "Wheel");
	holder->AddRelationship("Car", "Tire", RelationshipComposition);


	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "tempfile.txt", true) == SaveSuccess);
	
	UMLObjectsHolder* holder2 = new UMLObjectsHolder();

	REQUIRE(SavingLoadingIO::LoadProject(holder2, "tempfile.txt") == true);

	std::vector<UMLObject*> c, d;
	c = holder->ReturnPtrToVector();
	d = holder2->ReturnPtrToVector();

	SECTION("Verify Save Contents", "0")
	{
		REQUIRE(c.size() == d.size());
		REQUIRE(c[0]->ReturnTitle() == "Car");
		REQUIRE(c[0]->ReturnTitle() == d[0]->ReturnTitle());


		REQUIRE(c[0]->ReturnMethods() == "{{Drive(), void, {}, Private}, }");
		REQUIRE(c[0]->ReturnMethods() == d[0]->ReturnMethods());


		REQUIRE(c[0]->ReturnFields() == "{{Color, string, Public}, {Make, string, Public}, }");
		REQUIRE(c[0]->ReturnFields() == d[0]->ReturnFields());

		REQUIRE(c[0]->ReturnRelationships() == "{{Type: 6, Parent of: Tire}, }");
		REQUIRE(c[0]->ReturnRelationships() == d[0]->ReturnRelationships());
	   
		REQUIRE(c[1]->ReturnTitle() == "Tire");
		REQUIRE(c[1]->ReturnTitle() == d[1]->ReturnTitle());


		REQUIRE(c[1]->ReturnMethods() == "{{Rotate(), unsigned int, {int Dummy param 1, float Dummy param 2 = 0.0f, }, Private}, }");
		REQUIRE(c[1]->ReturnMethods() == d[1]->ReturnMethods());


		REQUIRE(c[1]->ReturnFields() == "{{Manufacturer, string, Public}, {Diameter, unsigned int, Public}, }");
		REQUIRE(c[1]->ReturnFields() == d[1]->ReturnFields());
		
		REQUIRE(c[1]->ReturnRelationships() == "{{Type: 6, Child of: Car}, }");
		REQUIRE(c[1]->ReturnRelationships() == d[1]->ReturnRelationships());

	}

	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder2, "tempfile2.txt", true) == SaveSuccess);

	std::ifstream in("tempfile.txt");

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

}

TEST_CASE("Test Saving Overwriting", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "do_not_overwrite_me.txt", true) == SaveSuccess);

	REQUIRE(SavingLoadingIO::LoadProject(holder, "do_not_overwrite_me.txt") == true);

	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "do_not_overwrite_me.txt") == SaveAlreadyExists);

	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, "do_not_overwrite_me.txt", true) == SaveSuccess);

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

	UMLObjectsHolder* holder = new UMLObjectsHolder();

	REQUIRE(SavingLoadingIO::LoadProject(holder, randfilename) == false);

	REQUIRE(SavingLoadingIO::SaveProjectToFile(holder, randfilename, true) == SaveSuccess);

	REQUIRE(SavingLoadingIO::LoadProject(holder, randfilename) == true);
}

TEST_CASE("Test Terminal Class Functionality", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	RunREPL(holder, "add class test_class1");
	REQUIRE(holder->Size() == 1);
	REQUIRE(holder->GetUMLObject("test_class1") != NULL);

	RunREPL(holder, "edit class test_class1 new_class_name");

	REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "new_class_name");

	RunREPL(holder, "edit class new_class_name test_class1");

    RunREPL(holder, "add class test_class2");
    RunREPL(holder, "add class test_class3");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "add class a b");
    REQUIRE(holder->Size() == 3);

    RunREPL(holder, "add class");
    REQUIRE(holder->Size() == 3);

    RunREPL(holder, "add class test_class2");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "edit class");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "edit class a b");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "edit class test_class1");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "edit class test_class4 test_classA");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "delete class test_class4");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "delete class");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "delete class test_class1 a");
    REQUIRE(holder->Size() == 3);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class2");
    REQUIRE(holder->ReturnPtrToVector()[2]->ReturnTitle() == "test_class3");

    RunREPL(holder, "delete class test_class2");
    REQUIRE(holder->Size() == 2);
    REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "test_class1");
    REQUIRE(holder->ReturnPtrToVector()[1]->ReturnTitle() == "test_class3");
}

TEST_CASE("Test Terminal Method & Field Functionality", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	RunREPL(holder, "add class test_class1");
	RunREPL(holder, "add method test_class1 test_method1");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, , {}, Private}, }");

	RunREPL(holder, "add method test_class1 test_method2");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, , {}, Private}, {test_method2, , {}, Private}, }");

	RunREPL(holder, "add method test_class2 test_method3");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, , {}, Private}, {test_method2, , {}, Private}, }");

	RunREPL(holder, "add method test_class1");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_method1, , {}, Private}, {test_method2, , {}, Private}, }");
	
	RunREPL(holder, "add method test_class2");
	REQUIRE(holder->GetUMLObject("test_class2") == 0);

	RunREPL(holder, "add method test_class2 newMethod");
	REQUIRE(holder->GetUMLObject("test_class2") == 0);

	RunREPL(holder, "edit method test_class1 test_method1 test_methodA");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, , {}, Private}, {test_method2, , {}, Private}, }");

	RunREPL(holder, "edit method test_class1");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, , {}, Private}, {test_method2, , {}, Private}, }");

	RunREPL(holder, "edit method test_class1 test_methodA");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, , {}, Private}, {test_method2, , {}, Private}, }");

	RunREPL(holder, "delete method test_class1 test_method2");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, , {}, Private}, }");

	RunREPL(holder, "delete method test_class1");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnMethods() == "{{test_methodA, , {}, Private}, }");

	// ===

	RunREPL(holder, "add field test_class1 test_field1");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, , Private}, }");

	RunREPL(holder, "add field test_class1 test_field2");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, , Private}, {test_field2, , Private}, }");

	RunREPL(holder, "add field test_class2 test_field3");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, , Private}, {test_field2, , Private}, }");

	RunREPL(holder, "add field test_class1");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_field1, , Private}, {test_field2, , Private}, }");
	
	RunREPL(holder, "add field test_class2");
	REQUIRE(holder->GetUMLObject("test_class2") == 0);

	RunREPL(holder, "add field test_class2 newField");
	REQUIRE(holder->GetUMLObject("test_class2") == 0);

	RunREPL(holder, "edit field test_class1 test_field1 test_fieldA");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, , Private}, {test_field2, , Private}, }");

	RunREPL(holder, "edit field test_class1");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, , Private}, {test_field2, , Private}, }");

	RunREPL(holder, "edit field test_class1 test_fieldA");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, , Private}, {test_field2, , Private}, }");

	RunREPL(holder, "delete field test_class1 test_field2");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, , Private}, }");

	RunREPL(holder, "delete field test_class1");
	REQUIRE(holder->GetUMLObject("test_class1")->ReturnFields() == "{{test_fieldA, , Private}, }");
}