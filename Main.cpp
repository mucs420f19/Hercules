// HerculesProject.cpp : Defines the entry point for the application.
//

#include <iostream>

#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h"

int main()
{
  UMLObjectsHolder* holder = new UMLObjectsHolder();
  bool run = true;
  std::string input;
  
  std::cout << "Welcome to the Hercules UML Editor" << std::endl;
  std::cout << "Type 'help' for a list of commands." << std::endl;
  
  while (run)
  {
    std::cin >> input;
    
    if (input.compare("help"))
    {
      std::cout << "Usable Commands:" << std::endl << "===========" << std::endl;
      std::cout << "help - Display a list of usable commands." << std::endl;
      std::cout << "list - Lists all currently existing classes and their attributes." << std::endl << std::endl;
      
      std::cout << "add class [class name] - " << std::endl;
      std::cout << "add method [class name] [method name] - " << std::endl;
      std::cout << "add field [class name] [field name] - " << std::endl;
      std::cout << "add relationship [parent class] [child class] - " << std::endl << std:: endl;
      
      std::cout << "edit class [class name] - " << std::endl;
      std::cout << "edit method [class name] [method name] - " << std::endl;
      std::cout << "edit field [class name] [field name] - " << std::endl << std::endl;
      
      std::cout << "delete class [class name] - " << std::endl;
      std::cout << "delete method [class name] [method name] - " << std::endl;
      std::cout << "delete field [class name] [field name] - " << std::endl;
      std::cout << "delete relationship [parent class] [child class] - " << std::endl << std::endl;
      
      std::cout << "save [file] - Saves the current project to the given file." << std::endl;
      std::cout << "load [file] - Loads a previous project from the given file." << std::endl;
    }
    
    else if (input.compare("list"))
    {
      holder->UMLObjectPrintContents();
    }
    
    
    
    else 
    {
      std::cout << "Unknown input, type 'help' for a list of commands." << std::endl;
    }
  }
  
  return 0;
}
