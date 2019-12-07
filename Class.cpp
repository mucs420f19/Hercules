// System includes
#include <iterator>

// Local includes
#include "Class.h"

#include <iostream>

// Default constructor
Class::Class()
	:x(0), y(0)
{
}

// Constructor given a name
Class::Class(const std::string &name)
	:mName(name), x(0), y(0)
{
}

// Changes the name of an existing class to a new given name
void Class::rename(const std::string &newName)
{
    mName = newName;
}

// Returns the name of a class
const std::string &Class::name() const
{
    return mName;
}

// Returns the raw name of a class
const char *Class::rawName() const
{
    return mName.c_str();
}

// Adds a field to the classes' field vector
void Class::addField(const Field &field)
{
    mFields.push_back(field);
}

// Adds a method to the classes' method vector
void Class::addMethod(const Method &method)
{
    mMethods.push_back(method);
}

// Removes a field from the vector of fields at the given index
void Class::removeField(int index)
{
	std::list<Field>::iterator it = mFields.begin();
	std::advance(it, index);
	mFields.erase(it);
}

// Removes a field from the vector of fields after finding its index
void Class::removeField(const std::string& name)
{
	auto matchesName = [&name](auto const& f) {
		return f.name() == name;
	};
	mFields.remove_if(matchesName);
}

// Removes a method from the vector of methods at the given index
void Class::removeMethod(int index)
{
	std::list<Method>::iterator it = mMethods.begin();
	std::advance(it, index);
	mMethods.erase(it);
}

// Removes a method from the vector of methods after finding its index
void Class::removeMethod(const std::string &name)
{
	auto matchesName = [&name](auto const& f) {
		return f.name() == name;
	};
	mMethods.remove_if(matchesName);
}

// Returns a method from the vector of methods given its name
Method *Class::method(const std::string &name)
{
	Method *Temp = nullptr;
	for (auto& i : mMethods)
	{
		if (i.name() == name)
		{
			return &i;
		}
	}
	return Temp;
}

// Returns a method from the vector of methods given its name
const Method *Class::method(const std::string &name) const
{
	Method *Temp = nullptr;
    for (auto &i : mMethods)
    {
		if (i.name() == name)
		{
			return &i;
		}
    }
	return Temp;
}

// Returns a method from the vector of methods given its index
Method &Class::method(int index)
{
	std::list<Method>::iterator it = mMethods.begin();
	std::advance(it, index);
	return *it;
}

// Returns a method from the vector of methods given its index
const Method &Class::method(int index) const
{
	std::list<Method>::const_iterator it = mMethods.begin();
	std::advance(it, index);
	return *it;
}

// Returns a field from the vector of fields given its name
Field *Class::field(const std::string &name)
{
	Field *Temp = nullptr;
    for (auto &i : mFields)
    {
		if (i.name() == name)
		{
			return &i;
		}
    }
	return Temp;
}

// Returns a field from the vector of fields gien its name
const Field *Class::field(const std::string &name) const
{
	Field *Temp = nullptr;
	for (auto &i : mFields)
	{
		if (i.name() == name)
		{
			return &i;
		}
	}
	return Temp;
}

// Returns a field from the vector of fields gien its index
Field &Class::field(int index)
{
	std::list<Field>::iterator it = mFields.begin();
	std::advance(it, index);
	return *it;
}

// Returns a field from the vector of fields gien its index
const Field &Class::field(int index) const
{
	std::list<Field>::const_iterator it = mFields.begin();
	std::advance(it, index);
	return *it;
}

// Returns the number of methods in the list mMethods
unsigned int Class::getMethodSize ()
{
	return mMethods.size();
}

// Returns the number of fields in the list mMethods
unsigned int Class::getFieldSize ()
{
	return mFields.size();
}

void Class::SetX(unsigned int in)
{
	x = in;
}

void Class::SetY(unsigned int in)
{
	y = in;
}

unsigned int Class::GetXPosition()
{
	return x;
}

unsigned int Class::GetYPosition()
{
	return y;
}

const std::list<Field>* Class::ReturnFields() const
{
	return &mFields;
}

const std::list<Method>* Class::ReturnMethods() const
{
	return &mMethods;
}

void Class::PrintClasses(size_t largest)
{
	size_t largestString = largest;
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

	addSpace = largestString - name().size();

	std::cout << "\xB3 " + name()<< std::flush;
		
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

	for (size_t x = 0; x < getFieldSize(); ++x)
	{
		Field& tempField = field(x);

		std::cout << "\xB3 ";
		std::string out = tempField.visibilitySymbol() + " " + tempField.type() + " " + tempField.name();
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
		
	for (size_t x = 0; x < getMethodSize(); ++x)
	{
		Method& tempMethod = method(x);

		std::cout << "\xB3 ";
		std::string out = tempMethod.visibilitySymbol() + " " + tempMethod.ReturnType() + " " + tempMethod.name() + " " + tempMethod.params();
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

bool operator== (const Method &n1, const Method &n2)
{
	return n1.name() == n2.name();
}

bool operator== (const Field &n1, const Field &n2)
{
	return n1.name() == n2.name();
}

bool operator== (const Class &n1, const Class &n2)
{
	return n1.name() == n2.name();
}