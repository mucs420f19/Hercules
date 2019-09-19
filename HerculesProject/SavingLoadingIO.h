#pragma once
#include "UMLObject.h"
#include "UMLObjectsHolder.h"
#include <fstream>
#include <algorithm>

#define DefaultFileName "Output.xml"

namespace SavingLoadingIO
{
	void SaveProjectToFile(UMLObjectsHolder * in, std::string filename = DefaultFileName);
	bool LoadProject(UMLObjectsHolder* out, std::string filename = DefaultFileName);
	std::string RemoveQuotes(std::string in);
	UMLObject* ProcessUMLObject(std::vector<std::string> i1);
	void ProcessUMLField(std::vector<std::string> i1, UMLObject * a);
	void ProcessUMLMethod(std::vector<std::string> i1, UMLObject* a);
	void ProcessUMLMethodParameters(std::vector<std::string> i1, UMLMethod * a);
}