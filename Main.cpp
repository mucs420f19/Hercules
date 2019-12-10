// HerculesProject.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h"
//#include "REPL.h"
#include "GUI.h"
#include "node_editor.h"
#include "ConsoleView.h"

int main(int argc, char** argv)
{

	//Vars for class holders
	//UMLObjectsHolder* holder = new UMLObjectsHolder();
	ConsoleView view(std::cout, std::cin);
	if (argc == 1)
	{
		view.runREPL();
	}
	else
	{
		
	}

	return 0;
}

