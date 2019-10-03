#include "UMLObjectsHolder.h"

UMLObjectsHolder::UMLObjectsHolder()
{
}

UMLObject * UMLObjectsHolder::CreateNewClass(std::string title)
{
	if (IsTitleUnique(title))
	{
		std::cout << "Creating Class: " << title << std::endl;
		UMLObject* a = new UMLObject();
		a->SetTitle(title);
		UMLObjects_holder.push_back(a);
		return a;
	}
	else
	{
		std::cout << "Duplicate name detected" << std::endl;
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

UMLObjectsHolder::~UMLObjectsHolder()
{
	for (auto i : UMLObjects_holder)
	{
		i = NULL;
		delete i;
	}
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

std::vector<UMLObject*> UMLObjectsHolder::ReturnPtrToVector()
{
	return UMLObjects_holder;
}

void UMLObjectsHolder::AddUMLObject(UMLObject* in)
{
	UMLObjects_holder.push_back(in);
}

bool UMLObjectsHolder::DeleteUMLObject(std::string title)
{
	for (unsigned int i = 0; i < UMLObjects_holder.size(); i++)
	{
		if (UMLObjects_holder[i]->ReturnTitle() == title)
		{
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

bool UMLObjectsHolder::AddRelationship(std::string parent, std::string child, int type)
{
	UMLObject* p, * c;

	p = GetObject(parent);
	c = GetObject(child);

	if (p == 0 || c == 0) return false;

	if (p->GetIndexRelationshipWith(child) != -1 || c->GetIndexRelationshipWith(parent) != -1) return false;

	p->AddRelationship({ type, c, true });
	c->AddRelationship({ type, p, false });

	return true;
}

bool UMLObjectsHolder::EditRelationship(std::string parent, std::string child, int type)
{
	UMLObject* p, * c;

	p = GetObject(parent);
	c = GetObject(child);

	if (p == 0 || c == 0) return false;

	if (p->GetIndexRelationshipWith(child) == -1 || c->GetIndexRelationshipWith(parent) == -1) return false;

	p->UpdateRelationship(p->GetIndexRelationshipWith(child), type);
	c->UpdateRelationship(c->GetIndexRelationshipWith(parent), type);
	return true;
}

bool UMLObjectsHolder::DeleteRelationship(std::string parent, std::string child)
{
	UMLObject* p, * c;

	p = GetObject(parent);
	c = GetObject(child);

	if (p == 0 || c == 0) return false;

	if (p->GetIndexRelationshipWith(child) == -1 || c->GetIndexRelationshipWith(parent) == -1) return false;

	p->DeleteRelationship(p->GetIndexRelationshipWith(child));
	c->DeleteRelationship(c->GetIndexRelationshipWith(parent));
	return true;
}

UMLObject* UMLObjectsHolder::GetObject(std::string title)
{
	for (auto i : UMLObjects_holder)
	{
		if (i->ReturnTitle() == title) return i;
	}
	return 0;
}
