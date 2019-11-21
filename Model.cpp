#include "Model.h"

void Model::addClass(const std::string & name)
{
	Class *temp = new Class(name);
	mClasses.push_back(*temp);
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
	int index = 0;
	for (auto & i : mClasses)
	{
		if (i.name() == name)
		{
			mClasses.erase(mClasses.begin()+index);
		}
		++index;
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
	Relationship *temp = new Relationship(p, c, type);
	mRelationships.push_back(*temp);
}

void Model::removeRelationship(const std::string & one, const std::string & two)
{
	int index = 0;
	for (auto i : mRelationships)
	{
		if (i.parent().name() == one && i.child().name() == two)
		{
			//Ask About this error
			mRelationships.erase(mRelationships.begin() + index);
		}
		++index;
	}
}

Relationship * Model::findRelationship(const std::string & one, const std::string & two)
{
	Class p;
	Class c;
	std::string pString;
	std::string cString;
	for (auto  i : mRelationships)
	{
		p = i.parent();
		pString = p.name();
		c = i.child();
		cString = c.name();
		if (pString == one && cString == two)
		{
			return &i;
		}
	}
	return nullptr;
}

const Relationship * Model::findRelationship(const std::string & one, const std::string & two) const
{
	Class p;
	Class c;
	std::string pString;
	std::string cString;
	for (auto i : mRelationships)
	{
		p = i.parent();
		pString = p.name();
		c = i.child();
		cString = c.name();
		if (pString == one && cString == two)
		{
			return &i;
		}
	}
	return nullptr;
}

Class * Model::findClass(const std::string & name)
{
	for (auto  i : mClasses)
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
	for (auto  i : mClasses)
	{
		if (i.name() == name)
		{
			return &i;
		}
	}
	return nullptr;
}
