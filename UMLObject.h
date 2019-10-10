#pragma once

#include <string>
#include <vector>

const int UMLFieldVisibilityPublic = 1;
const int UMLFieldVisibilityPrivate = 2;

const int RelationshipAbstraction =1;
const int RelationshipAggregation = 2;
const int RelationshipAssociation = 3;
const int RelationshipBinding = 4;
const int RelationshipCommunicationPath = 5;
const int RelationshipComposition = 6;
const int RelationshipControlFlow = 7;
const int RelationshipDependency =8;
const int RelationshipDeploy = 9;
const int RelationshipDirectedAssociation = 10;
const int RelationshipExtend = 11;
const int RelationshipGeneralization = 12;
const int RelationshipInterfaceRealization = 13;
const int RelationshipInclude = 14;
const int RelationshipManifestation = 15;
const int RelationshipNoteAttachment = 16;
const int RelationshipObjectFlow = 17;
const int RelationshipRealization = 18;
const int RelationshipUsage = 19;

//forward declaration
struct UMLRelationship;

struct UMLField
{
	UMLField();
	UMLField(std::string inName, std::string inType, int inVisibility)
	{
		name = inName;
		type = inType;
		visibility = inVisibility;
	}
	std::string GetVisibilityString()
	{
		std::string out;
		switch (visibility)
		{
			case UMLFieldVisibilityPublic: 
			{
				out = "Public";
				break;
			}
			case UMLFieldVisibilityPrivate:
			{
				out = "Private";
				break;
			}
		}
		return out;
	}
	std::string ToString()
	{
		return "{" + name + ", " + type + ", " + GetVisibilityString() + "}";
	 }
	std::string ReturnName();
	std::string ReturnType();
	int ReturnVisibility();

	void SetName(std::string in);
	void SetReturnType(std::string in);
	void SetVisibility(int in);
private:
	std::string name;
	std::string type;
	int visibility;
};

struct UMLMethod
{
	UMLMethod();
	UMLMethod(std::string inName, std::string inType, std::vector<std::string> in_parameters, int inVisibility)
	{
		name = inName;
		return_type = inType;
		parameters = in_parameters;
		visibility = inVisibility;
	}
	std::string GetVisibilityString()
	{
		std::string out;
		switch (visibility)
		{
		case UMLFieldVisibilityPublic:
		{
			out = "Public";
			break;
		}
		case UMLFieldVisibilityPrivate:
		{
			out = "Private";
			break;
		}
		}
		return out;
	}
	std::string ToString()
	{
		std::string out = "{" + name + ", " + return_type + ", {";
		for (auto a : parameters)
		{
			out += a + ", ";
		}
		out += "}, ";
		out += GetVisibilityString() + "}";
		return out;
	}
	std::string ReturnName();
	std::string ReturnType();
	std::vector<std::string> ReturnParameters();
	int ReturnVisibility();

	void SetName(std::string in);
	void SetReturnType(std::string in);
	void SetVisibility(int in);
	void SetParameters(std::vector<std::string> in);
private:
	std::string name;
	std::string return_type;
	std::vector<std::string> parameters;
	int visibility;
};

class UMLObject
{
public:
	UMLObject();
	UMLObject(UMLObject * copy);
	void SetTitle(std::string in);
	void AddField(UMLField in);
	void AddMethod(UMLMethod in);
	std::string ReturnTitle();
	std::string ReturnFields();
	std::string ReturnMethods();
	std::string ToString();

	std::string ReturnRelationships();
	void AddRelationship(UMLRelationship in);
	size_t GetIndexRelationshipWith(std::string in);
	void UpdateRelationship(size_t index, int type);
	void DeleteRelationship(size_t index);

	std::vector<UMLField> ReturnFieldsRaw();
	std::vector<UMLMethod> ReturnMethodsRaw();
private:
	std::string title;
	std::vector<UMLField> fields;
	std::vector<UMLMethod> methods;
	std::vector<UMLRelationship> relationships;
};

//Relationship objects are part of UMLObjects but they cannot be edited directly
//The need to be edited through the holder, which takes care of bookkeeping between all of the UMLObjects
struct UMLRelationship
{
	int type;
	UMLObject* object;
	bool parent;
	//There is no editing allowed besides changing the type of relationship
	//Changing who the relationship is attached to is considered a new relationship
	//So you must delete this relationship and start a new one (just like how the GUI would be)
	void SetType(int in) { type = in; }
	std::string GetObject() { return object->ReturnTitle(); }
	std::string ToString()
	{
		return "{ type: " + std::to_string(type) + ", object: " + object->ReturnTitle() + ", parent: " + std::to_string(parent) + "}";
	}
};