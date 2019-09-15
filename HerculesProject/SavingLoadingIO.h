#pragma once
#include "UMLObject.h"
#include <fstream>
#include <algorithm>

#define DefaultFileName "Output.xml"

namespace SavingLoadingIO
{
	void SaveProjectToFile(std::vector<UMLObject*> in);
	std::vector<UMLObject*> LoadProject(std::string filename = DefaultFileName);
	std::string RemoveQuotes(std::string in);
	UMLObject* ProcessUMLObject(std::vector<std::string> i1);
	void ProcessUMLField(std::vector<std::string> i1, UMLObject * a);
	void ProcessUMLMethod(std::vector<std::string> i1, UMLObject* a);
	void ProcessUMLMethodParameters(std::vector<std::string> i1, UMLMethod * a);
}