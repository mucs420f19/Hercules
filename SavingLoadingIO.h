#pragma once
#include "Model.h"
#include <fstream>
#include <algorithm>

#define DefaultFileName "Output.yml"

const int SaveSuccess = 0;
const int SaveError = 1;
const int SaveAlreadyExists = 2;
//header file defines the parent and children to provide saving and loading functionality.
namespace SavingLoadingIO
{
	struct Node
	{
		std::string key;
		Node* parent;
		std::vector<Node*> children;
		std::vector<std::string> contents;
	};

	//SaveProjectToFile does as it says. A default file name is given if there is none specified
	//the file will return SaveSuccess for success, SaveError for an unspecified error,
	//or SaveAlreadyExists if the target file already exists
	//the file can be overwritten if the overwrite optional parameter is true
	int SaveProjectToFile(Model * in, std::string filename = DefaultFileName, bool overwrite = false);

	//LoadProject accepts a UMLObjectsHolder and attempts to load filename into it as a Hercules project
	//The contents of the UMLObjectsHolder passed in are deleted regardless of what happens
	//a default file name is given if there is none specified
	bool LoadProject(Model * out, std::string filename = DefaultFileName);

	//these functions assign in generating and parsing the file for saving/loading
	std::string RemoveQuotes(std::string in);
	size_t GetIndent(std::string in);
	bool IsItem(std::string in);
	bool IsNode(std::string in);
	std::string RemoveWhitespaceBefore(std::string in);
	std::string RemoveWhitespaceAfter(std::string in);
	std::string StripItem(std::string in);
	std::string StripNode(std::string in);
	void ParseNode(Node* current, std::vector<std::string> lines, size_t c = 0);
	std::string FindChildWhere(Node* in, std::string key);
	std::vector<Node *> FindNodesWhere(Node * in, std::string key);

	//clean up all resources that were necessary for generating the UMLObjectsHolder during loading
	void LoadingCleanup(Node* in);

	//Once the items have been read from the file and a tree has been constructed, this function is used to load
	//the contents into a UMLObjectsHolder by parsing the tree
	void ProcessResults(Node* current, Model* out);

}