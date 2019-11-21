#include "Relationship.h"

Relationship::Relationship(const Class & parent, const Class & child, RelationshipType type)
{
	mParent = parent;
	mChild = child;
	mType = type;
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
	if (t == 0)
	{
		return "Aggregation";
	}
	else if (t == 1)
	{
		return "Composition";
	}
	else if (t == 2)
	{
		return "Association";
	}
	else if (t == 3)
	{
		return "Dependency";
	}
}

const char * ToRawString(RelationshipType t)
{
	if (t == 0)
	{
		return "Aggregation";
	}
	else if (t == 1)
	{
		return "Composition";
	}
	else if (t == 2)
	{
		return "Association";
	}
	else if (t == 3)
	{
		return "Dependency";
	}
}
