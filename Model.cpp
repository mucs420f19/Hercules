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

void Model::addField(const std::string& className, const std::string& fieldName, const std::string& fieldType, Visibility fieldVisibility)
{
	Class* a = findClass(className);
	if (a == nullptr) return;
	//if the class already has a field with this name, exit
	if (findField(className, fieldName) != nullptr) return;
	Field f(fieldName, fieldVisibility, fieldType);
	a->addField(f);
}

void Model::editField(const std::string& whichAttr, const std::string& className, const std::string& fieldName, const std::string& NewValue)
{
}

void Model::deleteField(const std::string& className, const std::string& fieldName)
{
	Class* a = findClass(className);
	if (a == nullptr) return;
	a->removeField(fieldName);
}

void Model::addMethod(const std::string& className, const std::string& methodName, const std::string& methodType, Visibility methodVisibility)
{
	Class* a = findClass(className);
	if (a == nullptr) return;
	//if the class already has a field with this name, exit
	if (findField(className, methodName) != nullptr) return;
	Method f(methodName, methodVisibility, methodType);
	a->addMethod(f);
}

void Model::editMethod(const std::string& whichAttr, const std::string& className, const std::string& methodName, const std::string& NewValue)
{
}

void Model::deleteMethod(const std::string& className, const std::string& methodName)
{
	Class* a = findClass(className);
	if (a == nullptr) return;
	a->removeMethod(methodName);
}

void Model::addParameter(const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& ParameterType)
{
}

void Model::editParameter(const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& NewValue, const std::string& WhichAttr)
{
}

void Model::deleteParameter(const std::string& className, const std::string& methodName, const std::string& ParameterName)
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

Field* Model::findField(const std::string& className, const std::string& fieldName)
{
	if (findClass(className) == nullptr) return nullptr;
	Class* a = findClass(className);
	return &a->field(fieldName);
}

Method* Model::findMethod(const std::string& className, const std::string& methodName)
{
	if (findClass(className) == nullptr) return nullptr;
	Class* a = findClass(className);
	return &a->method(methodName);
}
