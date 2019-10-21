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

		REQUIRE(c[0]->ReturnRelationships() == "{{}}Type: 6, Parent of: Tire}, }");
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

TEST_CASE("REPL Test 1", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	RunREPL(holder, "add class test_class1");
	REQUIRE(holder->Size() == 1);
	REQUIRE(holder->GetUMLObject("test_class1") != NULL);

	RunREPL(holder, "edit class test_class1 new_class_name");

	REQUIRE(holder->ReturnPtrToVector()[0]->ReturnTitle() == "new_class_name");

	//write more here
}

TEST_CASE("REPL Test 2", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	//write more here
}

TEST_CASE("")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();
}

//
//void RunUnitTest1()
//{
//	std::cout << "---------------\nRunning test 1...---------------\n\n\n\n";
//
//
//	UMLObjectsHolder* holder = new UMLObjectsHolder();
//
//	std::cout << "Creating example UMLObjects...\n\n\n";
//
//	std::string before1 = "empty string", before2 = "empty string", after1, after2;
//	UMLObject* a = NULL, * b = NULL;
//
//	if (holder->CreateNewClass("Car"))
//	{
//		std::cout << "Successfully created class" << std::endl;
//
//		a = holder->ReturnPtrToVector()[0];
//
//		std::vector<std::string> testVec;
//
//		a->AddField(UMLField("Color", "string", UMLFieldVisibilityPublic));
//		a->AddField(UMLField("Make", "string", UMLFieldVisibilityPublic));
//		a->AddMethod(UMLMethod("Drive()", "void", testVec, UMLFieldVisibilityPrivate));
//		std::cout << a->ToString() << std::endl << std::endl;
//		before1 = a->ToString();
//
//	}
//	else
//	{
//		std::cout << "Unable to create class due to duplicate name" << std::endl;
//	}
//
//	if (holder->CreateNewClass("Wheel"))
//	{
//		std::cout << "Successfully created class" << std::endl;
//
//		b = holder->ReturnPtrToVector()[1];
//
//		std::vector<std::string> testVec;
//		testVec.push_back("Dummy param 1");
//		testVec.push_back("Dummy param 2");
//
//		b->AddField(UMLField("Manufacturer", "string", UMLFieldVisibilityPublic));
//		b->AddField(UMLField("Diameter", "unsigned int", UMLFieldVisibilityPublic));
//		b->AddMethod(UMLMethod("Rotate()", "unsigned int", testVec, UMLFieldVisibilityPrivate));
//		std::cout << b->ToString() << std::endl << std::endl;
//		before2 = b->ToString();
//
//	}
//	else
//	{
//		std::cout << "Unable to create class due to duplicate name" << std::endl;
//	}
//
//	std::cout << "Saving and destroying these UMLObjects...\n\n\n";
//
//	//save them to file
//	SavingLoadingIO::SaveProjectToFile(holder);
//
//	//destory them out of memory
//	delete holder;
//
//	std::cout << "Reloading UMLObjects...\n\n\n";
//
//	//load them into memory again
//	holder = new UMLObjectsHolder();
//
//	if (SavingLoadingIO::LoadProject(holder))
//	{
//		std::cout << "Load successful" << std::endl;
//	}
//	else
//	{
//		std::cout << "Unable to load" << std::endl;
//	}
//
//
//
//	std::cout << "Comparing UMLObjects before and after...\n\n\n";
//
//	if (a != NULL)
//	{
//		a = holder->ReturnPtrToVector()[0];
//		std::cout << a->ToString() << std::endl << std::endl;
//		after1 = a->ToString();
//	}
//
//	if (b != NULL)
//	{
//		b = holder->ReturnPtrToVector()[1];
//		std::cout << b->ToString() << std::endl << std::endl;
//		after2 = b->ToString();
//	}
//
//	if (before1 == after1)
//	{
//		std::cout << "UMLObject1 is correct" << std::endl;
//	}
//	else std::cout << "UMLObject1 is not correct" << std::endl;
//
//	if (before2 == after2)
//	{
//		std::cout << "UMLObject2 is correct" << std::endl;
//	}
//	else std::cout << "UMLObject2 is not correct" << std::endl;
//
//	std::cout << "---------------\nTest 1 completed...---------------\n\n\n\n";
//
//}
//
//void RunUnitTest2()
//{
//	std::cout << "---------------\nRunning test 2...\n---------------\n\n\n\n";
//
//	UMLObjectsHolder* holder = new UMLObjectsHolder();
//
//
//	UMLObject* a = NULL, * b = NULL;
//
//	if (holder->CreateNewClass("Car"))
//	{
//		std::cout << "Successfully created class" << std::endl;
//
//		a = holder->ReturnPtrToVector()[0];
//
//		std::vector<std::string> testVec;
//
//		a->AddField(UMLField("Color", "string", UMLFieldVisibilityPublic));
//		a->AddField(UMLField("Make", "string", UMLFieldVisibilityPublic));
//		a->AddMethod(UMLMethod("Drive()", "void", testVec, UMLFieldVisibilityPrivate));
//		std::cout << a->ToString() << std::endl << std::endl;
//
//	}
//	else
//	{
//		std::cout << "Unable to create class due to duplicate name" << std::endl;
//	}
//
//	if (holder->CreateNewClass("Wheel"))
//	{
//		std::cout << "Successfully created class" << std::endl;
//
//		b = holder->ReturnPtrToVector()[1];
//
//		std::vector<std::string> testVec;
//		testVec.push_back("Dummy param 1");
//		testVec.push_back("Dummy param 2");
//
//		b->AddField(UMLField("Manufacturer", "string", UMLFieldVisibilityPublic));
//		b->AddField(UMLField("Diameter", "unsigned int", UMLFieldVisibilityPublic));
//		b->AddMethod(UMLMethod("Rotate()", "unsigned int", testVec, UMLFieldVisibilityPrivate));
//		std::cout << b->ToString() << std::endl << std::endl;
//
//	}
//	else
//	{
//		std::cout << "Unable to create class due to duplicate name" << std::endl;
//	}
//
//
//	if (b != NULL)
//	{
//		if (holder->EditClassTitle("Car", "Wheel"))
//		{
//			std::cout << "Rename succeeded.... this should not have worked!\n\n\n";
//			std::cout << "TEST 2 FAILED\n\n\n";
//		}
//		else
//		{
//			std::cout << "Unable to rename \"Wheel\" to \"Car\", class name already exists\n\n\n";
//		}
//
//		std::cout << b->ToString() << std::endl << std::endl;
//
//
//		if (holder->EditClassTitle("Tire", "Wheel"))
//		{
//			std::cout << "Rename succeeded....\n\n\n";
//		}
//		else
//		{
//			std::cout << "Unable to rename \"Wheel\" to \"Tire\", class name already exists\n\n\n";
//			std::cout << "TEST 2 FAILED\n\n\n";
//		}
//
//		std::cout << b->ToString() << std::endl << std::endl;
//	}
//	else
//	{
//		std::cout << "TEST 2 FAILED\n\n\n";
//
//	}
//
//
//	std::cout << "---------------\nTest 2 completed...\n---------------\n\n\n\n";
//}
//
//
//void RunUnitTest3()
//{
//	std::cout << "---------------\nRunning test 3...\n---------------\n\n\n\n";
//
//
//	UMLObject* a = NULL, * b = NULL;
//	UMLObjectsHolder* holder = new UMLObjectsHolder();
//
//	a = holder->CreateNewClass("Car");
//	b = holder->CreateNewClass("Wheel");
//
//	holder->AddRelationship("Car", "Wheel", RelationshipAggregation);
//
//	std::cout << a->ReturnRelationships() << std::endl;
//	std::cout << b->ReturnRelationships() << std::endl;
//
//	holder->EditRelationship("Car", "Wheel", RelationshipComposition);
//	std::cout << a->ReturnRelationships() << std::endl;
//	std::cout << b->ReturnRelationships() << std::endl;
//
//	holder->DeleteRelationship("Car", "Wheel");
//	std::cout << a->ReturnRelationships() << std::endl;
//	std::cout << b->ReturnRelationships() << std::endl;
//
//}
