#include "Relationship.h"

Relationship::Relationship(const Class & parent, const Class & child, RelationshipType type) :mParent(parent), mChild(child), mType(type)
{
}

const Class & Relationship::parent() const
{
	return mParent;
}

const Class & Relationship::child() const
{
	return mChild;
}

RelationshipType Relationship::type() const
{
	return mType;
}

void Relationship::setType(RelationshipType type)
{
	mType = type;
}

const std::string & ToString(RelationshipType t)
{
	switch (t)
	{
	case 0:
		return "Aggregation";
	case 1:
		return "Composition";
	case 2:
		return "Association";
	case 3:
		return "Dependency";
	}
}

const char * ToRawString(RelationshipType t)
{
	std::string A = "Aggregation";
	std::string C = "Composition";
	std::string Assoc = "Association";
	std::string D = "Dependency";
	switch (t)
	{
		case 0:
			return A.c_str();
		case 1:
			return C.c_str();
		case 2:
			return Assoc.c_str();
		case 3:
			return D.c_str();
	}
}
