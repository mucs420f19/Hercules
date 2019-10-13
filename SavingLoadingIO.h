#pragma once
#include "UMLObject.h"
#include "UMLObjectsHolder.h"
#include <fstream>
#include <algorithm>

#define DefaultFileName "Output.xml"

const int SaveSuccess = 0;
const int SaveError = 1;
const int SaveAlreadyExists = 2;

namespace SavingLoadingIO
{
	struct Node
	{
		std::string key;
		Node* parent;
		std::vector<Node*> children;
		std::vector<std::string> contents;
	};

	struct Relationship
	{
		Relationship(std::string p, std::string c, std::string t)
		{
			parent = p;
			child = c;
			type = t;
		}
		std::string parent;
		std::string child;
		std::string type;
	};

	int SaveProjectToFile(UMLObjectsHolder * in, std::string filename = DefaultFileName, bool overwrite = false);
	bool LoadProject(UMLObjectsHolder* out, std::string filename = DefaultFileName);
	std::string RemoveQuotes(std::string in);
	size_t GetIndent(std::string in);
	bool IsItem(std::string in);
	bool IsNode(std::string in);
	std::string RemoveWhitespaceBefore(std::string in);
	std::string RemoveWhitespaceAfter(std::string in);
	std::string StripItem(std::string in);
	std::string StripNode(std::string in);
	void ParseNode(Node* current, std::vector<std::string> lines, size_t c = 0);
	void ProcessResults(Node* current, UMLObjectsHolder* out, std::vector<Relationship> &relationships);
	std::string FindChildWhere(Node * in, std::string key);
	void LoadingCleanup(Node* in);
}