#include "UMLObject.h"
//initialize object
UMLObject::UMLObject()
{
}
//title is the input of the user
void UMLObject::SetTitle(std::string in)
{
	title = in;
}
//adds the fields into the vector
int UMLObject::AddField(UMLField in)
{
	for (auto i : fields)
	{
		if (i.ReturnName() == in.ReturnName())
		{
			return ElementAlreadyExists;
		}
	}
	fields.push_back(in);
	return ElementSuccess;
}
//adds the methods to the vector
int UMLObject::AddMethod(UMLMethod in)
{
	for (auto i : methods)
	{
		if (i.ReturnName() == in.ReturnName())
		{
			return ElementAlreadyExists;
		}
	}
	methods.push_back(in);
	return ElementSuccess;
}
//returns title of object
const std::string & UMLObject::ReturnTitle() const
{
	return title;
}
//concatenates the fields 
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
//returns method of the object
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

std::vector<const char *> UMLObject::ReturnMethodsgui()
{
    std::vector<const char *> out;
    for (auto& i : methods)
    {
        out.push_back(i.ToString().c_str());
    }
    return out;
}

//concatenates all the objects return types
std::string UMLObject::ToString()
{
	return "Title: {" + ReturnTitle() + "}, Fields:" + ReturnFields() + ", Methods: " + ReturnMethods() + ", Relationships: " + ReturnRelationships();
	
}
int UMLObject::GetXPosition()
{
	return x;
}
int UMLObject::GetYPosition()
{
	return y;
}
void UMLObject::SetXPosition(int in)
{
	x = in;
}
void UMLObject::SetYPosition(int in)
{
	y = in;
}

size_t UMLObject::GetLargestStringSize()
{
	size_t maxSize = 0;
	size_t temp = 0;

	// Check title string size
	temp = title.size();
	if (temp > maxSize)
		maxSize = temp;

	// Check field string sizes
	for (auto f : fields)
	{
		// For visibility and space
		temp = 2;

		temp += f.ReturnName().size();

		// For type and : space
		temp += f.ReturnType().size() + 3;

		if (temp > maxSize)
			maxSize = temp;
	}
	
	// Check method string sizes
	for (auto m : methods)
	{
		// For visibility and space
		temp = 2;

		temp += m.ReturnName().size();

		// For type and : space
		temp += m.ReturnType().size() + 3;

		if (temp > maxSize)
			maxSize = temp;
	}

	return maxSize;
}

std::string UMLObject::ReturnFieldsREPL()
{
	std::string out;
	size_t temp = 0;
	size_t addSpace = 0;

	for (auto a : fields)
	{
		temp = 5 + a.ReturnName().size() + a.ReturnType().size();
		addSpace = GetLargestStringSize() - temp;

		out += "\xB3 ";

		if (a.ReturnVisibility() == 1)
			out += "+ ";
		else if (a.ReturnVisibility() == 2)
			out += "- ";
		else if (a.ReturnVisibility() == 3)
			out += "# ";

		out += a.ReturnName() + " : " + a.ReturnType();

		for (size_t x = 0; x < addSpace; ++x)
			out += " ";

		out += " \xB3\n";
	}

	return out;
}

std::string UMLObject::ReturnMethodsREPL()
{
	std::string out;
	size_t temp = 0;
	size_t addSpace = 0;

	for (auto a : methods)
	{
		temp = 5 + a.ReturnName().size() + a.ReturnType().size();
		addSpace = GetLargestStringSize() - temp;

		out += "\xB3 ";

		if (a.ReturnVisibility() == 1)
			out += "+ ";
		else if (a.ReturnVisibility() == 2)
			out += "- ";
		else if (a.ReturnVisibility() == 3)
			out += "# ";

		out += a.ReturnName() + " : " + a.ReturnType();

		for (size_t x = 0; x < addSpace; ++x)
			out += " ";

		out += " \xB3\n";
	}

	return out;
}

std::string UMLObject::ReturnRelationshipsREPL()
{
	std::string out;
  	
	out += "\n" + ReturnTitle() + " Relationships:\n";

	for (auto a : relationships)
	{
		out += a.ToString();
	}

	return out;
}

std::string UMLObject::ToStringREPL()
{
	std::string out;
	std::string breakLine;
	size_t temp = 0;
	size_t addSpace = 0;

	// ==========================================================================================

	// ┌────────────────────┐

	out += "\xDA";

	for (size_t x = 0; x < GetLargestStringSize() + 2; ++x)
		out += "\xC4";

	out += "\xBF\n";

	// ==========================================================================================

	// │ Title              │

	temp = title.size();
	addSpace = GetLargestStringSize() - temp;

	out += "\xB3 " + ReturnTitle();

	for (size_t x = 0; x < addSpace; ++x)
		out += " ";

	out += " \xB3\n";

	// ==========================================================================================

	// ├────────────────────┤

	breakLine += "\xC3";

	for (size_t x = 0; x < GetLargestStringSize() + 2; ++x)
		breakLine += "\xC4";

	breakLine += "\xB4\n";

	out += breakLine;

	// ==========================================================================================

	// Print fields
	out += ReturnFieldsREPL();

	// ==========================================================================================

	// ├────────────────────┤

	out += breakLine;

	// ==========================================================================================

	// Print methods
	out += ReturnMethodsREPL();

	// ==========================================================================================

	// └────────────────────┘

	out += "\xC0";

	for (size_t x = 0; x < GetLargestStringSize() + 2; ++x)
		out += "\xC4";

	out += "\xD9";

	// ==========================================================================================

	// Print relationships
	out += ReturnRelationshipsREPL();

	// ==========================================================================================

	out += "\n";
	return out;
}

//iterates to return the relationship
std::string UMLObject::ReturnRelationships()
{
	std::string out;
  out += "{";
	for (auto a : relationships)
	{
		out += a.ToString() + ", ";
	}
	out += "}";
	return out;
}
//adds relationship to the vector
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
UMLRelationship * UMLObject::GetRelationshipWith(std::string in)
{
	UMLRelationship * out = 0;
	for (unsigned int i = 0; i < relationships.size(); i++)
	{
		if (relationships[i].GetObject() == in)
		{
			out = &relationships[i];
			break;
		}
	}
	return out;
}
//updates corrisponding relationship
void UMLObject::UpdateRelationship(size_t index, int type, int quantifier)
{
	relationships[index].SetType(type);
	relationships[index].SetQuantifier(quantifier);
}
//deletes corrisponding relationship
void UMLObject::DeleteRelationship(std::string in)
{
	if (GetIndexRelationshipWith(in) != -1)
	{
		relationships.erase(relationships.begin() + GetIndexRelationshipWith(in));
	}
}
//returns fields unformatted
std::vector<UMLField> UMLObject::ReturnFieldsRaw()
{
	return fields;
}
//returns methods unformatted
std::vector<UMLMethod> UMLObject::ReturnMethodsRaw()
{
	return methods;
}
//returns relationships unformatted
std::vector<UMLRelationship> UMLObject::ReturnRelationshipsRaw()
{
	return relationships;
}
size_t UMLObject::RelationshipsSize()
{
	return relationships.size();
}
//returns name of the field
std::string UMLField::ReturnName()
{
	return name;
}
// returns type of field
std::string UMLField::ReturnType()
{
	return type;
}
//returns field visibility back to the user
int UMLField::ReturnVisibility()
{
	return visibility;
}
//sets the name from user
void UMLField::SetName(std::string in)
{
	name = in;
}
//sets the type from user
void UMLField::SetReturnType(std::string in)
{
	type = in;
}
//sets the visibility from the user
void UMLField::SetVisibility(int in)
{
	visibility = in;
}
// returns name from method
std::string UMLMethod::ReturnName()
{
	return name;
}
// returns the type
std::string UMLMethod::ReturnType()
{
	return return_type;
}
//returns parameters unformatted
std::vector<UMLParameter> UMLMethod::ReturnParametersRaw()
{
	return parameters;
}
//returns visibility from method
int UMLMethod::ReturnVisibility()
{
	return visibility;
}
// sets the name of method from user
void UMLMethod::SetName(std::string in)
{
	name = in;
}
//returns the type of method from user
void UMLMethod::SetReturnType(std::string in)
{
	return_type = in;
}
//gives visibility back to the user
void UMLMethod::SetVisibility(int in)
{
	visibility = in;
}
//pushes parameters to the vector
int UMLMethod::AddParameter(UMLParameter in)
{
	for (auto i : parameters)
	{
		if (in.name == i.name) return ElementAlreadyExists;
	}
	parameters.push_back(in);
	return ElementSuccess;
}

int UMLMethod::EditParamName(std::string old, std::string newn)
{
	for (auto i : parameters)
	{
		if (newn == i.name) return ElementAlreadyExists;
	}
	for (auto & i : parameters)
	{
		if (old == i.name)
		{
			i.name = newn;
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}

int UMLMethod::EditParamType(std::string name, std::string type)
{
	for (auto& i : parameters)
	{
		if (name == i.name)
		{
			i.type = type;
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}

int UMLMethod::SetParamDefaultValue(std::string name, std::string value)
{
	for (auto& i : parameters)
	{
		if (name == i.name)
		{
			i.deflt = value;
			i.opt = true;
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}

int UMLMethod::ClearParamDefaultValue(std::string name)
{
	for (auto& i : parameters)
	{
		if (name == i.name)
		{
			i.deflt = "";
			i.opt = false;
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}

int UMLMethod::DeleteParameter(std::string name)
{
	unsigned int count = 0;
	for (auto i : parameters)
	{
		if (i.ReturnName() == name)
		{
			parameters.erase(parameters.begin() + count);
			return ElementSuccess;
		}
		++count;
	}
	return ElementDoesntExist;
}

//replaces old name of the method to the new one
int UMLObject::EditMethod(std::string oldName, std::string newName)
{
	for (auto& i : methods)
	{
		if (i.ReturnName() == newName)
			return ElementAlreadyExists;
	}
	for (auto& i : methods)
	{
		if (i.ReturnName() == oldName)
		{
			i.SetName(newName);
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}

//replaces old name of the field to the new one
int UMLObject::EditField(std::string oldName, std::string newName)
{
	for (auto& i : fields)
	{
		if (i.ReturnName() == newName)
			return ElementAlreadyExists;
	}
	for (auto& i : fields)
	{
		if (i.ReturnName() == oldName)
		{
			i.SetName(newName);
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}

//deletes the method
int UMLObject::DeleteMethod(std::string in)
{
	unsigned int count = 0;
	for (auto i : methods)
	{
		if (i.ReturnName() == in)
		{
			methods.erase(methods.begin() + count);
			return ElementSuccess;
		}
		++count;
	}
	return ElementDoesntExist;
}

//deletes the field
int UMLObject::DeleteField(std::string in)
{
	unsigned int count = 0;
	for (auto i : fields)
	{
		if (i.ReturnName() == in)
		{
			fields.erase(fields.begin() + count);
			return ElementSuccess;
		}
		++count;
	}
	return ElementDoesntExist;
}

int UMLObject::EditFieldT(std::string fieldName, std::string newType)
{
	for (auto &i : fields)
	{
		if (i.ReturnName() == fieldName)
		{
			i.SetReturnType(newType);
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}

int UMLObject::EditFieldV(std::string fieldName, int vis)
{
	for (auto &i : fields)
	{
		if (i.ReturnName() == fieldName)
		{
			i.SetVisibility(vis);
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}

int UMLObject::EditMethodT(std::string methodName, std::string newType)
{
	for (auto &i : methods)
	{
		if (i.ReturnName() == methodName)
		{
			i.SetReturnType(newType);
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}

int UMLObject::EditMethodV(std::string methodName, int vis)
{
	for (auto &i : methods)
	{
		if (i.ReturnName() == methodName)
		{
			i.SetVisibility(vis);
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}

int UMLObject::AddParameter(std::string method_title, std::string param_name)
{
	for (auto& i : methods)
	{
		if (i.ReturnName() == method_title)
		{
			return i.AddParameter({ "int", param_name });
		}
	}
	return ElementDoesntExist;
}

int UMLObject::EditParameterName(std::string method_title, std::string old_param_name, std::string new_param_name)
{
	for (auto& i : methods)
	{
		if (i.ReturnName() == method_title)
		{
			return i.EditParamName(old_param_name, new_param_name);
		}
	}
	return ElementDoesntExist;
}

int UMLObject::EditParameterType(std::string method_title, std::string param_name, std::string type)
{
	for (auto& i : methods)
	{
		if (i.ReturnName() == method_title)
		{
			return i.EditParamType(param_name, type);
		}
	}
	return ElementDoesntExist;
}

int UMLObject::EditParameterSetDefaultValue(std::string method_title, std::string param_name, std::string value)
{
	for (auto& i : methods)
	{
		if (i.ReturnName() == method_title)
		{
			return i.SetParamDefaultValue(param_name, value);
		}
	}
	return ElementDoesntExist;
}

int UMLObject::EditParameterClearDefaultValue(std::string method_title, std::string param_name)
{
	for (auto& i : methods)
	{
		if (i.ReturnName() == method_title)
		{
			return i.ClearParamDefaultValue(param_name);
		}
	}
	return ElementDoesntExist;
}

int UMLObject::DeleteParameter(std::string method_title, std::string param_name)
{
	for (auto& i : methods)
	{
		if (i.ReturnName() == method_title)
		{
			return i.DeleteParameter(param_name);
		}
	}
	return ElementDoesntExist;
}
