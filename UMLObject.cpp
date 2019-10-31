#include "UMLObject.h"
//initialize object
UMLObject::UMLObject()
{
}
//creates copy of title field methods
UMLObject::UMLObject(UMLObject* copy)
{
	title = copy->title;
	fields = copy->fields;
	methods = copy->methods;
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

int UMLObject::GetLargestStringSize()
{
	int maxSize = 0;
	int temp = 0;

	// Check title string size
	temp = title.size();
	if (temp > maxSize)
		maxSize = temp;

		// Check field string sizes
		for (auto f : fields)
		{
			temp = f.ReturnName().size();

			if (temp > maxSize)
				maxSize = temp;
		}
	
	// Check method string sizes
	for (auto m : methods)
	{
		temp = m.ReturnName().size();

		if (temp > maxSize)
			maxSize = temp;
	}

	//maxSize += 2;

	return maxSize;
}

std::string UMLObject::ReturnFieldsPretty()
{
	std::string out;
	int temp = 0;
	int addSpace = 0;

	for (auto a : fields)
	{
		temp = a.ReturnName().size();
		addSpace = GetLargestStringSize() - temp;

		out += "\xB3 - " + a.ReturnName();

		for (int x = 0; x < addSpace; ++x)
		out += " ";

		out += " \xB3\n";
	}

	return out;
}

std::string UMLObject::ReturnMethodsPretty()
{
	std::string out;
	int temp = 0;
	int addSpace = 0;

	for (auto a : methods)
	{
		temp = a.ReturnName().size();
		addSpace = GetLargestStringSize() - temp;

		out += "\xB3 + " + a.ReturnName();

		for (int x = 0; x < addSpace; ++x)
		out += " ";

		out += " \xB3\n";
	}

	return out;
}

std::string UMLObject::ReturnRelationshipsPretty()
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
			out += "\t\t" + x.ToStringPretty() + "\n";
	}

	if (Co.size() != 0)
	{
		out += "\tComposition:\n";

		for (auto x : Co)
			out += "\t\t" + x.ToStringPretty() + "\n";
	}

	if (Ge.size() != 0)
	{
		out += "\tGeneralization:\n";

		for (auto x : Ge)
			out += "\t\t" + x.ToStringPretty() + "\n";
	}

	if (Re.size() != 0)
	{
		out += "\tRealization:\n";

		for (auto x : Re)
			out += "\t\t" + x.ToStringPretty() + "\n";
	}

	


	return out;
}

std::string UMLObject::ToStringPretty()
{
	std::string out;
	std::string breakLine;
	int temp = 0;
	int addSpace = 0;

	// ==========================================================================================

	// ┌────────────────────┐

	out += "\xDA";

	for (int x = 0; x < GetLargestStringSize() + 4; ++x)
		out += "\xC4";

	out += "\xBF\n";

	// ==========================================================================================

	// │ Title              │

	temp = title.size();
	addSpace = GetLargestStringSize() - temp;

	out += "\xB3 " + ReturnTitle();

	for (int x = 0; x < addSpace + 2; ++x)
		out += " ";

	out += " \xB3\n";

	// ==========================================================================================

	// ├────────────────────┤

	breakLine += "\xC3";

	for (int x = 0; x < GetLargestStringSize() + 4; ++x)
		breakLine += "\xC4";

	breakLine += "\xB4\n";

	out += breakLine;

	// ==========================================================================================

	// Print fields
	out += ReturnFieldsPretty();

	// ==========================================================================================

	// ├────────────────────┤

	out += breakLine;

	// ==========================================================================================

	// Print methods
	out += ReturnMethodsPretty();

	// ==========================================================================================

	// └────────────────────┘

	out += "\xC0";

	for (int x = 0; x < GetLargestStringSize() + 4; ++x)
		out += "\xC4";

	out += "\xD9";

	// ==========================================================================================

	// Print relationships
	out += ReturnRelationshipsPretty();

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
//makes field private from user
UMLField::UMLField()
{
	visibility = UMLFieldVisibilityPrivate;
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
//makes visibility private from user
UMLMethod::UMLMethod()
{
	visibility = UMLFieldVisibilityPrivate;
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