#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <cctype>

#include "UMLObject.h"

const int ClassDoesntExist = 1;
const int FieldExists = 2;
const int FieldSuccess = 3;
const int MethodExists = 2;
const int MethodSuccess = 3;

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
	//print to console the contents of a class in a pseudo UML manner
	void UMLObjectsHolder::UMLObjectPrintContentsREPL();
	//Returns a vector containing just the object titles
	std::vector<std::string> UMLObjectReturnTitles();
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


	//used by the REPL to retrieve a relationship type from a string
	int GetRelationshipTypeFromString(std::string in);
	//similarly for the Visibility
	int GetVisibilityTypeFromString(std::string in);

	int AddField(std::string class_title, std::string field_title, std::string type, int visibility);
	bool EditFieldName(std::string class_title, std::string old_field_title, std::string new_field_title);
	bool EditFieldType(std::string class_title, std::string field_title, std::string type);
	bool EditFieldVisibility(std::string class_title, std::string field_title, std::string visibility);
	bool DeleteField(std::string class_title, std::string field_title);

	bool AddMethod(std::string class_title, std::string method_title, std::string type, int visibility);
	bool EditMethodName(std::string class_title, std::string old_method_name, std::string new_method_name);
	bool EditMethodReturnType(std::string class_title, std::string method_name, std::string type);
	bool EditMethodVisibility(std::string class_title, std::string method_title, std::string visibility);
	bool DeleteMethod(std::string class_title, std::string method_title);

	bool AddParameter(std::string class_title, std::string method_title, std::string param_name);
	bool EditParameterName(std::string class_title, std::string method_title, std::string old_param_name, std::string new_param_name);
	bool EditParameterType(std::string class_title, std::string method_title, std::string param_name, std::string type);
	//this makes the parameter optional, since it has a default value
	bool EditParameterSetDefaultValue(std::string class_title, std::string method_title, std::string param_name, std::string value);
	//this makes the parameter required again, since it no longer has a default value
	bool EditParameterClearDefaultValue(std::string class_title, std::string method_title, std::string param_name);
	bool DeleteParameter(std::string class_title, std::string method_title, std::string param_name);

	//Add a relationship between a parent and child. returns true if successful
	bool AddRelationship(std::string parent, std::string child, int type, int quantifier1, int quantifier2);
	//Edit a relationship between a specified parent and child. returns true if successful
	//The only thing that can be edited is the relationship type.. otherwise that is considered a new relationship.
	bool EditRelationship(std::string parent, std::string child, int type, int quantifier1, int quantifier2);
	//delete the specified relationship. returns true if successful
	bool DeleteRelationship(std::string parent, std::string child);
	//this function is not used, and under normal conditions should never need to be used
	//its purpose is to go through the relationships and fix missing quantifiers, but that should not happen 
	void RefreshRelationships();
	UMLObject* GetUMLObject(std::string title);

private:
	std::vector<UMLObject*> UMLObjects_holder;

};