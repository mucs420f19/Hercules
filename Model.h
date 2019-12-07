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


  void SetX(const std::string& className, unsigned int in);
  void SetY(const std::string& className, unsigned int in);

  unsigned int GetXPosition(const std::string& className);
  unsigned int GetYPosition(const std::string& className);

  void list();
  size_t getLargestStringSize();

  Relationship* findRelationship (const std::string &one, const std::string &two);
  const Relationship* findRelationship (const std::string &one, const std::string &two) const;
  std::vector<Relationship> findRelationship(const std::string& className) const;

  Class* findClass (const std::string &name);
  const Class* findClass (const std::string &name) const;

  Field* findField(const std::string& className, const std::string& fieldName);
  Method* findMethod(const std::string& className, const std::string& methodName);
  const Method* findMethod(const std::string& className, const std::string& methodName) const;

  Parameter* findParameter(const std::string& className, const std::string& methodName, const std::string& paramName);
  const Parameter* findParameter(const std::string& className, const std::string& methodName, const std::string& paramName) const;
  const std::list<Class>* ReturnClasses() const;
  const std::list<Relationship>* ReturnRelationships() const;

  void ClearProject();

private:
  std::list<Class> mClasses;
  std::list<Relationship> mRelationships;
};
