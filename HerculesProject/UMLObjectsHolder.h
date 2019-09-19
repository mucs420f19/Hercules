#pragma once

#include <iostream>

#include "UMLObject.h"

class UMLObjectsHolder
{
public:
	UMLObjectsHolder();
	bool CreateNewClass(std::string title);
	bool IsTitleUnique(std::string in);
	~UMLObjectsHolder();
	void UMLObjectPrintTitles();
	void UMLObjectPrintContents();
	std::vector<UMLObject*> ReturnPtrToVector();
	void AddUMLObject(UMLObject * in);

private:
	std::vector<UMLObject*> UMLObjects_holder;

};