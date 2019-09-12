#pragma once

#include <string>
#include <vector>

#define UMLFieldVisibilityPublic 1
#define UMLFieldVisibilityPrivate 2

struct UMLField
{
	UMLField(std::string in_name, std::string in_type, int in_Visibility)
	{
		name = in_name;
		type = in_type;
		visibility = in_Visibility;
	}
	std::string name;
	std::string type;
	int visibility;
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
};

struct UMLMethod
{
	UMLMethod(std::string in_name, std::string in_type, std::vector<std::string> in_parameters, int in_Visibility)
	{
		name = in_name;
		return_type = in_type;
		parameters = in_parameters;
		visibility = in_Visibility;
	}
	std::string name;
	std::string return_type;
	std::vector<std::string> parameters;
	int visibility;
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
private:
	std::string title;
	std::vector<UMLField> fields;
	std::vector<UMLMethod> methods;
};