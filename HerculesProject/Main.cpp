// HerculesProject.cpp : Defines the entry point for the application.
//

#include <iostream>

#include "UMLObject.h"

int main()
{
	std::cout << "Hello Team Hercules." << std::endl;


	UMLObject* a = new UMLObject();

	a->SetTitle("test1");
	a->AddField(UMLField("field1", "float", UMLFieldVisiblityPublic));
	a->AddField(UMLField("field2", "unsigned int", UMLFieldVisiblityPrivate));
	a->AddMethod(UMLMethod("Method1()", "unsigned int", {}, UMLFieldVisiblityPrivate));



	std::cout << a->ToString() << std::endl;

	return 0;
}