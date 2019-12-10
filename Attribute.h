#pragma once

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <locale>
#include <cctype>


enum class Visibility { PUBLIC = 0, PROTECTED = 1, PRIVATE = 2, INVALID = -1};

class Attribute {
public:
  Attribute(const std::string &name, Visibility v);

  void setVisibility(Visibility v);
  void setName(const std::string &name);

  const std::string &name() const;
  const std::string &visibility() const;
  const std::string &visibilitySymbol() const;
  const char* rawName() const;
  const char* rawVisibility() const;

private:
  Visibility mVisibility;
  std::string mName;
};

class Field : public Attribute {

	using Attribute::Attribute;
public:
	Field(const std::string& name, Visibility v, const std::string& type);
  const std::string &type() const;
  const char* rawType() const;

  void setType(const std::string &type);

private:
  std::string mType;
};

class Parameter {

public:
  Parameter (const std::string &type, const std::string &name);

  void setType (const std::string &type);
  void setName (const std::string &name);

  const std::string &type () const;
  const std::string &name () const;

  const char* rawType() const;
  const char* rawName() const;


private:
  std::string mType;
  std::string mName;
};

class Method : public Attribute {
public:
  using Attribute::Attribute;
  Method(const std::string& name, Visibility v, const std::string& type);
  void appendParameter (const Parameter & param);
  void removeParameter (const std::string& name);
  void setParameters (const std::list<Parameter>& params);
  void clearParameters ();
  const std::string &ReturnType() const;

  void setmStringRep(const std::string &type);

  const std::string& params();
  const char* rawParams() const;
  const std::list<Parameter>* ReturnParameters() const;
  std::list<Parameter>* ReturnParameters();

  void setType(const std::string &type);

private:
  std::string mReturnType;
  std::list<Parameter> mParameters;
  std::string mStringRep;
};

Visibility VisibilityFromString(const std::string& type);

const std::string &ToStringVis(Visibility v);
const char* ToRawStringVis(Visibility v);
