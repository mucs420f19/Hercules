﻿#pragma once

#include <string>
#include <vector>

#define UMLFieldVisibilityPublic 1
#define UMLFieldVisibilityPrivate 2

#define RelationshipAbstraction 1
#define RelationshipAggregation 2
#define RelationshipAssociation 3
#define RelationshipBinding 4
#define RelationshipCommunicationPath 5
#define RelationshipComposition 6
#define RelationshipControlFlow 7
#define RelationshipDependency 8
#define RelationshipDeploy 9
#define RelationshipDirectedAssociation 10
#define RelationshipExtend 11
#define RelationshipGeneralization 12
#define RelationshipInterfaceRealization 13
#define RelationshipInclude 14
#define RelationshipManifestation 15
#define RelationshipNoteAttachment 16
#define RelationshipObjectFlow 17
#define RelationshipRealization 18
#define RelationshipUsage 19

//forward declaration
struct UMLRelationship;

struct UMLField
{
	UMLField();
	UMLField(std::string in_name, std::string in_type, int in_visiblity)
	{
		name = in_name;
		type = in_type;
		visibility = in_visiblity;
	}
	UMLField(std::string in_name, std::string in_type, std::string in_visiblity = "1")
	{
		name = in_name;
		type = in_type;
		if (std::stoi(in_visiblity) == UMLFieldVisibilityPublic)
		{
			visibility = UMLFieldVisibilityPublic;
		}
		else visibility = UMLFieldVisibilityPrivate;
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

struct UMLParameter
{
	UMLParameter(std::string in_type, std::string in_name, std::string in_opt = "", std::string in_deflt = "")
	{
		type = in_type;
		name = in_name;
		if (in_opt == "false" || in_opt == "") opt = false; else opt = true;
		deflt = in_deflt;
	}
	std::string type;
	std::string name;
	bool opt;
	std::string deflt;
	std::string ReturnType()
	{
		return type;
	}
	std::string ReturnName()
	{
		return name;
	}
	std::string ReturnOpt()
	{
		if (opt) return "true"; else return "false";
	}
	std::string ReturnDefault()
	{
		return deflt;
	}
	std::string ToString()
	{
		std::string out;
		out += type + " " + name;
		if (opt) out += " = " + deflt;
		return out;
	}
};

struct UMLMethod
{
	UMLMethod();
	UMLMethod(std::string in_name, std::string in_type, std::vector<UMLParameter> in_parameters, int in_visiblity)
	{
		name = in_name;
		return_type = in_type;
		parameters = in_parameters;
		visibility = in_visiblity;
	}
	UMLMethod(std::string in_name, std::string in_type, std::vector<UMLParameter> in_parameters, std::string in_visiblity = "1")
	{
		name = in_name;
		return_type = in_type;
		parameters = in_parameters;
		if (std::stoi(in_visiblity) == UMLFieldVisibilityPublic)
		{
			visibility = UMLFieldVisibilityPublic;
		}
		else visibility = UMLFieldVisibilityPrivate;
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
			out += a.ToString() + ", ";
		}
		out += "}, ";
		out += GetVisibilityString() + "}";
		return out;
	}
	std::string ReturnName();
	std::string ReturnType();
	std::vector<std::string> ReturnParameters();
	std::vector<UMLParameter> ReturnParametersRaw();
	int ReturnVisibility();

	void SetName(std::string in);
	void SetReturnType(std::string in);
	void SetVisibility(int in);
	bool AddParameter(UMLParameter in);
private:
	std::string name;
	std::string return_type;
	std::vector<UMLParameter> parameters;
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
	const std::string & ReturnTitle() const;
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
	std::vector<UMLRelationship> ReturnRelationshipsRaw();
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
	//There is no editing allowed besides chaning the type of relationship
	//Changing who the relationship is attached to is considered a new relationship
	//So you must delete this relationship and start a new one (just like how the GUI would be)
	void SetType(int in) { type = in; }
	std::string GetObject() { return object->ReturnTitle(); }
	std::string ToString()
	{
		return "{ type: " + std::to_string(type) + ", object: " + object->ReturnTitle() + ", parent: " + std::to_string(parent) + "}";
	}
};