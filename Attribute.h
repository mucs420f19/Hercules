#pragma once

#include <string>
#include <vector>

enum class Visibility { PUBLIC = 0, PROTECTED = 1, PRIVATE = 2 };

class Attribute {
public:
  Attribute(const std::string &name, Visibility v);

  void setVisibility(Visibility v);

  const std::string &name() const;
  const std::string &visibility() const;
  const char* rawName() const;
  const char* rawVisibility() const;

private:
  Visibility mVisibility;
  std::string mName;
};

class Field : public Attribute {

public:
  const std::string &type() const;
  const char* rawType() const;

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

  void appendParameter (const Parameter & param);
  void removeParameter (int index);
  void setParameters (const std::vector<Parameter>& params);
  void clearParameters ();

  const std::string& params() const;
  const char* rawParams() const;

private:
  std::vector<Parameter> mParameters;
  std::string mStringRep;
};

const std::string &ToString(Visibility v);
const char* ToRawString(Visibility v);
