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

	holder->AddRelationship("Vehicle", "Tire", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany);

	SECTION("Verify relationship", "0")
	{
		REQUIRE(holder->ReturnPtrToVector()[0]->ReturnRelationships() == "{{Vehicle is Parent in relationship Composition One-to-Many with Tire}, }");
		REQUIRE(holder->ReturnPtrToVector()[1]->ReturnRelationships() == "{{Tire is Child in relationship Composition Many-to-One with Vehicle}, }");
	}

}

TEST_CASE("Relationships functionality test multiple relationships on item", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	holder->CreateNewClass("Vehicle");

	for (unsigned int i = 0; i < 4; i++)
	{
		holder->CreateNewClass("Door" + std::to_string(i + 1));
		holder->AddRelationship("Vehicle", "Door" + std::to_string(i + 1), RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany);

		holder->CreateNewClass("Tire" + std::to_string(i + 1));
		holder->AddRelationship("Vehicle", "Tire" + std::to_string(i + 1), RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany);
	}

	SECTION("Create classes", "0")
	{
		REQUIRE(holder->Size() == 9);
		REQUIRE(holder->UMLObjectReturnTitlesString()[0] == "Vehicle");
		for (unsigned int i = 0; i < 4; i++)
		{
			REQUIRE(holder->UMLObjectReturnTitlesString()[1+(i*2)] == "Door" + std::to_string(i + 1));
			REQUIRE(holder->UMLObjectReturnTitlesString()[2 + (i*2)] == "Tire" + std::to_string(i + 1));
		}
	}

	SECTION("Verify relationship", "0")
	{
		REQUIRE(holder->ReturnPtrToVector()[0]->ReturnRelationships() ==   "{{Vehicle is Parent in relationship Composition One-to-Many with Door1}, {Vehicle is Parent in relationship Composition One-to-Many with Tire1}, {Vehicle is Parent in relationship Composition One-to-Many with Door2}, {Vehicle is Parent in relationship Composition One-to-Many with Tire2}, {Vehicle is Parent in relationship Composition One-to-Many with Door3}, {Vehicle is Parent in relationship Composition One-to-Many with Tire3}, {Vehicle is Parent in relationship Composition One-to-Many with Door4}, {Vehicle is Parent in relationship Composition One-to-Many with Tire4}, }");
		for (unsigned int i = 0; i < 4; i++)
		{
			REQUIRE(holder->ReturnPtrToVector()[1 + (i * 2)]->ReturnRelationships() == "{{Door" + std::to_string(i + 1) + " is Child in relationship Composition Many-to-One with Vehicle}, }");
			REQUIRE(holder->ReturnPtrToVector()[2 + (i * 2)]->ReturnRelationships() == "{{Tire" + std::to_string(i + 1) + " is Child in relationship Composition Many-to-One with Vehicle}, }");
		}
	}

}

TEST_CASE("Relationships edit functionality test", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	UMLObject* c = holder->CreateNewClass("Vehicle");
	UMLObject* a = holder->CreateNewClass("Tire");
	UMLObject* d = holder->CreateNewClass("Door");
	UMLObject* e = holder->CreateNewClass("Light");
	UMLObject* f = holder->CreateNewClass("Cylinders");
	UMLObject* g = holder->CreateNewClass("Engine");
	UMLObject* h = holder->CreateNewClass("Fleet");
	UMLObject* i = holder->CreateNewClass("Driver");

	//every one of these must succeed
	REQUIRE((
		holder->AddRelationship("Vehicle", "Tire", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany) &&
		holder->AddRelationship("Vehicle", "Door", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany) &&
		holder->AddRelationship("Vehicle", "Light", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany) &&
		holder->AddRelationship("Vehicle", "Engine", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierOne) &&
		holder->AddRelationship("Engine", "Cylinders", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany) &&
		holder->AddRelationship("Fleet", "Vehicle", RelationshipAggregation, RelationshipQuantifierMany, RelationshipQuantifierMany) &&
		holder->AddRelationship("Driver", "Vehicle", RelationshipRealization, RelationshipQuantifierOne, RelationshipQuantifierOne)
	));

	SECTION("Verify relationship", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle")->ReturnRelationships() == "{{Vehicle is Parent in relationship Composition One-to-Many with Tire}, {Vehicle is Parent in relationship Composition One-to-Many with Door}, {Vehicle is Parent in relationship Composition One-to-Many with Light}, {Vehicle is Parent in relationship Composition One-to-One with Engine}, {Vehicle is Child in relationship Aggregation Many-to-Many with Fleet}, {Vehicle is Child in relationship Realization One-to-One with Driver}, }");

		REQUIRE(holder->GetUMLObject("Tire")->ReturnRelationships() == "{{Tire is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Door")->ReturnRelationships() == "{{Door is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Light")->ReturnRelationships() == "{{Light is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Engine")->ReturnRelationships() == "{{Engine is Child in relationship Composition One-to-One with Vehicle}, {Engine is Parent in relationship Composition One-to-Many with Cylinders}, }");
		REQUIRE(holder->GetUMLObject("Cylinders")->ReturnRelationships() == "{{Cylinders is Child in relationship Composition Many-to-One with Engine}, }");
		REQUIRE(holder->GetUMLObject("Fleet")->ReturnRelationships() == "{{Fleet is Parent in relationship Aggregation Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Driver")->ReturnRelationships() == "{{Driver is Parent in relationship Realization One-to-One with Vehicle}, }");
	}

	//these values might not make sense in the real world, they are just for the purpose of the test
	REQUIRE((
		holder->EditRelationship("Vehicle", "Tire", RelationshipGeneralization, RelationshipQuantifierMany, RelationshipQuantifierMany) &&
		holder->EditRelationship("Door", "Vehicle", RelationshipRealization, RelationshipQuantifierMany, RelationshipQuantifierMany) &&
		holder->EditRelationship("Vehicle", "Light", RelationshipRealization, RelationshipQuantifierMany, RelationshipQuantifierMany) &&
		holder->EditRelationship("Cylinders", "Engine", RelationshipRealization, RelationshipQuantifierMany, RelationshipQuantifierMany) &&
		holder->EditRelationship("Fleet", "Vehicle", RelationshipRealization, RelationshipQuantifierOne, RelationshipQuantifierOne) &&
		holder->EditRelationship("Vehicle", "Driver", RelationshipGeneralization, RelationshipQuantifierMany, RelationshipQuantifierMany)
		));

	SECTION("Verify relationships after edit", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle")->ReturnRelationships() == "{{Vehicle is Parent in relationship Generalization Many-to-Many with Tire}, {Vehicle is Parent in relationship Realization Many-to-Many with Door}, {Vehicle is Parent in relationship Realization Many-to-Many with Light}, {Vehicle is Parent in relationship Composition One-to-One with Engine}, {Vehicle is Child in relationship Realization One-to-One with Fleet}, {Vehicle is Child in relationship Generalization Many-to-Many with Driver}, }");

		REQUIRE(holder->GetUMLObject("Tire")->ReturnRelationships() == "{{Tire is Child in relationship Generalization Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Door")->ReturnRelationships() == "{{Door is Child in relationship Realization Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Light")->ReturnRelationships() == "{{Light is Child in relationship Realization Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Engine")->ReturnRelationships() == "{{Engine is Child in relationship Composition One-to-One with Vehicle}, {Engine is Parent in relationship Realization Many-to-Many with Cylinders}, }");
		REQUIRE(holder->GetUMLObject("Cylinders")->ReturnRelationships() == "{{Cylinders is Child in relationship Realization Many-to-Many with Engine}, }");
		REQUIRE(holder->GetUMLObject("Fleet")->ReturnRelationships() == "{{Fleet is Parent in relationship Realization One-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Driver")->ReturnRelationships() == "{{Driver is Parent in relationship Generalization Many-to-Many with Vehicle}, }");
	}

	holder->DeleteRelationship("Light", "Vehicle");
	holder->DeleteRelationship("Vehicle", "Engine");

	SECTION("Verify relationships after relationship deletion", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle")->ReturnRelationships() == "{{Vehicle is Parent in relationship Generalization Many-to-Many with Tire}, {Vehicle is Parent in relationship Realization Many-to-Many with Door}, {Vehicle is Child in relationship Realization One-to-One with Fleet}, {Vehicle is Child in relationship Generalization Many-to-Many with Driver}, }");

		REQUIRE(holder->GetUMLObject("Tire")->ReturnRelationships() == "{{Tire is Child in relationship Generalization Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Door")->ReturnRelationships() == "{{Door is Child in relationship Realization Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Light")->ReturnRelationships() == "{}");
		REQUIRE(holder->GetUMLObject("Engine")->ReturnRelationships() == "{{Engine is Parent in relationship Realization Many-to-Many with Cylinders}, }");
		REQUIRE(holder->GetUMLObject("Cylinders")->ReturnRelationships() == "{{Cylinders is Child in relationship Realization Many-to-Many with Engine}, }");
		REQUIRE(holder->GetUMLObject("Fleet")->ReturnRelationships() == "{{Fleet is Parent in relationship Realization One-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Driver")->ReturnRelationships() == "{{Driver is Parent in relationship Generalization Many-to-Many with Vehicle}, }");
	}
}

TEST_CASE("Relationships composite delete functionality test", "0")
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	UMLObject* c = holder->CreateNewClass("Vehicle");
	UMLObject* a = holder->CreateNewClass("Tire");
	UMLObject* d = holder->CreateNewClass("Door");
	UMLObject* e = holder->CreateNewClass("Light");
	UMLObject* f = holder->CreateNewClass("Cylinders");
	UMLObject* g = holder->CreateNewClass("Engine");
	UMLObject* h = holder->CreateNewClass("Fleet");
	UMLObject* i = holder->CreateNewClass("Driver");

	//every one of these must succeed
	REQUIRE((
		holder->AddRelationship("Vehicle", "Tire", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany) &&
		holder->AddRelationship("Vehicle", "Door", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany) &&
		holder->AddRelationship("Vehicle", "Light", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany) &&
		holder->AddRelationship("Vehicle", "Engine", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierOne) &&
		holder->AddRelationship("Engine", "Cylinders", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany) &&
		holder->AddRelationship("Fleet", "Vehicle", RelationshipAggregation, RelationshipQuantifierMany, RelationshipQuantifierMany) &&
		holder->AddRelationship("Driver", "Vehicle", RelationshipRealization, RelationshipQuantifierOne, RelationshipQuantifierOne)
		));

	SECTION("Verify relationship", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle")->ReturnRelationships() == "{{Vehicle is Parent in relationship Composition One-to-Many with Tire}, {Vehicle is Parent in relationship Composition One-to-Many with Door}, {Vehicle is Parent in relationship Composition One-to-Many with Light}, {Vehicle is Parent in relationship Composition One-to-One with Engine}, {Vehicle is Child in relationship Aggregation Many-to-Many with Fleet}, {Vehicle is Child in relationship Realization One-to-One with Driver}, }");

		REQUIRE(holder->GetUMLObject("Tire")->ReturnRelationships() == "{{Tire is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Door")->ReturnRelationships() == "{{Door is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Light")->ReturnRelationships() == "{{Light is Child in relationship Composition Many-to-One with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Engine")->ReturnRelationships() == "{{Engine is Child in relationship Composition One-to-One with Vehicle}, {Engine is Parent in relationship Composition One-to-Many with Cylinders}, }");
		REQUIRE(holder->GetUMLObject("Cylinders")->ReturnRelationships() == "{{Cylinders is Child in relationship Composition Many-to-One with Engine}, }");
		REQUIRE(holder->GetUMLObject("Fleet")->ReturnRelationships() == "{{Fleet is Parent in relationship Aggregation Many-to-Many with Vehicle}, }");
		REQUIRE(holder->GetUMLObject("Driver")->ReturnRelationships() == "{{Driver is Parent in relationship Realization One-to-One with Vehicle}, }");
	}

	holder->DeleteUMLObject("Door");

	//Delete just one class, see what happens
	SECTION("Verify relationships after class deletion", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle")->ReturnRelationships() == "{{Vehicle is Parent in relationship Composition One-to-Many with Tire}, {Vehicle is Parent in relationship Composition One-to-Many with Light}, {Vehicle is Parent in relationship Composition One-to-One with Engine}, {Vehicle is Child in relationship Aggregation Many-to-Many with Fleet}, {Vehicle is Child in relationship Realization One-to-One with Driver}, }");

		REQUIRE(holder->GetUMLObject("Door") == NULL);
	}

	holder->DeleteUMLObject("Vehicle");

	//tire and light should be deleted, since they are both composed children of Vehicle with no other connections
	//fleet and driver lost their only relationship (which was with vehcile)
	//engine lost 1 relationship
	//cylinder is unchanged
	SECTION("Verify relationships after class deletion", "0")
	{
		REQUIRE(holder->GetUMLObject("Vehicle") == NULL);
		REQUIRE(holder->GetUMLObject("Tire") == NULL);
		REQUIRE(holder->GetUMLObject("Light") == NULL);
		REQUIRE(holder->GetUMLObject("Engine")->ReturnRelationships() == "{{Engine is Parent in relationship Composition One-to-Many with Cylinders}, }");
		REQUIRE(holder->GetUMLObject("Cylinders")->ReturnRelationships() == "{{Cylinders is Child in relationship Composition Many-to-One with Engine}, }");
		REQUIRE(holder->GetUMLObject("Fleet")->ReturnRelationships() == "{}");
		REQUIRE(holder->GetUMLObject("Driver")->ReturnRelationships() == "{}");
	}
}

/*
		std::ofstream out("out.txt");
		out << holder->GetUMLObject("Vehicle")->ReturnRelationships();
		out.close();
		*/

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
		a->SetXPosition(100);
		a->SetYPosition(200);
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
		b->SetXPosition(300);
		b->SetYPosition(400);
	}

	holder->EditClassTitle("Tire", "Wheel");
	holder->AddRelationship("Car", "Tire", RelationshipComposition, RelationshipQuantifierOne, RelationshipQuantifierMany);


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

		REQUIRE(c[0]->ReturnRelationships() == "{{Car is Parent in relationship Composition One-to-Many with Tire}, }");
		REQUIRE(c[0]->ReturnRelationships() == d[0]->ReturnRelationships());

		REQUIRE(c[0]->GetXPosition() == 100);
		REQUIRE(c[0]->GetXPosition() == d[0]->GetXPosition());

		REQUIRE(c[0]->GetYPosition() == 200);
		REQUIRE(c[0]->GetYPosition() == d[0]->GetYPosition());
	   
		REQUIRE(c[1]->ReturnTitle() == "Tire");
		REQUIRE(c[1]->ReturnTitle() == d[1]->ReturnTitle());


		REQUIRE(c[1]->ReturnMethods() == "{{Rotate(), unsigned int, {int Dummy param 1, float Dummy param 2 = 0.0f, }, Private}, }");
		REQUIRE(c[1]->ReturnMethods() == d[1]->ReturnMethods());


		REQUIRE(c[1]->ReturnFields() == "{{Manufacturer, string, Public}, {Diameter, unsigned int, Public}, }");
		REQUIRE(c[1]->ReturnFields() == d[1]->ReturnFields());
		
		REQUIRE(c[1]->ReturnRelationships() == "{{Tire is Child in relationship Composition Many-to-One with Car}, }");
		REQUIRE(c[1]->ReturnRelationships() == d[1]->ReturnRelationships());
		
		REQUIRE(c[1]->GetXPosition() == 300);
		REQUIRE(c[1]->GetXPosition() == d[1]->GetXPosition());

		REQUIRE(c[1]->GetYPosition() == 400);
		REQUIRE(c[1]->GetYPosition() == d[1]->GetYPosition());
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



/*
This test will not work until the REPL is updated to reflect the changes in the relationships!
*/

//TEST_CASE("Test Terminal Relationship Functionality (Deleting)", "0")
//{
//	UMLObjectsHolder* holder = new UMLObjectsHolder();
//
//	RunREPL(holder, "add class test_class1");
//	RunREPL(holder, "add class test_class2");
//	RunREPL(holder, "add class test_class3");
//
//	RunREPL(holder, "add relationship test_class1 test_class2");
//	RunREPL(holder, "add relationship test_class2 test_class3");
//
//	RunREPL(holder, "delete relationship test_class1 test_class2");
//	REQUIRE(holder->GetUMLObject("test_class1")->ReturnRelationships() == "{}");
//	REQUIRE(holder->GetUMLObject("test_class2")->ReturnRelationships() == "{{Type: 0, Parent of: test_class3}, }");
//	REQUIRE(holder->GetUMLObject("test_class3")->ReturnRelationships() == "{{Type: 0, Child of: test_class2}, }");
//
//	RunREPL(holder, "delete relationship test_class2");
//	REQUIRE(holder->GetUMLObject("test_class1")->ReturnRelationships() == "{}");
//	REQUIRE(holder->GetUMLObject("test_class2")->ReturnRelationships() == "{{Type: 0, Parent of: test_class3}, }");
//	REQUIRE(holder->GetUMLObject("test_class3")->ReturnRelationships() == "{{Type: 0, Child of: test_class2}, }");
//
//	RunREPL(holder, "delete relationship");
//	REQUIRE(holder->GetUMLObject("test_class1")->ReturnRelationships() == "{}");
//	REQUIRE(holder->GetUMLObject("test_class2")->ReturnRelationships() == "{{Type: 0, Parent of: test_class3}, }");
//	REQUIRE(holder->GetUMLObject("test_class3")->ReturnRelationships() == "{{Type: 0, Child of: test_class2}, }");
//}