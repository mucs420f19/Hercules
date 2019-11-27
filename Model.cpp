#include "Model.h"

void Model::addClass(const std::string & name)
{
	Class a(name);
	mClasses.push_back(a);
}

void Model::editClass(const std::string & Oldname, const std::string & Newname)
{
	for (auto & i : mClasses)
	{
		if (i.name() == Oldname)
		{
			i.rename(Newname);
		}
	}
}

void Model::removeClass(const std::string & name)
{
	auto it = find(mClasses.begin(), mClasses.end(), name);
	mClasses.erase(it);
}

void Model::addField(const std::string& className, const std::string& fieldName, const std::string& fieldType, const std::string& fieldVisibility)
{
}

void Model::editField(const std::string& whichAttr, const std::string& className, const std::string& fieldName, const std::string& NewValue)
{
}

void Model::deleteField(const std::string& className, const std::string& fieldName)
{
}

void Model::addRelationship(const std::string & parent, const std::string & child, RelationshipType type)
{
	auto p = find(mClasses.begin(), mClasses.end(), parent);
	auto c = find(mClasses.begin(), mClasses.end(), child);
	mRelationships.push_back(Relationship((*p), (*c), type));
}

void Model::editRelationship(const std::string& parent, const std::string& child, RelationshipType type)
{
	if (findRelationship(parent, child) == NULL) return;
	findRelationship(parent, child)->setType(type);
}

void Model::removeRelationship(const std::string & one, const std::string & two)
{
	for (auto it = mRelationships.begin(); it != mRelationships.end(); ++it)
	{
		if ((*it).parent().name() == one && (*it).child().name() == two)
		{
			mRelationships.erase(it);
		}
		if ((*it).parent().name() == two && (*it).child().name() == one)
		{
			mRelationships.erase(it);
		}
	}
}

void Model::list()
{
	for (auto & i : mClasses)
	{
		std::cout << i.name() << "\n";
	}
	for (auto & i : mRelationships)
	{
		std::cout << i.parent().name() << i.child().name() << ToString(i.type()) << "\n";
	}
}

Relationship * Model::findRelationship(const std::string & one, const std::string & two)
{
	for (auto it = mRelationships.begin(); it != mRelationships.end(); ++it)
	{
		if ((*it).parent().name() == one && (*it).child().name() == two)
		{
			return &(*it);
		}
		if ((*it).parent().name() == two && (*it).child().name() == one)
		{
			return &(*it);
		}
	}
	return nullptr;
}

const Relationship * Model::findRelationship(const std::string & one, const std::string & two) const
{
	for (auto it = mRelationships.begin(); it != mRelationships.end(); ++it)
	{
		if ((*it).parent().name() == one && (*it).child().name() == two)
		{
			return &(*it);
		}
		if ((*it).parent().name() == two && (*it).child().name() == one)
		{
			return &(*it);
		}
	}
	return nullptr;
}

Class * Model::findClass(const std::string & name)
{
	for (auto  &i : mClasses)
	{
		if (i.name() == name)
		{
			return &i;
		}
	}
	return nullptr;
}

const Class * Model::findClass(const std::string & name) const
{
	for (auto  &i : mClasses)
	{
		if (i.name() == name)
		{
			return &i;
		}
	}
	return nullptr;
}
