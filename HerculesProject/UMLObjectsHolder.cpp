#include "UMLObjectsHolder.h"

UMLObjectsHolder::UMLObjectsHolder()
{
}

bool UMLObjectsHolder::CreateNewClass(std::string title)
{
	if (IsTitleUnique(title))
	{
		std::cout << "Creating Class: " << title << std::endl;
		UMLObject* a = new UMLObject();
		a->SetTitle(title);
		UMLObjects_holder.push_back(a);
		return true;
	}
	else
	{
		std::cout << "Duplicate name detected" << std::endl;
		return false;
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
	for (auto i : UMLObjects_holder)
		std::cout << i->ReturnTitle() << std::endl;
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
