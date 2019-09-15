#pragma once
#include "UMLObject.h"

namespace SavingLoadingIO
{
	void SaveProjectToFile(std::vector<UMLObject*> in);
	std::vector<UMLObject*> LoadProject();
}