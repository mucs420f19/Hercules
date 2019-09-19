// HerculesProject.cpp : Defines the entry point for the application.
//

#include <iostream>

#include "SavingLoadingIO.h"
#include "UMLObject.h"

std::vector<UMLObject*> UMLObjects_holder;

UMLObject* UMLObjectFactory()
{
	UMLObject* a = new UMLObject();
	UMLObjects_holder.push_back(a);
	return a;
}

void UMLObjectsDestructor()
{
	for (auto i : UMLObjects_holder)
	{
		delete i;
	}
}

void UMLObjectPrintTitles()
{
	for (auto i : UMLObjects_holder)
		std::cout << i->ReturnTitle() << std::endl;
}

void RunUnitTests()
{
	std::cout << "Creating example UMLObjects...\n\n\n";

	UMLObject* a = UMLObjectFactory();

	a->SetTitle("Car");
	a->AddField(UMLField("Color", "string", UMLFieldVisibilityPublic));
	a->AddField(UMLField("Make", "string", UMLFieldVisibilityPublic));
	a->AddMethod(UMLMethod("Drive()", "void", {}, UMLFieldVisibilityPrivate));


	UMLObject* b = UMLObjectFactory();

	b->SetTitle("Wheels");
	b->AddField(UMLField("Manufacturer", "string", UMLFieldVisibilityPublic));
	b->AddField(UMLField("Diameter", "unsigned int", UMLFieldVisibilityPublic));
	b->AddMethod(UMLMethod("Rotate()", "unsigned int", { "Dummy param 1", "Dummy param 2" }, UMLFieldVisibilityPrivate));

	std::cout << a->ToString() << std::endl << std::endl;

	std::cout << b->ToString() << std::endl << std::endl;


	std::string before1, before2, after1, after2;

	before1 = a->ToString();
	before2 = b->ToString();

	std::cout << "Saving and destroying these UMLObjects...\n\n\n";

	//save them to file
	SavingLoadingIO::SaveProjectToFile(UMLObjects_holder);

	//destory them out of memory
	UMLObjectsDestructor();

	std::cout << "Reloading UMLObjects...\n\n\n";

	//load them into memory again
	UMLObjects_holder = SavingLoadingIO::LoadProject();



	std::cout << "Comparing UMLObjects before and after...\n\n\n";
	a = UMLObjects_holder[0];
	b = UMLObjects_holder[1];
	std::cout << a->ToString() << std::endl << std::endl;
	std::cout << b->ToString() << std::endl << std::endl;

	after1 = a->ToString();
	after2 = b->ToString();

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
}

int main()
{
	RunUnitTests();
	return 0;
}