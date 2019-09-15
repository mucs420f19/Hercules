#include "UMLObject.h"

UMLObject::UMLObject()
{
}

UMLObject::UMLObject(UMLObject* copy)
{
	title = copy->title;
	fields = copy->fields;
	methods = copy->methods;
}

void UMLObject::SetTitle(std::string in)
{
	title = in;
}

void UMLObject::AddField(UMLField in)
{
	fields.push_back(in);
}

void UMLObject::AddMethod(UMLMethod in)
{
	methods.push_back(in);
}

std::string UMLObject::ReturnTitle()
{
	return title;
}

std::string UMLObject::ReturnFields()
{
	std::string out;
	out += "{";
	for (auto a : fields)
	{
		out += a.ToString() + ", ";
	}
	out += "}";
	return out;
}

std::string UMLObject::ReturnMethods()
{
	std::string out;
	out += "{";
	for (auto a : methods)
	{
		out += a.ToString() + ", ";
	}
	out += "}";
	return out;
}

std::string UMLObject::ToString()
{
	return "Title: {" + ReturnTitle() + "}, Fields:" + ReturnFields() + ", Methods: " + ReturnMethods();
}

std::vector<UMLField> UMLObject::ReturnFieldsRaw()
{
	return fields;
}

std::vector<UMLMethod> UMLObject::ReturnMethodsRaw()
{
	return methods;
}

std::string UMLField::ReturnName()
{
	return name;
}

std::string UMLField::ReturnType()
{
	return type;
}

int UMLField::ReturnVisibility()
{
	return visibility;
}

std::string UMLMethod::ReturnName()
{
	return name;
}

std::string UMLMethod::ReturnType()
{
	return return_type;
}

std::vector<std::string> UMLMethod::ReturnParameters()
{
	return parameters;
}

int UMLMethod::ReturnVisibility()
{
	return visibility;
}
