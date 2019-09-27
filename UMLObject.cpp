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

UMLField::UMLField()
{
	visibility = UMLFieldVisibilityPrivate;
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

void UMLField::SetName(std::string in)
{
	name = in;
}

void UMLField::SetReturnType(std::string in)
{
	type = in;
}

void UMLField::SetVisibility(int in)
{
	visibility = in;
}

UMLMethod::UMLMethod()
{
	visibility = UMLFieldVisibilityPrivate;
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

void UMLMethod::SetName(std::string in)
{
	name = in;
}

void UMLMethod::SetReturnType(std::string in)
{
	return_type = in;
}

void UMLMethod::SetVisibility(int in)
{
	visibility = in;
}

void UMLMethod::SetParameters(std::vector<std::string> in)
{
	parameters = in;
}
