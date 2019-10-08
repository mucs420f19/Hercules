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
	std::vector<const char*> UMLObjectReturnTitles();
	std::vector<UMLObject*> ReturnPtrToVector();
	void AddUMLObject(UMLObject * in);
	bool DeleteUMLObject(std::string title);
	size_t Size();
	bool EditClassTitle(std::string new_title, std::string old_title);

private:
	std::vector<UMLObject*> UMLObjects_holder;

};