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

std::string UMLObject::ReturnRelationships()
{
	std::string out;
	for (auto a : relationships)
	{
		out += a.ToString() + ", ";
	}
	return out;
}

void UMLObject::AddRelationship(UMLRelationship in)
{
	relationships.push_back(in);
}

size_t UMLObject::GetIndexRelationshipWith(std::string in)
{
	size_t out = -1;
	for (unsigned int i = 0; i < relationships.size(); i++)
	{
		if (relationships[i].GetObject() == in)
		{
			out = i;
			break;
		}
	}
	return out;
}

void UMLObject::UpdateRelationship(size_t index, int type)
{
	relationships[index].SetType(type);
}

void UMLObject::DeleteRelationship(size_t index)
{
	relationships.erase(relationships.begin() + index);
}

std::vector<UMLField> UMLObject::ReturnFieldsRaw()
{
	return fields;
}

std::vector<UMLMethod> UMLObject::ReturnMethodsRaw()
{
	return methods;
}

std::vector<UMLRelationship> UMLObject::ReturnRelationshipsRaw()
{
	return relationships;
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
	std::vector<std::string> out;
	for (auto i : parameters) out.push_back(i.ToString());
	return out;
}

std::vector<UMLParameter> UMLMethod::ReturnParametersRaw()
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

bool UMLMethod::AddParameter(UMLParameter in)
{
	for (auto i : parameters)
	{
		if (in.name == i.name) return false;
	}
	parameters.push_back(in);
	return true;
}

bool UMLObject::EditMethod(std::string oldName, std::string newName)
{
  for (auto i : methods)
  {
    if (i.ReturnName() == newName) 
      return false;
  }
  for (auto i : methods)
  {
    if (i.ReturnName() == oldName)
    {
      i.SetName(newName);
      return true;
    }
  }
  return false;
}

bool UMLObject::EditField(std::string oldName, std::string newName)
{
  for (auto i : fields)
  {
    if (i.ReturnName() == newName)
      return false;
  }
  for (auto i : fields)
  {
    if (i.ReturnName() == oldName)
    {
      i.SetName(newName);
      return true;
    }
  }
  return false;
}

bool UMLObject::DeleteMethod(std::string in)
{
  unsigned int count = 0;
  for (auto i : methods)
  {
    if (i.ReturnName() == in)
    {
      methods.erase(methods.begin() + count);
      return true;
    }
    ++count;
  }
  return false;
}