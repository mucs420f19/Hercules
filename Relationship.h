#pragma once

#include "Class.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <cctype>

enum class RelationshipType {
	AGGREGATION = 0,
	COMPOSITION = 1,
	ASSOCIATION = 2,
	DEPENDENCY = 3,
	ERROR = -1
};

class Relationship {
public:
  Relationship(const Class &parent, const Class &child, RelationshipType type);

  const Class &parent() const;
  const Class &child() const;

  const Relationship& operator=(const Relationship &other);


  RelationshipType type() const;

  void setType (RelationshipType type);

  void PrintRelationships();

private:
  const Class &mParent;
  const Class &mChild;
  RelationshipType mType;
};


RelationshipType RelationshipFromString(const std::string &type);

const std::string &ToString(RelationshipType t);
const char* ToRawString(RelationshipType t);

bool operator== (const Relationship &n1, const Relationship &n2);

