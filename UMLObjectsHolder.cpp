#include "UMLObjectsHolder.h"
// Creates a constructor
UMLObjectsHolder::UMLObjectsHolder()
{
}
// Allows a new class using title as primary key
UMLObject * UMLObjectsHolder::CreateNewClass(std::string title)
{
	if (IsTitleUnique(title))
	{
		//std::cout << "Creating Class: " << title << std::endl;
		UMLObject* a = new UMLObject();
		a->SetTitle(title);
		UMLObjects_holder.push_back(a);
		return a;
	}
	else
	{
		//std::cout << "Duplicate name detected" << std::endl;
		return 0;
	}
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

bool UMLObjectsHolder::EditClassTitle(std::string new_title, std::string old_title)
{
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == new_title) return false;
	}
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == old_title)
		{
			i->SetTitle(new_title);
			return true;
		}
	}
	return false;
}

int UMLObjectsHolder::GetVisibilityTypeFromString(std::string in)
{
	int result = 0;
	if (in.size() == 0) return result;
	std::transform(std::cbegin(in), std::cend(in), std::begin(in), [](const unsigned char i) { return std::tolower(i); });
	if (in == "private") result = UMLFieldVisibilityPrivate;
	else if (in == "public") result = UMLFieldVisibilityPublic;
	else if (in == "protected") result = UMLFieldVisibilityProtected;
	return result;
}

int UMLObjectsHolder::AddField(std::string class_title, std::string field_title, std::string type, int visibility)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) 
		return ClassDoesntExist;

	if (c->AddField(UMLField(field_title, type, visibility)) == false)
		return ElementExists;
	
	return ElementSuccess;
}

bool UMLObjectsHolder::EditFieldName(std::string class_title, std::string old_field_title, std::string new_field_title)
{
	return false;
}

bool UMLObjectsHolder::EditFieldType(std::string class_title, std::string field_title, std::string type)
{
	return false;
}

bool UMLObjectsHolder::EditFieldVisibility(std::string class_title, std::string field_title, std::string visibility)
{
	return false;
}

bool UMLObjectsHolder::DeleteField(std::string class_title, std::string field_title)
{
	return false;
}

int UMLObjectsHolder::AddMethod(std::string class_title, std::string method_title, std::string type, int visibility)
{
	UMLObject* c = GetUMLObject(class_title);

	if (c == 0) 
		return ClassDoesntExist;

	if (c->AddMethod(UMLMethod(method_title, type, {}, visibility)) == false)
		return ElementExists;
	
	return ElementSuccess;
}

bool UMLObjectsHolder::EditMethodName(std::string class_title, std::string old_method_name, std::string new_method_name)
{
	return false;
}

bool UMLObjectsHolder::EditMethodReturnType(std::string class_title, std::string method_name, std::string type)
{
	return false;
}

bool UMLObjectsHolder::EditMethodVisibility(std::string class_title, std::string method_title, std::string visibility)
{
	return false;
}

bool UMLObjectsHolder::DeleteMethod(std::string class_title, std::string method_title)
{
	return false;
}

bool UMLObjectsHolder::AddParameter(std::string class_title, std::string method_title, std::string param_name)
{
	return false;
}

bool UMLObjectsHolder::EditParameterName(std::string class_title, std::string method_title, std::string old_param_name, std::string new_param_name)
{
	return false;
}

bool UMLObjectsHolder::EditParameterType(std::string class_title, std::string method_title, std::string param_name, std::string type)
{
	return false;
}

bool UMLObjectsHolder::EditParameterSetDefaultValue(std::string class_title, std::string method_title, std::string param_name, std::string value)
{
	return false;
}

bool UMLObjectsHolder::EditParameterClearDefaultValue(std::string class_title, std::string method_title, std::string param_name)
{
	return false;
}

bool UMLObjectsHolder::DeleteParameter(std::string class_title, std::string method_title, std::string param_name)
{
	return false;
}

bool UMLObjectsHolder::AddRelationship(std::string parent, std::string child, int type, int quantifier1, int quantifier2)
{
	UMLObject* p, * c;

	p = GetUMLObject(parent);
	c = GetUMLObject(child);

	if (p == 0 || c == 0) return false;

	if (p->GetIndexRelationshipWith(child) != -1 || c->GetIndexRelationshipWith(parent) != -1) return false;

	p->AddRelationship({ type, quantifier1, c, p, true});
	c->AddRelationship({ type, quantifier2, p, c, false});

	return true;
}

bool UMLObjectsHolder::EditRelationship(std::string parent, std::string child, int type, int quantifier1, int quantifier2)
{
	UMLObject* p, * c;

	p = GetUMLObject(parent);
	c = GetUMLObject(child);

	if (p == 0 || c == 0) return false;

	if (p->GetIndexRelationshipWith(child) == -1 || c->GetIndexRelationshipWith(parent) == -1) return false;

	p->UpdateRelationship(p->GetIndexRelationshipWith(child), type, quantifier1);
	c->UpdateRelationship(c->GetIndexRelationshipWith(parent), type, quantifier2);
	return true;
}

bool UMLObjectsHolder::DeleteRelationship(std::string parent, std::string child)
{
	UMLObject* p, * c;

	p = GetUMLObject(parent);
	c = GetUMLObject(child);

	if (p == 0 || c == 0) return false;

	if (p->GetIndexRelationshipWith(child) == -1 || c->GetIndexRelationshipWith(parent) == -1) return false;

	p->DeleteRelationship(child);
	c->DeleteRelationship(parent);
	return true;
}

void UMLObjectsHolder::RefreshRelationships()
{
	UMLRelationship* a, * b;
	for (auto i : UMLObjects_holder)
	{
		for (auto j : UMLObjects_holder)
		{
			a = i->GetRelationshipWith(j->ReturnTitle());
			if (a)
			{
				b = j->GetRelationshipWith(i->ReturnTitle());
				EditRelationship(i->ReturnTitle(), j->ReturnTitle(), a->type, a->quantifier, b->quantifier);
			}
		}
	}
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