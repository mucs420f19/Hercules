#include "Model.h"

void Model::addClass(const std::string & name)
{
	Class* testClassName = findClass(name);

	if (testClassName == nullptr)
	{
		Class a(name);
		mClasses.push_back(a);
	}
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
	Class* c = findClass(name);
	if (c == nullptr)
	{
		return;
	}
	std::vector<Relationship> temp = findRelationship(name);
	for (auto &i : temp)
	{
		removeRelationship(i.parent().name(),i.child().name());
	}
	auto it = find(mClasses.begin(), mClasses.end(), name);
	mClasses.erase(it);
}

void Model::addField(const std::string& className, const std::string& fieldName, const std::string& fieldType, Visibility fieldVisibility)
{
	Class* a = findClass(className);
	if (a == nullptr)
	{
		return;
	}
	//if the class already has a field with this name, exit
	if (findField(className, fieldName) != nullptr)
	{
		return;
	}
	a->addField(Field(fieldName, fieldVisibility, fieldType));
}

void Model::editField(const std::string& whichAttr, const std::string& className, const std::string& fieldName, const std::string& NewValue)
{
	Field* f = findField (className, fieldName);
	if (f == nullptr)
	{
		return;
	}

	if (whichAttr == "name")
	{
		f->setName(NewValue);
	}
	else if (whichAttr == "type")
	{
		f->setType(NewValue);
	}
	else if (whichAttr == "visibility")
	{
		Visibility v = VisibilityFromString(NewValue);
		f->setVisibility(v);
	}
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
	if (findMethod(className, methodName) != nullptr)
	{
		return;
	}
	a->addMethod(Method(methodName, methodVisibility, methodType));
}

void Model::editMethod(const std::string& whichAttr, const std::string& className, const std::string& methodName, const std::string& NewValue)
{
	Method* m = findMethod (className, methodName);
	if (m == nullptr)
	{
		return;
	}

	if (whichAttr == "name")
	{
		m->setName(NewValue);
	}
	else if (whichAttr == "type")
	{
		m->setType(NewValue);
	}
	else if (whichAttr == "visibility")
	{
		Visibility v = VisibilityFromString(NewValue);
		m->setVisibility(v);
	}
}

void Model::deleteMethod(const std::string& className, const std::string& methodName)
{
	Class* a = findClass(className);
	if (a == nullptr) return;
	a->removeMethod(methodName);
}

void Model::addParameter(const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& ParameterType)
{
	Class* c = findClass(className);
	if (c == nullptr) 
	{
		return;
	}

	Method* m = findMethod(className, methodName);
	if (m == nullptr)
	{
		return;
	}

	if (findParameter(className, methodName, ParameterName) != nullptr)
	{
		return;
	}

	m->appendParameter(Parameter(ParameterName, ParameterType));
}

void Model::editParameter(const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& NewValue, const std::string& WhichAttr)
{
}

void Model::deleteParameter(const std::string& className, const std::string& methodName, const std::string& ParameterName)
{
}

void Model::addRelationship(const std::string & parent, const std::string & child, RelationshipType type)
{
	if (parent == child)
	{
		return;
	}

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
		if (it->parent().name() == one && it->child().name() == two)
		{
			mRelationships.erase(it);
			return;
		}
		if (it->parent().name() == two && it->child().name() == one)
		{
			mRelationships.erase(it);
			return;
		}
	}
}

void Model::SetX(const std::string& className, unsigned int in)
{
	Class* a = findClass(className);
	if (a != nullptr) a->SetX(in);
}

void Model::SetY(const std::string& className, unsigned int in)
{
	Class* a = findClass(className);
	if (a != nullptr) a->SetY(in);
}

unsigned int Model::GetXPosition(const std::string& className)
{
	unsigned int result = 0;
	Class* a = findClass(className);
	if (a != nullptr) result = a->GetXPosition();
	return result;
}

unsigned int Model::GetYPosition(const std::string& className)
{
	unsigned int result = 0;
	Class* a = findClass(className);
	if (a != nullptr) result = a->GetYPosition();
	return result;
}

void Model::list()
{
	for (auto& i : mClasses)
	{
		size_t largestString = getLargestStringSize();
		size_t addSpace = 0;

		// ==================================================
		// ┌────────────────────┐

		std::cout << "\xDA";

		for (size_t x = 0; x < largestString + 2; ++x)
		{
			std::cout << "\xC4";
		}

		std::cout << "\xBF\n";

		// ==================================================
		// │ Title              │

		addSpace = largestString - i.name().size();

		std::cout << "\xB3 " + i.name()<< std::flush;
		
		for (size_t x = 0; x < addSpace; ++x)
		{
			std::cout << " ";
		}

		std::cout << " \xB3\n";

		// ==================================================
		// ├────────────────────┤

		std::string breakLine = "\xC3";

		for (size_t x = 0; x < largestString + 2; ++x)
		{
			breakLine += "\xC4";
		}

		breakLine += "\xB4\n";

		std::cout << breakLine;

		// ==================================================
		// Fields

		for (size_t x = 0; x < i.getFieldSize(); ++x)
		{
			Field& tempField = i.field(x);

			std::cout << "\xB3 ";
			std::string out = tempField.visibilitySymbol() + " " + tempField.name() + " : " + tempField.type();
			std::cout << out;

			addSpace = largestString - out.size();

			for (size_t x = 0; x < addSpace; ++x)
			{
				std::cout << " ";
			}

			std::cout << " \xB3\n";
		}

		// ==================================================
		// ├────────────────────┤

		std::cout << breakLine;

		// ==================================================
		// Methods
		
		for (size_t x = 0; x < i.getMethodSize(); ++x)
		{
			Method& tempMethod = i.method(x);

			std::cout << "\xB3 ";
			std::string out = tempMethod.visibilitySymbol() + " " + tempMethod.name() + tempMethod.params() +tempMethod.ReturnType();
			std::cout << out;

			addSpace = largestString - out.size();

			for (size_t x = 0; x < addSpace; ++x)
			{
				std::cout << " ";
			}

			std::cout << " \xB3\n";
		}

		// ==================================================
		// └────────────────────┘

		std::cout << "\xC0";

		for (size_t x = 0; x < largestString + 2; ++x)
		{
			std::cout << "\xC4";
		}

		std::cout << "\xD9\n";
	}

	// Print relationships
	for (auto & i : mRelationships)
	{
		std::cout << i.parent().name() << " is the parent of " << i.child().name() << " in a " << ToString(i.type()) << " relationship.\n";

		//std::cout << i.parent().name() << i.child().name() << ToString(i.type()) << "\n";
	}
}

size_t Model::getLargestStringSize()
{
	size_t largestString = 0;

	for (auto& i : mClasses)
	{
		// Check length of class name
		if (i.name().size() > largestString)
		{
			largestString = i.name().size();
		}

		// Check length of field strings
		// visibility fieldName : type
		for (size_t x = 0; x < i.getFieldSize(); ++x)
		{
			Field& temp = i.field(x);

			std::string check = temp.visibilitySymbol() + " " + temp.name() + " : " + temp.type();

			if (check.size() > largestString)
			{
				largestString = check.size();
			}
		}

		// Check length of method strings
		// visibility methodName(paramaters) : type
		for (size_t x = 0; x < i.getMethodSize(); ++x)
		{
			Method& temp = i.method(x);

			std::string check = temp.visibilitySymbol() + " " + temp.name() + "(!PARAMS!) : " + temp.ReturnType();

			if (check.size() > largestString)
			{
				largestString = check.size();
			}
		}
	}

	return largestString;
}

Relationship * Model::findRelationship(const std::string & one, const std::string & two)
{
	for (auto it = mRelationships.begin(); it != mRelationships.end(); ++it)
	{
		if (it->parent().name() == one && it->child().name() == two)
		{
			return &(*it);
		}
		if (it->parent().name() == two && it->child().name() == one)
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
		if (it->parent().name() == one && it->child().name() == two)
		{
			return &(*it);
		}
		if (it->parent().name() == two && it->child().name() == one)
		{
			return &(*it);
		}
	}
	return nullptr;
}

std::vector< Relationship> Model::findRelationship(const std::string& className) const
{
	std::vector<Relationship> result;
	for (auto it = mRelationships.begin(); it != mRelationships.end(); ++it)
	{
		if (it->parent().name() == className || it->child().name() == className)
		{
			result.push_back((*it));
		}
	}
	return result;
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
	if (mClasses.empty())
	{
		return nullptr;
	}
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
	if (findClass(className) == nullptr)
	{
		return nullptr;
	}
	Class* a = findClass(className);
	return a->field(fieldName);
}

Method* Model::findMethod(const std::string& className, const std::string& methodName)
{
	if (findClass(className) == nullptr) return nullptr;
	Class* a = findClass(className);
	return a->method(methodName);
}

const Parameter* Model::findParameter(const std::string& className, const std::string& methodName, const std::string& paramName)
{
	if (findMethod(className, methodName) == nullptr)
	{
		return nullptr;
	}

	Method* a = findMethod(className, methodName);
	const std::list<Parameter>* paramVec = a->ReturnParameters();
	
	for (auto &i : *paramVec)
	{
		if (i.name() == paramName)
		{
			return &i;
		}
	}

	return nullptr;
}

const std::list<Class>* Model::ReturnClasses() const
{
	return &mClasses;
}

const std::list<Relationship>* Model::ReturnRelationships() const
{
	return &mRelationships;
}

void Model::ClearProject()
{
	mClasses.clear();
	mRelationships.clear();
}
