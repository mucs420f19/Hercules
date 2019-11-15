#pragma once

#include "Class.h"
#include "Relationship.h"

class Model {

public:
  void addClass(const std::string &name);

  void removeClass(const std::string &name);

  void addRelationship(const std::string &parent, const std::string &child,
                       RelationshipType type);

  void removeRelationship(const std::string &one, const std::string &two);

  Relationship* findRelationship (const std::string &one, const std::string &two);
  const Relationship* findRelationship (const std::string &one, const std::string &two) const;

  Class* findClass (const std::string &name);
  const Class* findClass (const std::string &name) const;

private:
  std::vector<Class> mClasses;
  std::vector<Relationship> mRelationships;
};
