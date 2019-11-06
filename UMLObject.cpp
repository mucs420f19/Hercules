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
bool UMLObject::AddField(UMLField in)
{
	for (auto i : fields)
	{
		if (i.ReturnName() == in.ReturnName())
		{
			return false;
		}
	}
	fields.push_back(in);
	return true;
}
//adds the methods to the vector
bool UMLObject::AddMethod(UMLMethod in)
{
	for (auto i : methods)
	{
		if (i.ReturnName() == in.ReturnName())
		{
			return false;
		}
	}
	methods.push_back(in);
	return true;
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
	std::vector<UMLRelationship> Ag;
	std::vector<UMLRelationship> Co;
	std::vector<UMLRelationship> Ge;
	std::vector<UMLRelationship> Re;
  	
	out += "\n" + ReturnTitle() + " Relationships:\n";

	for (auto r : relationships)	
	{
		if (r.GetType() == RelationshipAggregation)
			Ag.push_back(r);

		if (r.GetType() == RelationshipComposition)
			Co.push_back(r);

		if (r.GetType() == RelationshipGeneralization)
			Ge.push_back(r);

		if (r.GetType() == RelationshipRealization)
			Re.push_back(r);
	}

	if (Ag.size() != 0)
	{
		out += "\tAggregation:\n";

		for (auto x : Ag)
			out += "\t\t" + x.ToStringREPL() + "\n";
	}

	if (Co.size() != 0)
	{
		out += "\tComposition:\n";

		for (auto x : Co)
			out += "\t\t" + x.ToStringREPL() + "\n";
	}

	if (Ge.size() != 0)
	{
		out += "\tGeneralization:\n";

		for (auto x : Ge)
			out += "\t\t" + x.ToStringREPL() + "\n";
	}

	if (Re.size() != 0)
	{
		out += "\tRealization:\n";

		for (auto x : Re)
			out += "\t\t" + x.ToStringREPL() + "\n";
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
//returns parameters from vector
std::vector<std::string> UMLMethod::ReturnParameters()
{
	std::vector<std::string> out;
	for (auto i : parameters) out.push_back(i.ToString());
	return out;
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
bool UMLMethod::AddParameter(UMLParameter in)
{
	for (auto i : parameters)
	{
		if (in.name == i.name) return false;
	}
	parameters.push_back(in);
	return true;
}
//replaces old name of the method to the new one
bool UMLObject::EditMethod(std::string oldName, std::string newName)
{
  for (auto &i : methods)
  {
    if (i.ReturnName() == newName) 
      return false;
  }
  for (auto &i : methods)
  {
    if (i.ReturnName() == oldName)
    {
      i.SetName(newName);
      return true;
    }
  }
  return false;
}
//replaces old name of the field to the new one
bool UMLObject::EditField(std::string oldName, std::string newName)
{
  for (auto &i : fields)
  {
    if (i.ReturnName() == newName)
      return false;
  }
  for (auto &i : fields)
  {
    if (i.ReturnName() == oldName)
    {
      i.SetName(newName);
      return true;
    }
  }
  return false;
}
//deletes the method
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
//deletes the field
bool UMLObject::DeleteField(std::string in)
{
  unsigned int count = 0;
  for (auto i : fields)
  {
    if (i.ReturnName() == in)
    {
      fields.erase(fields.begin() + count);
      return true;
    }
    ++count;
  }
  return false;
}

bool UMLObject::EditFieldT(std::string fieldName, std::string newType)
{
	for (auto &i : fields)
	{
		if (i.ReturnName() == fieldName)
		{
			i.SetReturnType(newType);

			return true;
		}
	}

	return false;
}

bool UMLObject::EditFieldV(std::string fieldName, int vis)
{
	for (auto &i : fields)
	{
		if (i.ReturnName() == fieldName)
		{
			i.SetVisibility(vis);

			return true;
		}
	}

	return false;
}

bool UMLObject::EditMethodT(std::string methodName, std::string newType)
{
	for (auto &i : methods)
	{
		if (i.ReturnName() == methodName)
		{
			i.SetReturnType(newType);

			return true;
		}
	}

	return false;
}

bool UMLObject::EditMethodV(std::string methodName, int vis)
{
	for (auto &i : methods)
	{
		if (i.ReturnName() == methodName)
		{
			i.SetVisibility(vis);

			return true;
		}
	}

	return false;
}

bool UMLObject::DoesMethodExist(std::string in)
{
  for (auto i : methods)
  {
    if (i.ReturnName() == in)
      return true;
  }
  return false;
}

bool UMLObject::DoesFieldExist(std::string in)
{
  for (auto i : fields)
  {
    if (i.ReturnName() == in)
      return true;
  }
  return false;
}