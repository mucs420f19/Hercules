#include "Attribute.h"

Attribute::Attribute(const std::string & name, Visibility v)
	:mName(name), mVisibility(v)
{
}

void Attribute::setVisibility(Visibility v)
{
	mVisibility = v;
}

const std::string & Attribute::name() const
{
	return mName;
}

const std::string & Attribute::visibility() const
{
	return ToString(mVisibility);
}

const char * Attribute::rawName() const
{
	return mName.c_str();
}

const char * Attribute::rawVisibility() const
{
	return ToString(mVisibility).c_str();
}

Parameter::Parameter(const std::string & type, const std::string & name)
	:mName(name), mType(type)
{
}

void Parameter::setType(const std::string & type)
{
	mType = type;
}

void Parameter::setName(const std::string & name)
{
	mName = name;
}

const std::string & Parameter::type() const
{
	return mType;
}

const std::string & Parameter::name() const
{
	return mName;
}

const char * Parameter::rawType() const
{
	return mType.c_str();
}

const char * Parameter::rawName() const
{
	return mName.c_str();
}

Field::Field(const std::string& name, Visibility v, const std::string& type)
	: Attribute{ name, v }, mType(type)
{
}

const std::string & Field::type() const
{
	return mType;
}

const char * Field::rawType() const
{
	return mType.c_str();
}

void Method::appendParameter(const Parameter & param)
{
	mParameters.push_back(param);
}

void Method::removeParameter(int index)
{
	mParameters.erase(mParameters.begin() + index);
}

void Method::setParameters(const std::vector<Parameter>& params)
{
	mParameters = params;
}

void Method::clearParameters()
{
	mParameters.clear();
}

const std::string & Method::params() const
{
	for (auto & i : mParameters)
	{
		mStringRep + i.type() + " " + i.name() + ", ";
	}
	return mStringRep;
}

const char * Method::rawParams() const
{
	return mStringRep.c_str();
}

Visibility VisibilityFromString(const std::string& type)
{
	std::string in = type;
	Visibility result = Visibility::PRIVATE;
	if (in.size() == 0) return result;
	std::transform(std::cbegin(in), std::cend(in), std::begin(in), [](const unsigned char i) { return std::tolower(i); });
	if (in == "private" || in[0] == '-') result = Visibility::PRIVATE;
	else if (in == "public" || in[0] == '+') result = Visibility::PUBLIC;
	else if (in == "protected" || in[0] == '#') result = Visibility::PROTECTED;
	return result;
}

const std::string & ToString(Visibility v)
{
	static const std::string str[3] = { "Public", "Protected", "Private" };
	return str[static_cast<int>(v)];
}

const char * ToRawString(Visibility v)
{
	return ToString(v).c_str();
}
