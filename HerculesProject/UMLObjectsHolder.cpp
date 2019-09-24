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

void UMLObjectsHolder::DeleteUMLObject(size_t in)
{
  UMLObjects_holder.erase(UMLObjects_holder.begin() + in);
}

bool UMLObjectsHolder::isNotEmpty()
{
  if (UMLObjects_holder.size() == 0)
    return false;
  else
    return true;
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
