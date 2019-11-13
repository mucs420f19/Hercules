#include "UMLObjectsHolder.h"
// Creates a constructor
UMLObjectsHolder::UMLObjectsHolder()
{
}

bool UMLObjectsHolder::IsTitleUnique(std::string in)
{
	//we will not accept an empty string as a title
	if (in == "") return false;
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == in) return false;
	}
	return true;
}
// Destructor
UMLObjectsHolder::~UMLObjectsHolder()
{
	ClearProject();
}

void UMLObjectsHolder::ClearProject()
{
	for (auto i : UMLObjects_holder)
		delete i;
  
  UMLObjects_holder.clear();
}
// creates a new class with unique title
int UMLObjectsHolder::CreateNewClass(std::string title)
{
	if (!IsTitleUnique(title)) return ClassAlreadyExists;
	UMLObject* a = new UMLObject();
	a->SetTitle(title);
	UMLObjects_holder.push_back(a);
	return ElementSuccess;
}
// prints the title of the class
void UMLObjectsHolder::UMLObjectPrintTitles()
{
	int count = 1;

	for (auto i : UMLObjects_holder)
	{
		std::cout << count << ". " << i->ReturnTitle() << std::endl;
		++count;
	}
}
//prints contents of holder
void UMLObjectsHolder::UMLObjectPrintContents()
{
	for (auto i : UMLObjects_holder)
		std::cout << i->ToString() << std::endl;
}
//prints the content of the repl
void UMLObjectsHolder::UMLObjectPrintContentsREPL()
{
	for (auto i : UMLObjects_holder)
		std::cout << i->ToStringREPL() << std::endl;
}
// returns a vector with all content	
std::vector<std::string> UMLObjectsHolder::ReturnAll()
{
	std::vector<std::string> out;
	for (auto  i : UMLObjects_holder)
	{
		out.push_back(i->ToString());
	}
	return out;
}
// returns titles from vector	
std::vector<std::string> UMLObjectsHolder::ReturnTitles()
{
	std::vector<std::string> out;
	for (auto& i : UMLObjects_holder)
	{
		out.push_back(i->ReturnTitle());
	}
	return out;
}
// returns fields from the vector
std::vector<std::string> UMLObjectsHolder::ReturnFields()
{
	std::vector<std::string> out;
	for (auto& i : UMLObjects_holder)
	{
		out.push_back(i->ReturnFields());
	}
	return out;
}
// returns mehods from the vector
std::vector<std::string> UMLObjectsHolder::ReturnMethods()
{
	std::vector<std::string> out;
	for (auto& i : UMLObjects_holder)
	{
		out.push_back(i->ReturnMethods());
	}
	return out;
}
// returns relationships from the vector
std::vector<std::string> UMLObjectsHolder::ReturnRelationships()
{
	std::vector<std::string> out;
	for (auto& i : UMLObjects_holder)
	{
		out.push_back(i->ReturnRelationships());
	}
	return out;
}
// Returns the pointer that points to the holder
std::vector<UMLObject*> UMLObjectsHolder::ReturnPtrToVector()
{
	return UMLObjects_holder;
}
//grabs the contnents of the holder into the object
void UMLObjectsHolder::AddUMLObject(UMLObject* in)
{
	if (in != NULL) UMLObjects_holder.push_back(in);
}
// deletes the class based off title
int UMLObjectsHolder::DeleteClass(std::string title)
{
	std::vector<UMLObject*> UMLObjects_holder_temp = UMLObjects_holder;
	for (unsigned int i = 0; i < UMLObjects_holder.size(); i++)
	{
		if (UMLObjects_holder[i]->ReturnTitle() == title)
		{
			for (auto j : UMLObjects_holder_temp)
			{
				if (j->GetRelationshipWith(title))
				{
					//if the object we are deleting has a child and it is Composition relationship
					// and the child has no other relationships..... delete the child as well
					if (j->GetRelationshipWith(title)->type == RelationshipComposition && j->GetRelationshipWith(title)->parent == 0 && j->RelationshipsSize() == 1)
					{
						DeleteClass(j->ReturnTitle());
					}
					j->DeleteRelationship(title);
				}
			}
		  
			UMLObjects_holder.erase(UMLObjects_holder.begin() + i);
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}
// returns the size of the object
size_t UMLObjectsHolder::Size()
{
	return UMLObjects_holder.size();
}
// Allows to edit based off the title 
int UMLObjectsHolder::EditClassTitle(std::string new_title, std::string old_title)
{
	if (!IsTitleUnique(new_title)) return ElementAlreadyExists;
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == old_title)
		{
			i->SetTitle(new_title);
			return ElementSuccess;
		}
	}
	return ElementDoesntExist;
}
// Gets visibility on the stromh with its respected privacy
int UMLObjectsHolder::GetVisibilityTypeFromString(std::string in)
{
	int result = 0;
	if (in.size() == 0) return result;
	std::transform(std::cbegin(in), std::cend(in), std::begin(in), [](const unsigned char i) { return std::tolower(i); });
	if (in == "private" || in[0] == '-') result = UMLFieldVisibilityPrivate;
	else if (in == "public" || in[0] == '+') result = UMLFieldVisibilityPublic;
	else if (in == "protected" || in[0] == '#') result = UMLFieldVisibilityProtected;
	return result;
}
// adds a field with visibilities 
int UMLObjectsHolder::AddField(std::string class_title, std::string field_title, std::string type, std::string visibility)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	if (!GetVisibilityTypeFromString(visibility)) return InvalidVisibility;
	int result = c->AddField(UMLField(field_title, type, GetVisibilityTypeFromString(visibility)));
	if (result != ElementSuccess) return result;
	if (IsFieldReferringToExistingClass(type) != "")
	{
		AddRelationship(class_title, IsFieldReferringToExistingClass(type), "composition", "one", "many");
	}
	return result;
}
//allows to edit field name of class
int UMLObjectsHolder::EditFieldName(std::string class_title, std::string old_field_title, std::string new_field_title)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditField(old_field_title, new_field_title);
}
// allows to edit the field type of class
int UMLObjectsHolder::EditFieldType(std::string class_title, std::string field_title, std::string type)
{
	UMLObject* c = GetUMLObject(class_title);
	if (c == 0) return ClassDoesntExist;
	int result = c->EditFieldT(field_title, type);
	if (result != ElementSuccess) return result;
	if (IsFieldReferringToExistingClass(type) != "")
	{
		AddRelationship(class_title, IsFieldReferringToExistingClass(type), "composition", "one", "many");
	}
	return result;
}
// edits field with respect to visibility 
int UMLObjectsHolder::EditFieldVisibility(std::string class_title, std::string field_title, std::string visibility)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	if (!GetVisibilityTypeFromString(visibility)) return InvalidVisibility;
	return c->EditFieldV(field_title, GetVisibilityTypeFromString(visibility));
}
// deletes the field 
int UMLObjectsHolder::DeleteField(std::string class_title, std::string field_title)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->DeleteField(field_title);
}
// adds method with respect to its visibility 
int UMLObjectsHolder::AddMethod(std::string class_title, std::string method_title, std::string type, std::string visibility)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	if (!GetVisibilityTypeFromString(visibility)) return InvalidVisibility;
	return c->AddMethod(UMLMethod(method_title, type, {}, GetVisibilityTypeFromString(visibility)));
}
// edits method name with respect to visibility
int UMLObjectsHolder::EditMethodName(std::string class_title, std::string old_method_name, std::string new_method_name)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditMethod(old_method_name, new_method_name);
}
// edits the methods return type of the class
int UMLObjectsHolder::EditMethodReturnType(std::string class_title, std::string method_name, std::string type)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;

	return c->EditMethodT(method_name, type);
}
// edits method title with respect to visibility
int UMLObjectsHolder::EditMethodVisibility(std::string class_title, std::string method_title, std::string visibility)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	if (!GetVisibilityTypeFromString(visibility)) return InvalidVisibility;
	return c->EditMethodV(method_title, GetVisibilityTypeFromString(visibility));
}
// deletes the method
int UMLObjectsHolder::DeleteMethod(std::string class_title, std::string method_title)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->DeleteMethod(method_title);
}
// adds parameter to title 
int UMLObjectsHolder::AddParameter(std::string class_title, std::string method_title, std::string param_name)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->AddParameter(method_title, param_name);
}
// allows paramete name to be edited 
int UMLObjectsHolder::EditParameterName(std::string class_title, std::string method_title, std::string old_param_name, std::string new_param_name)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditParameterName(method_title, old_param_name, new_param_name);
}
// allows parameter type to be edited
int UMLObjectsHolder::EditParameterType(std::string class_title, std::string method_title, std::string param_name, std::string type)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditParameterType(method_title, param_name, type);
}
// allows parameters default value to be edited
int UMLObjectsHolder::EditParameterSetDefaultValue(std::string class_title, std::string method_title, std::string param_name, std::string value)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditParameterSetDefaultValue(method_title, param_name, value);
}
// allows to clear the default value of the parameter
int UMLObjectsHolder::EditParameterClearDefaultValue(std::string class_title, std::string method_title, std::string param_name)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditParameterClearDefaultValue(method_title, param_name);
}
// deletes parameter
int UMLObjectsHolder::DeleteParameter(std::string class_title, std::string method_title, std::string param_name)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->DeleteParameter(method_title, param_name);
}
// adds relationship between parent and child
int UMLObjectsHolder::AddRelationship(std::string parent, std::string child, std::string type, std::string quantifier1, std::string quantifier2)
{
	UMLObject* p, * c;

	p = GetUMLObject(parent);
	c = GetUMLObject(child);

	if (p == 0 || c == 0) return ClassDoesntExist;
	if (!GetQuantifierFromString(quantifier1) || !GetQuantifierFromString(quantifier2)) return InvalidQuantifier;
	if (!GetRelationshipTypeFromString(type)) return InvalidRelationshipType;
	if (p->GetIndexRelationshipWith(child) != -1 || c->GetIndexRelationshipWith(parent) != -1) return RelationshipAlreadyExists;

	p->AddRelationship({ GetRelationshipTypeFromString(type), GetQuantifierFromString(quantifier1), c, p, true});
	c->AddRelationship({ GetRelationshipTypeFromString(type), GetQuantifierFromString(quantifier2), p, c, false});

	return ElementSuccess;
}
// allows to edit relationships between parent and child
int UMLObjectsHolder::EditRelationship(std::string parent, std::string child, std::string type, std::string quantifier1, std::string quantifier2)
{
	UMLObject* p, * c;

	p = GetUMLObject(parent);
	c = GetUMLObject(child);

	if (p == 0 || c == 0) return ClassDoesntExist;
	if (!GetQuantifierFromString(quantifier1) || !GetQuantifierFromString(quantifier2)) return InvalidQuantifier;
	if (!GetRelationshipTypeFromString(type)) return InvalidRelationshipType;
	if (p->GetIndexRelationshipWith(child) == -1 || c->GetIndexRelationshipWith(parent) == -1) return RelationshipDoesNotExist;

	p->UpdateRelationship(p->GetIndexRelationshipWith(child), GetRelationshipTypeFromString(type), GetQuantifierFromString(quantifier1));
	c->UpdateRelationship(c->GetIndexRelationshipWith(parent), GetRelationshipTypeFromString(type), GetQuantifierFromString(quantifier2));
	return ElementSuccess;
}
// deletes relationship between parent and child
int UMLObjectsHolder::DeleteRelationship(std::string parent, std::string child)
{
	UMLObject* p, * c;

	p = GetUMLObject(parent);
	c = GetUMLObject(child);

	if (p == 0 || c == 0) return ClassDoesntExist;

	if (p->GetIndexRelationshipWith(child) == -1 || c->GetIndexRelationshipWith(parent) == -1) return RelationshipDoesNotExist;

	p->DeleteRelationship(child);
	c->DeleteRelationship(parent);
	return ElementSuccess;
}
//returns the title from the holder
UMLObject* UMLObjectsHolder::GetUMLObject(std::string title)
{
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == title) return i;
	}
	return 0;
}
// gets the relationship type based off the string
int UMLObjectsHolder::GetRelationshipTypeFromString(std::string in)
{
	int result = 0;
	if (in.size() == 0) return result;
	std::transform(std::cbegin(in), std::cend(in), std::begin(in), [](const unsigned char i) { return std::tolower(i); });
	if (in[0] == 'a') result = RelationshipAggregation;
	else if (in[0] == 'c') result = RelationshipComposition;
	else if (in[0] == 'g') result = RelationshipGeneralization;
	else if (in[0] == 'r') result = RelationshipRealization;
	return result;
}
// gets quantifier from the string
int UMLObjectsHolder::GetQuantifierFromString(std::string in)
{
	int result = 0;
	if (in.size() == 0) return result;
	std::transform(std::cbegin(in), std::cend(in), std::begin(in), [](const unsigned char i) { return std::tolower(i); });
	if (in == "1" || in == "one" || in[0] == 'o') result = RelationshipQuantifierOne;
	else if (in == "many" || in[0] == 'm') result = RelationshipQuantifierMany;
	return result;
}

//this function is used for determining if a user-entered field is actually referring
//to a class that already exists. If so, this means a relationship should be drawn between that class
//and the class in which the field was created
//currently it just checks for a case-sensitive substring, so there will be some false positives
//If the user does not want the relationship, they can just delete it.
std::string UMLObjectsHolder::IsFieldReferringToExistingClass(std::string in)
{
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle().find(in) != std::string::npos) return i->ReturnTitle();
	}
	return "";
}


//takes in the name of a class and the x position and sets that x postion 
int UMLObjectsHolder::SetX(std::string which_class, int x)
{
	UMLObject * m = GetUMLObject(which_class);
	if (m == NULL) return ClassDoesntExist;
	m->SetXPosition(x);
	return ElementSuccess;
}

//takes in the name of a class and the y position and sets that y postion 
int UMLObjectsHolder::SetY(std::string which_class, int y)
{
	UMLObject * m = GetUMLObject(which_class);
	if (m == NULL) return ClassDoesntExist;
	m->SetYPosition(y);
	return ElementSuccess;
}

int UMLObjectsHolder::GetX(std::string which_class)
{
	UMLObject * m = GetUMLObject(which_class);
	if (m == NULL) return ClassDoesntExist;
	return m->GetXPosition();
}

int UMLObjectsHolder::GetY(std::string which_class)
{
	UMLObject * m = GetUMLObject(which_class);
	if (m == NULL) return ClassDoesntExist;
	return m->GetYPosition();
}