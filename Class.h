#pragma once

#include "Attribute.h"

class Class {
public:
  Class();
  Class(const std::string &name);
  void rename(const std::string &newName);

  const std::string &name() const;
  const char *rawName() const;

  void addField (const Field& field);
  void addMethod (const Method& method);

  void removeField (int index);
  void removeField (const std::string& name);

  void removeMethod (int index);
  void removeMethod (const std::string& name);

  Method& method (const std::string& name);
  const Method& method (const std::string& name) const;
  Method& method (int index);
  const Method& method (int index) const;

  Field& field (const std::string& name);
  const Field& field (const std::string& name) const;
  Field& field (int index);
  const Field& field (int index) const;

private:
  std::string mName;
  std::list<Field> mFields;
  std::list<Method> mMethods;
};
