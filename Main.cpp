// HerculesProject.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <ctime> // For splitting strings
#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h"
#include "REPL.h"

int main()
{
	UMLObjectsHolder* holder = new UMLObjectsHolder();
	
	//Brian's code will select if we are running REPL or not
	RunREPL(holder);
	return 0;
}