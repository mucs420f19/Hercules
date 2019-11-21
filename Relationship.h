#pragma once

#include "Class.h"

enum class RelationshipType {
  AGGREGATION = 0,
  COMPOSITION = 1,
  ASSOCIATION = 2,
  DEPENDENCY = 3
};

class Relationship {
public:
  Relationship(const Class &parent, const Class &child, RelationshipType type);

  const Class &parent() const;
  const Class &child() const;

  RelationshipType type() const;

  void operator=(const Relationship &);

  void setType (RelationshipType type);

private:
  const Class &mParent;
  const Class &mChild;
  RelationshipType mType;
};

const std::string &ToString(RelationshipType t);
const char* ToRawString(RelationshipType t);
