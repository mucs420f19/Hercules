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

RelationshipType typeConvert(const std::string & type)
{
	std::string in = type;
	RelationshipType result = RelationshipType::ERROR;
	if (in.size() == 0) return result;
	std::transform(std::cbegin(in), std::cend(in), std::begin(in), [](const unsigned char i) { return std::tolower(i); });
	if (in[0] == 'a') result = RelationshipType::AGGREGATION;
	else if (in[0] == 'c') result = RelationshipType::COMPOSITION;
	else if (in[1] == 's') result = RelationshipType::ASSOCIATION;
	else if (in[0] == 'd') result = RelationshipType::DEPENDENCY;
	return result;
}

RelationshipType Relationship::type() const
{
	return mType;
}

const Relationship& Relationship::operator=(const Relationship &other)
{
	return other;
}

void Relationship::setType(RelationshipType type)
{
	mType = type;
}

const std::string & FromString(RelationshipType t)
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