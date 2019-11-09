#include "UMLObjectsHolder.h"
// Creates a constructor
UMLObjectsHolder::UMLObjectsHolder()
{
}

bool UMLObjectsHolder::IsTitleUnique(std::string in)
{
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

int UMLObjectsHolder::CreateNewClass(std::string title)
{
	if (!IsTitleUnique(title)) return ClassAlreadyExists;
	UMLObject* a = new UMLObject();
	a->SetTitle(title);
	UMLObjects_holder.push_back(a);
	return ElementSuccess;
}

void UMLObjectsHolder::UMLObjectPrintTitles()
{
	int count = 1;

	for (auto i : UMLObjects_holder)
	{
		std::cout << count << ". " << i->ReturnTitle() << std::endl;
		++count;
	}
}

void UMLObjectsHolder::UMLObjectPrintContents()
{
	for (auto i : UMLObjects_holder)
		std::cout << i->ToString() << std::endl;
}

void UMLObjectsHolder::UMLObjectPrintContentsREPL()
{
	for (auto i : UMLObjects_holder)
		std::cout << i->ToStringREPL() << std::endl;
}

std::vector<std::string> UMLObjectsHolder::UMLObjectReturnTitles()
{
	std::vector<std::string> out;
	for (auto  i : UMLObjects_holder)
	{
		out.push_back(i->ToString());
	}
	return out;
}

std::vector<std::string> UMLObjectsHolder::UMLObjectReturnTitlesString()
{
	std::vector<std::string> out;
	for (auto& i : UMLObjects_holder)
	{
		out.push_back(i->ReturnTitle());
	}
	return out;
}

std::vector<UMLObject*> UMLObjectsHolder::ReturnPtrToVector()
{
	return UMLObjects_holder;
}

void UMLObjectsHolder::AddUMLObject(UMLObject* in)
{
	if (in != NULL) UMLObjects_holder.push_back(in);
}

bool UMLObjectsHolder::DeleteUMLObject(std::string title)
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
						DeleteUMLObject(j->ReturnTitle());
					}
					j->DeleteRelationship(title);
				}
			}
		  
			UMLObjects_holder.erase(UMLObjects_holder.begin() + i);
			return true;
		}
	}
	return false;
}

size_t UMLObjectsHolder::Size()
{
	return UMLObjects_holder.size();
}

int UMLObjectsHolder::EditClassTitle(std::string new_title, std::string old_title)
{
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == new_title) return ElementAlreadyExists;
	}
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

int UMLObjectsHolder::AddField(std::string class_title, std::string field_title, std::string type, std::string visibility)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	if (!GetVisibilityTypeFromString(visibility)) return InvalidVisibility;
	return c->AddField(UMLField(field_title, type, GetVisibilityTypeFromString(visibility)));
}

int UMLObjectsHolder::EditFieldName(std::string class_title, std::string old_field_title, std::string new_field_title)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditField(old_field_title, new_field_title);
}

int UMLObjectsHolder::EditFieldType(std::string class_title, std::string field_title, std::string type)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditFieldT(field_title, type);
}

int UMLObjectsHolder::EditFieldVisibility(std::string class_title, std::string field_title, std::string visibility)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	if (!GetVisibilityTypeFromString(visibility)) return InvalidVisibility;
	return c->EditFieldV(field_title, GetVisibilityTypeFromString(visibility));
}

int UMLObjectsHolder::DeleteField(std::string class_title, std::string field_title)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->DeleteField(field_title);
}

int UMLObjectsHolder::AddMethod(std::string class_title, std::string method_title, std::string type, std::string visibility)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	if (!GetVisibilityTypeFromString(visibility)) return InvalidVisibility;
	return c->AddMethod(UMLMethod(method_title, type, {}, GetVisibilityTypeFromString(visibility)));
}

int UMLObjectsHolder::EditMethodName(std::string class_title, std::string old_method_name, std::string new_method_name)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditMethod(old_method_name, new_method_name);
}

int UMLObjectsHolder::EditMethodReturnType(std::string class_title, std::string method_name, std::string type)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;

	return c->EditMethodT(method_name, type);
}

int UMLObjectsHolder::EditMethodVisibility(std::string class_title, std::string method_title, std::string visibility)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	if (!GetVisibilityTypeFromString(visibility)) return InvalidVisibility;
	return c->EditMethodV(method_title, GetVisibilityTypeFromString(visibility));
}

int UMLObjectsHolder::DeleteMethod(std::string class_title, std::string method_title)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->DeleteMethod(method_title);
}

int UMLObjectsHolder::AddParameter(std::string class_title, std::string method_title, std::string param_name)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->AddParameter(method_title, param_name);
}

int UMLObjectsHolder::EditParameterName(std::string class_title, std::string method_title, std::string old_param_name, std::string new_param_name)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditParameterName(method_title, old_param_name, new_param_name);
}

int UMLObjectsHolder::EditParameterType(std::string class_title, std::string method_title, std::string param_name, std::string type)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditParameterType(method_title, param_name, type);
}

int UMLObjectsHolder::EditParameterSetDefaultValue(std::string class_title, std::string method_title, std::string param_name, std::string value)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditParameterSetDefaultValue(method_title, param_name, value);
}

int UMLObjectsHolder::EditParameterClearDefaultValue(std::string class_title, std::string method_title, std::string param_name)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->EditParameterClearDefaultValue(method_title, param_name);
}

int UMLObjectsHolder::DeleteParameter(std::string class_title, std::string method_title, std::string param_name)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) return ClassDoesntExist;
	return c->DeleteParameter(method_title, param_name);
}

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

UMLObject* UMLObjectsHolder::GetUMLObject(std::string title)
{
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == title) return i;
	}
	return 0;
}

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

int UMLObjectsHolder::GetQuantifierFromString(std::string in)
{
	int result = 0;
	if (in.size() == 0) return result;
	std::transform(std::cbegin(in), std::cend(in), std::begin(in), [](const unsigned char i) { return std::tolower(i); });
	if (in == "1" || in == "one" || in[0] == 'o') result = RelationshipQuantifierOne;
	else if (in == "many" || in[0] == 'm') result = RelationshipQuantifierMany;
	return result;
}