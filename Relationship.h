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

private:
  const Class &mParent;
  const Class &mChild;
  RelationshipType mType;
};


RelationshipType typeConvert(const std::string &type);

const std::string &FromString(RelationshipType t);
const char* ToRawString(RelationshipType t);
