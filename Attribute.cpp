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
	for (auto & i : params)
	{
		mParameters.push_back(i);
	}
}

void Method::clearParameters()
{
	int index = 0;
	for (auto & i : mParameters)
	{
		mParameters.erase(mParameters.begin() + index);
		++index;
	}
}

const std::string & Method::params() const
{
	std::string params;
	for (auto & i : mParameters)
	{
		//Work on This
		//params += "Type: " + i.type();
		//params += "Name: " + i.name() + ",";
	}
	return params;
}

const char * Method::rawParams() const
{
	std::string params;
	for (auto & i : mParameters)
	{
		//Work on This
		//params += "Type: " + i.type();
		//params += "Name: " + i.name() + ",";
	}
	return params.c_str();
}

const std::string & ToString(Visibility v)
{
	std::string temp;
	switch (v)
	{
		case Visibility::PUBLIC:
			temp = "Public";
			break;
		case Visibility::PROTECTED:
			temp = "Protected";
			break;
		case Visibility::PRIVATE:
			temp = "Private";
			break;
	}
	return temp;
}

const char * ToRawString(Visibility v)
{
	std::string temp;
	switch (v)
	{
	case Visibility::PUBLIC:
		temp = "Public";
		break;
	case Visibility::PROTECTED:
		temp = "Protected";
		break;
	case Visibility::PRIVATE:
		temp = "Private";
		break;
	}
	return temp.c_str();
}
