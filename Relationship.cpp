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
