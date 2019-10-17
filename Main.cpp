// HerculesProject.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <ctime> // For splitting strings
#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h"
void help();
void fail();
int main()
{
  UMLObjectsHolder* holder = new UMLObjectsHolder();
  bool run = true;
  std::cout << "Welcome to the Hercules UML Editor" << std::endl;
  std::cout << "Type 'help' for a list of commands." << std::endl;
  // Execute until 'exit' is used
  while (run)
  {
    // Split the user's input into substrings
    std::string input;
    getline(std::cin, input);
    int length = input.length();
    std::vector<std::string> substrings;
    
    for (int x = 0, y = 0; x < length; ++x)
    {
      if (input[x] == ' ')
      {
        std::string substring = input.substr(y, x - y);
        y = x + 1;
        substrings.push_back(substring);
      }
      
      if (x == length - 1)
      {
        std::string substring = input.substr(y, x - y + 1);
        substrings.push_back(substring);
      }
    }
    
    // Check number of substrings, fail if invalid
    switch (substrings.size())
    {
      case 1:
      {
        // 'help' - Output contained in method 'help()'
        if (substrings[0] == "help")
          help();
      
        // 'list'
        else if (substrings[0] == "list")
          holder->UMLObjectPrintContents();
        
      // 'exit'
        else if (substrings[0] == "exit")
        {
          std::cout << "Thank you for using the Hercules UML Editor!" << std::endl;
          std::cout << "Have a nice day!" << std::endl;
          run = false;
        }
        
        // Fail is none of the above commands are used
        else
          fail();
      
        break;
      }
        
      case 2:
      {
        // 'save _____' - NOT COMPLETE ==================================================================================================================
        if (substrings[0] == "save")
        {
          // Save successful
          if (SavingLoadingIO::SaveProjectToFile(holder, substrings[1], false) == SaveSuccess)
            std::cout << "File saved successfully." << std::endl;
        
          // Save file already exists
          else if (SavingLoadingIO::SaveProjectToFile(holder, substrings[1], false) == SaveAlreadyExists)
          {
            std::cout << "This file already exists. Would you like to overwrite it? (y/n)" << std::endl;
            
            std::cin >> input;
            
            if (input == "y")
            {
              SavingLoadingIO::SaveProjectToFile(holder, substrings[1], true);
              
              std::cout << "File saved successfully." << std::endl;
              
              break;
            }
            
            else
            {
              std::cout << "File not saved." << std::endl;
              
              break;
            }
              
          
          }
        }
        
        break;
      }
        
      case 3:
      {
        // '_____ class _____' - Only possible option for the second substring
        if (substrings[1] == "class")
        {
          // 'add class _____' // ===== Verify class doesn't already exist ============================================
          if (substrings[0] == "add")
          {
            holder->CreateNewClass(substrings[2]);
            std::cout << "Successfully created class " << substrings[2] << "." << std::endl;
          }
          
          // 'delete class _____'
          else if (substrings[0] == "delete")
          {
            // Class exists and is deleted
            if (holder->DeleteUMLObject(substrings[2]))
              std::cout << "Successfully deleted class " << substrings[2] << "." << std::endl;
            
            // Class does not exist
            else
              std::cout << "Could not find a class called " << substrings[2] << "." << std::endl;
          }
          
          // Fail if 'add' or 'delete' are not first substring
          else
            fail();
        }
        
        // Fail if second substring is not 'class'
        else
          fail();
        
        break;
      }
        
      case 4:
      {
        // 'add _____ ...'
        if (substrings[0] == "add")
        {
          // 'add method _____ _____'
          if (substrings[1] == "method")
          {
          }
          
          // 'add field _____ _____'
          else if (substrings[1] == "field")
          {
          }
          
          // 'add relationship _____ _____' - 'type' set to 0 until types of relationships are added
          else if (substrings[1] == "relationship")
          {
            // Relationship acceptable
            if (holder->AddRelationship(substrings[2], substrings[3], 0))
              std::cout << "Relationship created successfully." << std::endl;
            
            // Relationship not acceptable and not created
            else
              std::cout << "An error has occurred, relationship not created." << std::endl;
          }
          
          // Fail if second substring is not 'method', 'field', or 'relationship'
          else
            fail();
        }
      
        // 'edit _____ ...'
        else if (substrings[0] == "edit")
        {
          // 'edit class _____ _____'
          if (substrings[1] == "class")
          {
            // Class name change is acceptable
            if (holder->EditClassTitle(substrings[3], substrings[2]))
              std::cout << "Class name changed successfully." << std::endl;
            // Class name change is not acceptable - Either the class doesn't exist or the new title is taken
            else
            {
              std::cout << "An error has occurred." << std::endl;
              std::cout << "Make sure that the class exists and that the new title is not already in use." << std::endl;
            }
          }
        }
        
        // 'delete _____ ...'
        else if (substrings[0] == "delete")
        {
        }
        
        // Fail if first substring is not 'add', 'edit', or 'delete'
        else
          fail();
        
        break;
    }
      
    // Fail if too many commands are entered
      default:
      {
        fail();
        
        break;
      }
    }
  }
  return 0;
}

void help()
{
  std::cout << "Usable Commands:" << std::endl << "================" << std::endl;
  
  std::cout << "help - Display a list of usable commands." << std::endl; //
  std::cout << "list - Lists all currently existing classes and their attributes." << std::endl; //
  std::cout << "exit - Exit the Hercules UML Editor." << std::endl << std::endl; //
  
  std::cout << "save [file name] - Saves the current project to the given file." << std::endl;
  std::cout << "load [file name] - Loads a previous project from the given file." << std::endl << std::endl;
  
  std::cout << "add class [class name]    - " << std::endl; //
  std::cout << "edit class [old class name] [new class name] - " << std::endl; //
  std::cout << "delete class [class name] - " << std::endl << std::endl; //
  
  std::cout << "add method [class name] [method name]    - " << std::endl;
  std::cout << "edit method [class name] [method name]   - " << std::endl;
  std::cout << "delete method [class name] [method name] - " << std::endl << std::endl;
  
  std::cout << "add field [class name] [field name]    - " << std::endl;
  std::cout << "edit field [class name] [field name]   - " << std::endl;
  std::cout << "delete field [class name] [field name] - " << std::endl << std::endl;
  
  std::cout << "add relationship [parent class] [child class]    - " << std::endl;
  std::cout << "delete relationship [parent class] [child class] - " << std::endl << std::endl;
}

void fail()
{
  std::cout << "Unknown input, type 'help' for a list of commands." << std::endl;
}