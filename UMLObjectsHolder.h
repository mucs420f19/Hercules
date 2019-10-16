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
<<<<<<< Updated upstream
	std::vector<const char*> UMLObjectReturnTitles();
=======
	//Returns a vector containing just the object titles
	std::vector<const char*> UMLObjectReturnTitles();
	//returns a vector containing pointers to the classes
	//this allows direct access to the objects and might not be best practice
>>>>>>> Stashed changes
	std::vector<UMLObject*> ReturnPtrToVector();
	void AddUMLObject(UMLObject * in);
	bool DeleteUMLObject(std::string title);
	size_t Size();
	bool EditClassTitle(std::string new_title, std::string old_title);

private:
	std::vector<UMLObject*> UMLObjects_holder;

};