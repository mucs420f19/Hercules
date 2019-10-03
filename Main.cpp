// HerculesProject.cpp : Defines the entry point for the application.
//

#include <iostream>

#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h"

void RunUnitTest1()
{
	std::cout << "---------------\nRunning test 1...---------------\n\n\n\n";


	UMLObjectsHolder* holder = new UMLObjectsHolder();

	std::cout << "Creating example UMLObjects...\n\n\n";

	std::string before1 = "empty string", before2 = "empty string", after1, after2;
	UMLObject* a = NULL, * b = NULL;

	if (holder->CreateNewClass("Car"))
	{
		std::cout << "Successfully created class" << std::endl;

		a = holder->ReturnPtrToVector()[0];

		std::vector<std::string> testVec;

		a->AddField(UMLField("Color", "string", UMLFieldVisibilityPublic));
		a->AddField(UMLField("Make", "string", UMLFieldVisibilityPublic));
		a->AddMethod(UMLMethod("Drive()", "void", testVec, UMLFieldVisibilityPrivate));
		std::cout << a->ToString() << std::endl << std::endl;
		before1 = a->ToString();

	}
	else
	{
		std::cout << "Unable to create class due to duplicate name" << std::endl;
	}

	if (holder->CreateNewClass("Wheel"))
	{
		std::cout << "Successfully created class" << std::endl;

		b = holder->ReturnPtrToVector()[1];

		std::vector<std::string> testVec;
		testVec.push_back("Dummy param 1");
		testVec.push_back("Dummy param 2");

		b->AddField(UMLField("Manufacturer", "string", UMLFieldVisibilityPublic));
		b->AddField(UMLField("Diameter", "unsigned int", UMLFieldVisibilityPublic));
		b->AddMethod(UMLMethod("Rotate()", "unsigned int", testVec, UMLFieldVisibilityPrivate));
		std::cout << b->ToString() << std::endl << std::endl;
		before2 = b->ToString();

	}
	else
	{
		std::cout << "Unable to create class due to duplicate name" << std::endl;
	}

	std::cout << "Saving and destroying these UMLObjects...\n\n\n";

	//save them to file
	SavingLoadingIO::SaveProjectToFile(holder);

	//destory them out of memory
	delete holder;

	std::cout << "Reloading UMLObjects...\n\n\n";

	//load them into memory again
	holder = new UMLObjectsHolder();

	if (SavingLoadingIO::LoadProject(holder))
	{
		std::cout << "Load successful" << std::endl;
	}
	else
	{
		std::cout << "Unable to load" << std::endl;
	}



	std::cout << "Comparing UMLObjects before and after...\n\n\n";

	if (a != NULL)
	{
		a = holder->ReturnPtrToVector()[0];
		std::cout << a->ToString() << std::endl << std::endl;
		after1 = a->ToString();
	}

	if (b != NULL)
	{
		b = holder->ReturnPtrToVector()[1];
		std::cout << b->ToString() << std::endl << std::endl;
		after2 = b->ToString();
	}

	if (before1 == after1)
	{
		std::cout << "UMLObject1 is correct" << std::endl;
	}
	else std::cout << "UMLObject1 is not correct" << std::endl;

	if (before2 == after2)
	{
		std::cout << "UMLObject2 is correct" << std::endl;
	}
	else std::cout << "UMLObject2 is not correct" << std::endl;

	std::cout << "---------------\nTest 1 completed...---------------\n\n\n\n";

}

void RunUnitTest2()
{
	std::cout << "---------------\nRunning test 2...\n---------------\n\n\n\n";

	UMLObjectsHolder* holder = new UMLObjectsHolder();


	UMLObject* a = NULL, * b = NULL;

	if (holder->CreateNewClass("Car"))
	{
		std::cout << "Successfully created class" << std::endl;

		a = holder->ReturnPtrToVector()[0];

		std::vector<std::string> testVec;

		a->AddField(UMLField("Color", "string", UMLFieldVisibilityPublic));
		a->AddField(UMLField("Make", "string", UMLFieldVisibilityPublic));
		a->AddMethod(UMLMethod("Drive()", "void", testVec, UMLFieldVisibilityPrivate));
		std::cout << a->ToString() << std::endl << std::endl;

	}
	else
	{
		std::cout << "Unable to create class due to duplicate name" << std::endl;
	}

	if (holder->CreateNewClass("Wheel"))
	{
		std::cout << "Successfully created class" << std::endl;

		b = holder->ReturnPtrToVector()[1];

		std::vector<std::string> testVec;
		testVec.push_back("Dummy param 1");
		testVec.push_back("Dummy param 2");

		b->AddField(UMLField("Manufacturer", "string", UMLFieldVisibilityPublic));
		b->AddField(UMLField("Diameter", "unsigned int", UMLFieldVisibilityPublic));
		b->AddMethod(UMLMethod("Rotate()", "unsigned int", testVec, UMLFieldVisibilityPrivate));
		std::cout << b->ToString() << std::endl << std::endl;

	}
	else
	{
		std::cout << "Unable to create class due to duplicate name" << std::endl;
	}


	if (b != NULL)
	{
		if (holder->EditClassTitle("Car", "Wheel"))
		{
			std::cout << "Rename succeeded.... this should not have worked!\n\n\n";
			std::cout << "TEST 2 FAILED\n\n\n";
		}
		else
		{
			std::cout << "Unable to rename \"Wheel\" to \"Car\", class name already exists\n\n\n";
		}

		std::cout << b->ToString() << std::endl << std::endl;


		if (holder->EditClassTitle("Tire", "Wheel"))
		{
			std::cout << "Rename succeeded....\n\n\n";
		}
		else
		{
			std::cout << "Unable to rename \"Wheel\" to \"Tire\", class name already exists\n\n\n";
			std::cout << "TEST 2 FAILED\n\n\n";
		}

		std::cout << b->ToString() << std::endl << std::endl;
	}
	else
	{
		std::cout << "TEST 2 FAILED\n\n\n";

	}


	std::cout << "---------------\nTest 2 completed...\n---------------\n\n\n\n";
}


void RunUnitTest3()
{
	std::cout << "---------------\nRunning test 3...\n---------------\n\n\n\n";


	UMLObject* a = NULL, * b = NULL;
	UMLObjectsHolder* holder = new UMLObjectsHolder();

	a = holder->CreateNewClass("Car");
	b = holder->CreateNewClass("Wheel");

	holder->AddRelationship("Car", "Wheel", RelationshipAggregation);

	std::cout << a->ReturnRelationships() << std::endl;
	std::cout << b->ReturnRelationships() << std::endl;

	holder->EditRelationship("Car", "Wheel", RelationshipComposition);
	std::cout << a->ReturnRelationships() << std::endl;
	std::cout << b->ReturnRelationships() << std::endl;

	holder->DeleteRelationship("Car", "Wheel");
	std::cout << a->ReturnRelationships() << std::endl;
	std::cout << b->ReturnRelationships() << std::endl;

}

int main()
{
	//RunUnitTest1();
	//RunUnitTest2();
	//RunUnitTest3();

	UMLObjectsHolder* holder = new UMLObjectsHolder();
	bool run = true;
	int choice;
	std::string input, input2;

	std::cout << std::endl << "********************Welcome to Hercules********************" << std::endl;

	while (run)
	{
		std::cout << std::endl << "********************" << std::endl;
		std::cout << "1. View Class List" << std::endl;
		std::cout << "2. Create New Class" << std::endl;
		std::cout << "3. Delete A Class" << std::endl;
		std::cout << "4. Edit A Class" << std::endl;
		std::cout << "5. Save" << std::endl;
		std::cout << "6. Load" << std::endl;
		std::cout << "7. Exit" << std::endl;
		std::cout << "********************" << std::endl << std::endl;
		std::cout << "Which task would you like to run?" << std::endl;

		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			std::cout << std::endl << "Class List:" << std::endl;

			holder->UMLObjectPrintTitles();

			break;
		}

		case 2:
		{
			std::cout << std::endl << "Please enter the name of the new class." << std::endl;
			std::cin >> input;
			std::cout << std::endl;

			if (holder->CreateNewClass(input))
				std::cout << "Class created sucessfully." << std::endl;
			else
				std::cout << "Class creation failed." << std::endl;

			break;
		}

		case 3:
		{
			if (holder->Size())
			{
				std::cout << std::endl;

				holder->UMLObjectPrintTitles();

				std::cout << std::endl << "Please enter the number of the class you wish to delete." << std::endl;
				std::cin >> input;

				if (holder->DeleteUMLObject(input))
					std::cout << "Delete successful." << std::endl << std::endl;
				else
					std::cout << "Unable to delete class." << std::endl << std::endl;
			}
			else
				std::cout << std::endl << "You have no classes to delete." << std::endl;

			break;
		}

		case 4:
		{
			std::cout << std::endl << "Please enter the name of the class you wish to edit." << std::endl;

			std::cin >> input;

			std::cout << std::endl << "Please enter the new name for the class." << std::endl;

			std::cin >> input2;

			if (holder->EditClassTitle(input2, input))
				std::cout << "Rename successful." << std::endl << std::endl;
			else
				std::cout << "Unable to rename class." << std::endl << std::endl;

			break;
		}

		case 5:
		{
			std::cout << std::endl << "Please enter the name of the save file." << std::endl;

			std::cin >> input;

			SavingLoadingIO::SaveProjectToFile(holder, input);

			std::cout << std::endl << "File saved successfully as: " << input << std::endl;

			break;
		}

		case 6:
		{
			std::cout << std::endl << "Please enter the name of the file you wish to load." << std::endl;

			std::cin >> input;

			if (SavingLoadingIO::LoadProject(holder, input))
				std::cout << "Load successful." << std::endl << std::endl;
			else
				std::cout << "Unable to load." << std::endl << std::endl;

			break;
		}

		case 7:
		{
			run = false;

			std::cout << std::endl << "********************" << std::endl;
			std::cout << "Thank you for using Hercules!" << std::endl;
			std::cout << "********************" << std::endl << std::endl;

			break;
		}

		default:
		{
			std::cout << std::endl << "Invalid entry, please enter a number from 1 to 7." << std::endl << std::endl;
		}
		}
	}

	return 0;
}