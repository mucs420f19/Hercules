#include "Model.h"

void Model::addClass(const std::string & name)
{
	Class temp = Class::Class(name);
	mClasses.push_back(temp);
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
	for (auto & i : mClasses)
	{
		if (i.name() == name)
		{
			mClasses.erase(i);
		}
	}
}

void Model::addRelationship(const std::string & parent, const std::string & child, RelationshipType type)
{
	Class p;
	Class c;
	for (auto & i : mClasses)
	{
		if (i.name() == parent)
		{
			p = i;
		}
		if (i.name() == child)
		{
			c = i;
		}
	}
	Relationship temp = Relationship::Relationship(p, c, type);
	mRelationships.push_back(temp);
}

void Model::removeRelationship(const std::string & one, const std::string & two)
{
	for (auto & i : mRelationships)
	{
		if (i.parent() == one && i.child() == two)
		{
			mRelationships.erase(i);
		}
	}
}

Relationship * Model::findRelationship(const std::string & one, const std::string & two)
{
	for (auto & i : mRelationships)
	{
		if (i.parent() == one && i.child() == two)
		{
			return i;
		}
	}
	return nullptr;
}

const Relationship * Model::findRelationship(const std::string & one, const std::string & two) const
{
	for (auto & i : mRelationships)
	{
		if (i.parent() == one && i.child() == two)
		{
			return i;
		}
	}
	return nullptr;
	return nullptr;
}

Class * Model::findClass(const std::string & name)
{
	for (auto & i : mClasses)
	{
		if (i.name() == name)
		{
			return i;
		}
	}
	return nullptr;
}

const Class * Model::findClass(const std::string & name) const
{
	for (auto & i : mClasses)
	{
		if (i.name() == name)
		{
			return i;
		}
	}
	return nullptr;
}
