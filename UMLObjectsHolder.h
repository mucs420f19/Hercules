#pragma once

#include <iostream>

#include "UMLObject.h"

class UMLObjectsHolder
{
public:
	UMLObjectsHolder();
	//this method is used to add a new class. the holder will keep track of bookkeeping and everything
	UMLObject* CreateNewClass(std::string title);
	bool IsTitleUnique(std::string in);
	~UMLObjectsHolder();
	//delete all project contents
	void ClearProject();
	//print to console the class titles
	void UMLObjectPrintTitles();
	//print to console the entire contents of a class (using its ToString method)
	void UMLObjectPrintContents();
	//Returns a vector containing just the object titles
	std::vector<const char*> UMLObjectReturnTitles();
	std::vector<std::string> UMLObjectReturnTitlesString();
	//returns a vector containing pointers to the classes
	//this allows direct access to the objects and might not be best practice
	std::vector<UMLObject*> ReturnPtrToVector();

	//if a UMLObject was created externally, this method can be used to add it in to the holder
	//this is an alternative to the CreateNewClass using just a title but might not be best practice
	void AddUMLObject(UMLObject * in);
	//deletes an object using title as primary key
	bool DeleteUMLObject(std::string title);
	//returns number of objects in holder
	size_t Size();
	//Edit title.. pass in a new title and the name of the old title. returns true if successful
	bool EditClassTitle(std::string new_title, std::string old_title);
	//Add a relationship between a parent and child. returns true if successful
	bool AddRelationship(std::string parent, std::string child, int type);
	//Edit a relationship between a specified parent and child. returns true if successful
	//The only thing that can be edited is the relationship type.. otherwise that is considered a new relationship.
	bool EditRelationship(std::string parent, std::string child, int type);
	//delete the specified relationship. returns true if successful
	bool DeleteRelationship(std::string parent, std::string child);
	UMLObject* GetUMLObject(std::string title);

private:
	std::vector<UMLObject*> UMLObjects_holder;

};