#pragma once
#include "UMLObject.h"
#include <fstream>

namespace SavingLoadingIO
{
	void SaveProjectToFile(std::vector<UMLObject*> in);
	std::vector<UMLObject*> LoadProject();
}