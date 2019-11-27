#pragma once

#include "Class.h"
#include "Relationship.h"

class Model {

public:
  void addClass(const std::string &name);

  void editClass(const std::string &Oldname, const std::string &Newname);

  void removeClass(const std::string &name);


  void addField(const std::string& className, const std::string& fieldName, const std::string& fieldType, Visibility fieldVisibility);
  void editField(const std::string& whichAttr, const std::string& className, const std::string& fieldName, const std::string& NewValue);
  void deleteField(const std::string& className, const std::string& fieldName);

  void addMethod(const std::string& className, const std::string& methodName, const std::string& methodType, Visibility methodVisibility);
  void editMethod(const std::string& whichAttr, const std::string& className, const std::string& methodName, const std::string& NewValue);
  void deleteMethod(const std::string& className, const std::string& methodName);

  void addParameter(const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& ParameterType);
  void editParameter(const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& NewValue, const std::string& WhichAttr);
  void deleteParameter(const std::string& className, const std::string& methodName, const std::string& ParameterName);


  void addRelationship(const std::string &parent, const std::string &child,
                       RelationshipType type);

  void editRelationship(const std::string& parent, const std::string& child,
	  RelationshipType type);

  void removeRelationship(const std::string &one, const std::string &two);

  void list();

  Relationship* findRelationship (const std::string &one, const std::string &two);
  const Relationship* findRelationship (const std::string &one, const std::string &two) const;

  Class* findClass (const std::string &name);
  const Class* findClass (const std::string &name) const;

  Field* findField(const std::string& className, const std::string& fieldName);

private:
  std::list<Class> mClasses;
  std::list<Relationship> mRelationships;
};
