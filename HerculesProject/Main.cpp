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

int main()
{
	UMLObject* a = UMLObjectFactory();

	a->SetTitle("Car");
	a->AddField(UMLField("Color", "string", UMLFieldVisibilityPublic));
	a->AddField(UMLField("Make", "string", UMLFieldVisibilityPublic));
	a->AddMethod(UMLMethod("Drive()", "void", {}, UMLFieldVisibilityPrivate));


	UMLObject* b = UMLObjectFactory();

	b->SetTitle("Wheels");
	b->AddField(UMLField("Manufacturer", "string", UMLFieldVisibilityPublic));
	b->AddField(UMLField("Diameter", "unsigned int", UMLFieldVisibilityPublic));
	b->AddMethod(UMLMethod("Rotate()", "unsigned int", {}, UMLFieldVisibilityPrivate));

	std::cout << a->ToString() << std::endl << std::endl;

	std::cout << b->ToString() << std::endl;

	UMLObjectsDestructor();

	SavingLoadingIO::SaveProjectToFile(UMLObjects_holder);

	return 0;
}