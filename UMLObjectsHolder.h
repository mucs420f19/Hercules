#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <cctype>

#include "UMLObject.h"

class UMLObjectsHolder
{
public:
	UMLObjectsHolder();
	~UMLObjectsHolder();
	//delete all project contents
	void ClearProject();


	//this method is used to add a new class. the holder will keep track of bookkeeping and everything
	int CreateNewClass(std::string title);

	//deletes a class using title as primary key
	int DeleteClass(std::string title);
	//returns number of objects in holder
	size_t Size();
	//Edit title.. pass in a new title and the name of the old title. returns true if successful
	int EditClassTitle(std::string new_title, std::string old_title);

	int AddField(std::string class_title, std::string field_title, std::string type, std::string visibility);
	int EditFieldName(std::string class_title, std::string old_field_title, std::string new_field_title);
	int EditFieldType(std::string class_title, std::string field_title, std::string type);
	int EditFieldVisibility(std::string class_title, std::string field_title, std::string vis);
	int DeleteField(std::string class_title, std::string field_title);

	int AddMethod(std::string class_title, std::string method_title, std::string type, std::string visibility);
	int EditMethodName(std::string class_title, std::string old_method_name, std::string new_method_name);
	int EditMethodReturnType(std::string class_title, std::string method_name, std::string type);
	int EditMethodVisibility(std::string class_title, std::string method_title, std::string vis);
	int DeleteMethod(std::string class_title, std::string method_title);

	int AddParameter(std::string class_title, std::string method_title, std::string param_name);
	int EditParameterName(std::string class_title, std::string method_title, std::string old_param_name, std::string new_param_name);
	int EditParameterType(std::string class_title, std::string method_title, std::string param_name, std::string type);
	//this makes the parameter optional, since it has a default value
	int EditParameterSetDefaultValue(std::string class_title, std::string method_title, std::string param_name, std::string value);
	//this makes the parameter required again, since it no longer has a default value
	int EditParameterClearDefaultValue(std::string class_title, std::string method_title, std::string param_name);
	int DeleteParameter(std::string class_title, std::string method_title, std::string param_name);

	//Add a relationship between a parent and child. returns true if successful
	int AddRelationship(std::string parent, std::string child, std::string type, std::string quantifier1, std::string quantifier2);
	//Edit a relationship between a specified parent and child. returns true if successful
	//The only thing that can be edited is the relationship type.. otherwise that is considered a new relationship.
	int EditRelationship(std::string parent, std::string child, std::string type, std::string quantifier1, std::string quantifier2);
	//delete the specified relationship. returns true if successful
	int DeleteRelationship(std::string parent, std::string child);



	//the functions below are "naughty" functions because they allow direct access to the model
	//this violates the MVC principle because they effectively skip the controller
	//this could allow for mistakes or bad practices to be implemented
	int SetY(std::string which_class, int y);
	int SetX(std::string which_class, int x);
	int GetX(std::string which_class);
	int GetY(std::string which_class);
	//returns a vector containing pointers to the classes
	//this allows direct access to the objects and might not be best practice
	std::vector<UMLObject*> ReturnPtrToVector();
	UMLObject* GetUMLObject(std::string title);
	//if a UMLObject was created externally, this method can be used to add it in to the holder
	//this is an alternative to the CreateNewClass using just a title but might not be best practice
	void AddUMLObject(UMLObject* in);


	//the functions below all belong in REPL because they have nothing to do with the controller or model.
	//these functions might require access direct to the model, so something will have to be implemented to do that
	//for now they are fine, since they do not violate MVC but they are just awkwardly living here

	//print to console the class titles
	void UMLObjectPrintTitles();
	//print to console the entire contents of a class (using its ToString method)
	void UMLObjectPrintContents();
	//print to console the contents of a class in a pseudo UML manner
	void UMLObjectPrintContentsREPL();
	//Returns a vector containing just the object titles
	std::vector<std::string> ReturnAll();
	std::vector<std::string> ReturnTitles();
	std::vector<std::string> ReturnFields();
	std::vector<std::string> ReturnMethods();
	std::vector<std::string> ReturnRelationships();

private:
	//these functions are not needed outside of the controller
	std::vector<UMLObject*> UMLObjects_holder;
	bool IsTitleUnique(std::string in);
	int GetRelationshipTypeFromString(std::string in);
	int GetVisibilityTypeFromString(std::string in);
	int GetQuantifierFromString(std::string in);
	std::string IsFieldReferringToExistingClass(std::string in);
};