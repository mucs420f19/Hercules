#include "Attribute.h"

Attribute::Attribute(const std::string & name, Visibility v)
{
	mName = name;
	mVisibility = v;
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
	return mVisibility;
}

const char * Attribute::rawName() const
{
	return mName;
}

const char * Attribute::rawVisibility() const
{
	return mVisibility;
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
	return mType;
}

const char * Parameter::rawName() const
{
	return mName;
}

const std::string & Field::type() const
{
	return mType;
}

const char * Field::rawType() const
{
	return mType;
}

void Method::appendParameter(const Parameter & param)
{
	mParameters.push_back(param);
}

void Method::removeParameter(int index)
{
	mParameters.erase(index)
}

void Method::setParameters(const std::vector<Parameter>& params)
{
	for (auto & i : params)
	{
		mParameters.push_back(i);
	}
}

void Method::clearParameters()
{
	for (auto & i : mParameters)
	{
		mParmeters.erase(i);
	}
}

const std::string & Method::params() const
{
	std::string params;
	for (auto & i : mParameters)
	{
		params += "Type: " + i.type();
		params += "Name: " + i.name() + ",";
	}
	return params;
}

const char * Method::rawParams() const
{
	std::string params;
	for (auto & i : mParameters)
	{
		params += "Type: " + i.type();
		params += "Name: " + i.name() + ",";
	}
	return params;
}

const std::string & ToString(Visibility v)
{
	if (v == 0)
	{
		return "Public";
	}
	else if (v == 1)
	{
		return "Protected";
	}
	else if (v == 2)
	{
		return "Private";
	}
}

const char * ToRawString(Visibility v)
{
	if (v == 0)
	{
		return "Public";
	}
	else if (v == 1)
	{
		return "Protected";
	}
	else if (v == 2)
	{
		return "Private";
	}
}
