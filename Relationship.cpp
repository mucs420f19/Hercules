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
	std::string temp;
	switch (t)
	{
	case RelationshipType::AGGREGATION:
		temp = "Aggregation";
		break;
	case RelationshipType::COMPOSITION:
		temp = "Composition";
		break;
	case RelationshipType::ASSOCIATION:
		temp = "Association";
		break;
	case RelationshipType::DEPENDENCY:
		temp = "Dependency";
		break;
	}
	return temp;
}

const char * ToRawString(RelationshipType t)
{
	std::string temp;
	switch (t)
	{
	case RelationshipType::AGGREGATION:
		temp = "Aggregation";
		break;
	case RelationshipType::COMPOSITION:
		temp = "Composition";
		break;
	case RelationshipType::ASSOCIATION:
		temp = "Association";
		break;
	case RelationshipType::DEPENDENCY:
		temp = "Dependency";
		break;
	}
	return temp.c_str();
}