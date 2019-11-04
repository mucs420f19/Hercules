#pragma once

#include <string>
#include <vector>

const int UMLFieldVisibilityPublic = 1;
const int UMLFieldVisibilityPrivate = 2;
const int UMLFieldVisibilityProtected = 3;

const int RelationshipAggregation = 2;
const int RelationshipComposition = 6;
const int RelationshipGeneralization = 12;
const int RelationshipRealization = 18;

const int RelationshipQuantifierOne = 1;
const int RelationshipQuantifierMany = 2;

//forward declaration
struct UMLRelationship;

//structure for the field
struct UMLField
{
	UMLField()
	{ }

	UMLField(std::string inName)
	{
		name = inName;
		type = "no type defined";
		visibility = UMLFieldVisibilityPrivate;
	}
	UMLField(std::string inName, std::string inType, int inVisibility = 1)
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
			case UMLFieldVisibilityProtected:
			{
				out = "Protected";
				break;
			}
			default:
				out = "Invalid Visiblity";
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
//structure for the parameters
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
//structure for the methods
struct UMLMethod
{
	UMLMethod()
	{ }

	UMLMethod(std::string inName)
	{
		name = inName;
		return_type = "no type defined";
		visibility = UMLFieldVisibilityPrivate;
	}
	UMLMethod(std::string inName, std::string inType, std::vector<UMLParameter> inParameters, int inVisibility)
	{
		name = inName;
		return_type = inType;
		parameters = inParameters;
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
		case UMLFieldVisibilityProtected:
		{
			out = "Protected";
			break;
		}
		default:
			out = "Invalid Visiblity";
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
	void SetTitle(std::string in);
	bool AddField(UMLField in);
	bool AddMethod(UMLMethod in);
	const std::string & ReturnTitle() const;
	std::string ReturnFields();
	std::string ReturnMethods();
	std::string ToString();

	//these need to be saved every time for the GUI, so they are included here
	int GetXPosition();
	int GetYPosition();
	void SetXPosition(int in);
	void SetYPosition(int it);

	std::string ReturnRelationships();
	void AddRelationship(UMLRelationship in);
	size_t GetIndexRelationshipWith(std::string in);
	UMLRelationship * GetRelationshipWith(std::string in);
	void UpdateRelationship(size_t index, int type, int quantifier);
	void DeleteRelationship(std::string in);
	
	bool EditMethod(std::string oldName, std::string newName);
	bool EditField(std::string oldName, std::string newName);
	bool DeleteMethod(std::string in);
	bool DeleteField(std::string in);
	
	bool DoesMethodExist(std::string in);
	bool DoesFieldExist(std::string in);

	size_t GetLargestStringSize();
	std::string ReturnFieldsPretty();
	std::string ReturnMethodsPretty();
	std::string ToStringPretty();
	std::string ReturnRelationshipsPretty();
	
	std::vector<UMLField> ReturnFieldsRaw();
	std::vector<UMLMethod> ReturnMethodsRaw();
	std::vector<UMLRelationship> ReturnRelationshipsRaw();
	size_t RelationshipsSize();
private:
	std::string title;
	std::vector<UMLField> fields;
	std::vector<UMLMethod> methods;
	std::vector<UMLRelationship> relationships;
	//these will be used as the coordinates for display on the GUI
	int x = 0, y = 0;
};

//Relationship objects are part of UMLObjects but they cannot be edited directly
//The need to be edited through the holder, which takes care of bookkeeping between all of the UMLObjects
struct UMLRelationship
{
	int type;
	int quantifier;
	//the other object it has a relationship with
	UMLObject* object;
	//the object this relationship belongs to
	UMLObject* thisObject;
	//is this the parent in the relationship?
	bool parent;

	//There is no editing allowed besides changing the type of relationship
	//Changing who the relationship is attached to is considered a new relationship
	//So you must delete this relationship and start a new one (just like how the GUI would be)
	void SetType(int in) { type = in; }
  int GetType() { return type; }
	void SetQuantifier(int in) { quantifier = in; }
	std::string GetObject() { return object->ReturnTitle(); }
  
  std::string GetQuantifier() { return GetQuantifierName(); }
	std::string GetOtherQuantifier() { return object->GetRelationshipWith(thisObject->ReturnTitle())->GetQuantifier(); }
	bool GetParent() { return parent; }
	std::string GetRelationshipTypeName()
	{
		std::string out;
		switch (type)
		{
		case RelationshipAggregation:
			out = "Aggregation";
			break;
		case RelationshipComposition:
			out = "Composition";
			break;
		case RelationshipGeneralization:
			out = "Generalization";
			break;
		case RelationshipRealization:
			out = "Realization";
			break;
		default:
			out = "Unrecognized relationship";
		}
		return out;
	}
	std::string GetQuantifierName()
	{
		std::string out;
		switch (quantifier)
		{
		case RelationshipQuantifierOne:
			out = "One";
			break;
		case RelationshipQuantifierMany:
			out = "Many";
			break;
		default:
			out = "Unrecognized quantifier";
		}
		return out;
	}
  
  std::string ToString()
	{
		return "{" + thisObject->ReturnTitle() + ((parent) ? " is Parent" : " is Child") + " in relationship " + GetRelationshipTypeName() + " " + GetQuantifierName() + "-to-" + GetOtherQuantifier() + " with " + GetObject() + "}";
  }
  
  std::string ToStringPretty()
	{
		if (parent == true)
		  return "Parent of: " + object->ReturnTitle();
		
		else
		  return "Child of: " + object->ReturnTitle();
  }
};