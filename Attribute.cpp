#include "Attribute.h"
#include <iostream>

Attribute::Attribute(const std::string & name, Visibility v)
	:mName(name), mVisibility(v)
{
}

void Attribute::setVisibility(Visibility v)
{
	mVisibility = v;
}

void Attribute::setName(const std::string &name)
{
	mName = name;
}

const std::string & Attribute::name() const
{
	return mName;
}

const std::string & Attribute::visibility() const
{
	return ToStringVis(mVisibility);
}

const std::string & Attribute::visibilitySymbol() const
{
	static std::string plus = "+";
	static std::string bash = "#";
	static std::string minus = "-";
	static std::string qmark = "?";

	if (ToStringVis(mVisibility) == "Public")
	{
		return plus;
	}
	else if (ToStringVis(mVisibility) == "Protected")
	{
		return bash;
	}
	else if (ToStringVis(mVisibility) == "Private")
	{
		return minus;
	}
	else
	{
		return qmark;
	}
}

const char * Attribute::rawName() const
{
	return mName.c_str();
}

const char * Attribute::rawVisibility() const
{
	return ToRawStringVis(mVisibility);
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

void Field::setType(const std::string &type)
{
	mType = type;
}

Method::Method(const std::string& name, Visibility v, const std::string& type)
	: Attribute{ name, v }, mReturnType(type)
{
}

void Method::appendParameter(const Parameter & param)
{
	mParameters.push_back(param);
}

void Method::removeParameter(const std::string& name)
{
	auto matchesName = [&name](auto const& f) {
		return f.name() == name;
	};
	mParameters.remove_if(matchesName);
}

void Method::setParameters(const std::list<Parameter>& params)
{
	mParameters = params;
}

void Method::clearParameters()
{
	mParameters.clear();
}

const std::string & Method::ReturnType() const
{
	return mReturnType;
}

void Method::setmStringRep(const std::string & type)
{
	mStringRep.append(type);
}

const std::string & Method::params()
{
	mStringRep.clear();
	mStringRep += "(";

	if (!mParameters.empty())
	{
		for (auto & i : mParameters)
		{
			mStringRep += i.type() + " " + i.name() + ", ";
		}

		mStringRep.pop_back();
		mStringRep.pop_back();
	}
	mStringRep += ")";
	return mStringRep;
}

const char * Method::rawParams() const
{
	return mStringRep.c_str();
}

const std::list<Parameter>* Method::ReturnParameters() const
{
	return &mParameters;
}

std::list<Parameter>* Method::ReturnParameters()
{
	return &mParameters;
}

void Method::setType(const std::string &type)
{
	mReturnType = type;
}

Visibility VisibilityFromString(const std::string& type)
{
	std::string in = type;
	Visibility result = Visibility::INVALID;
	if (in.size() == 0) return result;
	std::transform(std::cbegin(in), std::cend(in), std::begin(in), [](const unsigned char i) { return std::tolower(i); });
	if (in == "private") result = Visibility::PRIVATE;
	else if (in == "public") result = Visibility::PUBLIC;
	else if (in == "protected") result = Visibility::PROTECTED;
	return result;
}

const std::string & ToStringVis(Visibility v)
{
	static const std::string str[3] = { "Public", "Protected", "Private" };
	return str[static_cast<int>(v)];
}

const char * ToRawStringVis(Visibility v)
{
	return ToStringVis(v).c_str();
}
