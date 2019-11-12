#pragma once

#include <string>
#include <vector>

const int UMLFieldVisibilityPublic = 1;
const int UMLFieldVisibilityPrivate = 2;
const int UMLFieldVisibilityProtected = 3;

const int RelationshipAggregation = 1;
const int RelationshipComposition = 2;
const int RelationshipGeneralization = 3;
const int RelationshipRealization = 4;

const int RelationshipQuantifierOne = 1;
const int RelationshipQuantifierMany = 2;

//error codes
const int ElementSuccess = 0;
const int ClassDoesntExist = 1;
const int ElementAlreadyExists = 2;
const int ClassAlreadyExists = 3;
const int ElementDoesntExist = 4;
const int RelationshipAlreadyExists = 5;
const int InvalidQuantifier = 6;
const int InvalidRelationshipType = 7;
const int RelationshipDoesNotExist = 8;
const int InvalidVisibility = 9;

//forward declaration
struct UMLRelationship;

//structure for the field
struct UMLField
{
	UMLField(std::string inName)
	{
		name = inName;
		type = "no type defined";
		visibility = UMLFieldVisibilityPrivate;
	}
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
	std::vector<UMLParameter> ReturnParametersRaw();
	int ReturnVisibility();

	void SetName(std::string in);
	void SetReturnType(std::string in);
	void SetVisibility(int in);
	int AddParameter(UMLParameter in);
	int EditParamName(std::string old, std::string newn);
	int EditParamType(std::string name, std::string type);
	int SetParamDefaultValue(std::string name, std::string value);
	int ClearParamDefaultValue(std::string name);
	int DeleteParameter(std::string name);
//private:
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
	int AddField(UMLField in);
	int AddMethod(UMLMethod in);
	const std::string & ReturnTitle() const;
	std::string ReturnFields();
	std::string ReturnMethods();
	std::vector<const char *> ReturnMethodsgui();
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
	
	int EditMethod(std::string oldName, std::string newName);
	int EditField(std::string oldName, std::string newName);
	int DeleteMethod(std::string in);
	int DeleteField(std::string in);

	int EditFieldT(std::string fieldName, std::string newType);
	int EditFieldV(std::string fieldName, int vis);
	int EditMethodT(std::string methodName, std::string newType);
	int EditMethodV(std::string methodName, int vis);

	int AddParameter(std::string method_title, std::string param_name);
	int EditParameterName(std::string method_title, std::string old_param_name, std::string new_param_name);
	int EditParameterType(std::string method_title, std::string param_name, std::string type);
	int EditParameterSetDefaultValue(std::string method_title, std::string param_name, std::string value);
	int EditParameterClearDefaultValue(std::string method_title, std::string param_name);
	int DeleteParameter(std::string method_title, std::string param_name);

	//these methods dont belong here; should be eventually moved
	size_t GetLargestStringSize();
	std::string ReturnFieldsREPL();
	std::string ReturnMethodsREPL();
	std::string ToStringREPL();
	std::string ReturnRelationshipsREPL();
	
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
};