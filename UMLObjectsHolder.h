#pragma once

#include <iostream>

#include "UMLObject.h"

class UMLObjectsHolder
{
public:
	UMLObjectsHolder();
	UMLObject* CreateNewClass(std::string title);
	bool IsTitleUnique(std::string in);
	~UMLObjectsHolder();
	void UMLObjectPrintTitles();
	void UMLObjectPrintContents();
	std::vector<UMLObject*> ReturnPtrToVector();
	void AddUMLObject(UMLObject * in);
	bool DeleteUMLObject(std::string title);
	size_t Size();
	bool EditClassTitle(std::string new_title, std::string old_title);
	bool AddRelationship(std::string parent, std::string child, int type);
	bool EditRelationship(std::string parent, std::string child, int type);
	bool DeleteRelationship(std::string parent, std::string child);

private:
	std::vector<UMLObject*> UMLObjects_holder;
	UMLObject* GetObject(std::string title);
};