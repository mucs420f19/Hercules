#pragma once

#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h"

void help();
void fail();
void RunREPL(UMLObjectsHolder* holder, std::string input = "");

void help()
{
	std::cout << "\nUsable Commands:" << std::endl << "================" << std::endl;

	std::cout << "help - Display a list of usable commands." << std::endl; 
	std::cout << "list - Lists all currently existing classes and their attributes." << std::endl;
	std::cout << "titles - Lists titles of all currently existing classes." << std::endl;
	std::cout << "exit - Exit the Hercules UML Editor." << std::endl << std::endl; 

	std::cout << "save [file name] - Saves the current project to the given file." << std::endl;
	std::cout << "load [file name] - Loads a previous project from the given file." << std::endl << std::endl;

	std::cout << "add class [class name] - Creates a new class." << std::endl;
	std::cout << "delete class [class name] - Deletes a class." << std::endl; 
	std::cout << "edit class [old class name] [new class name] - Changes the name of a class." << std::endl << std::endl; 

	std::cout << "add field [class name] [field name] [return type] [visibility] - Adds a new field to a given class." << std::endl;
	std::cout << "delete field [class name] [field name] - Removes an existing field from a given class." << std::endl;
	std::cout << "edit field name [class name] [field name] [new name] - Edit the name of an existing field." << std::endl;
	std::cout << "edit field type [class name] [field name] [new type] - Edit the return type of an existing field." << std::endl;
	std::cout << "edit field visibility [class name] [field name] [new visibility] - Edit the visibility of an existing field." << std::endl << std::endl;

	std::cout << "add method [class name] [method name] [return type] [visibility] - Adds a new method to a given class." << std::endl;
	std::cout << "delete method [class name] [method name] - Removes an existing method from a given class." << std::endl;
	std::cout << "edit method name [class name] [method name] [new name] - Edit the name of an existing field." << std::endl;
	std::cout << "edit method type [class name] [method name] [new type] - Edit the return type of an existing field." << std::endl;
	std::cout << "edit method visibility [class name] [method name] [new visibility] - Edit the visibility of an existing field." << std::endl << std::endl;

	std::cout << "add relationship [parent class] [child class] [type] [q1] [q2] - Adds a relationship between the parent and child classes." << std::endl;
	std::cout << "delete relationship [parent class] [child class] - Deletes a given relationship." << std::endl;
	std::cout << "edit relationship [parent class] [child class] [type] [q1] [q2] - Edits an existing relationship." << std::endl << std::endl;

	std::cout << "Additional Info:" << std::endl << "===============" << std::endl;

	std::cout << "Quantifier Syntax" << std::endl << "q1-q2" << std::endl << "\tSo if q2 = many and q1 = one, you would have a one-to-many relationship." << std::endl << std::endl;

	std::cout << "Acceptable visibilities for methods & fields:" << std::endl;
	std::cout << "public / +" << std::endl << "private / -" << std::endl << "protected / #" << std::endl << std::endl;

	std::cout << "Acceptable relationship types:" << std::endl;
	std::cout << "[a]ggregation" << std::endl << "[c]omposition" << std::endl << "[g]eneralization" << std::endl << "[r]ealization" << std::endl << std::endl;

	std::cout << "Acceptable relationship quantifiers:" << std::endl;
	std::cout << "one / 1" << std::endl << "many" << std::endl << std::endl;
}

void fail()
{
	std::cout << "Unknown input, type 'help' for a list of commands." << std::endl;
}

void RunREPL(UMLObjectsHolder* holder, std::string input)
{
	bool run = true;
	//Are we in test mode? yes, if there was already an input. default is empty string
	if (input != "")
	{
		//we are in test mode, so only run one pass through the loop
		run = false;
	}
	else
	{
		std::cout << "Welcome to the Hercules UML Editor" << std::endl;
		std::cout << "Type 'help' for a list of commands." << std::endl;
	}

	// Execute until 'exit' is used
	do
	{
		//no need to getline if we are in test mode
		if (run)
			getline(std::cin, input);
		
		size_t length = input.length();
		std::vector<std::string> substrings;

		// Check for end of file
		if (!std::cin)
 		{
     		if(std::cin.eof())
         		std::cout << "End of file reached." << std::endl;
			
			run = false;

			break;
 		}

		// Split the user's input into substrings if eof is not reached
		else
		{
			for (size_t x = 0, y = 0; x < length; ++x)
			{
				if (input[x] == ' ')
				{
					std::string substring = input.substr(y, x - y);
					y = x + 1;

					if (substring != "")
						substrings.push_back(substring);
				}

				if (x == length - 1)
				{
					std::string substring = input.substr(y, x - y + 1);

					if (substring != "")
						substrings.push_back(substring);
				}
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
				  	holder->UMLObjectPrintContentsREPL();
			  
			  	// 'title'
			  	else if (substrings[0] == "titles")
				  	holder->UMLObjectPrintTitles();

			  	// 'exit'
			  	else if (substrings[0] == "exit")
			  	{
				  	std::cout << "Thank you for using the Hercules UML Editor!" << std::endl;
				  	std::cout << "Have a nice day!" << std::endl << std::endl;
				  
				  	run = false;
			  	}

			  	// Fail is none of the above commands are used
			  	else
					fail();

			  	break;
		  	}

		  	case 2:
		  	{
			  	// 'save _____' 
			  	if (substrings[0] == "save")
			  	{
				  	// Save successful
				  	if (SavingLoadingIO::SaveProjectToFile(holder, substrings[1], false) == SaveSuccess)
					  	std::cout << "File saved successfully." << std::endl;

				  	// Save file already exists
				  	else if (SavingLoadingIO::SaveProjectToFile(holder, substrings[1], false) == SaveAlreadyExists)
				  	{
					  	std::cout << "This file already exists. Would you like to overwrite it? (y/n)" << std::endl;

					  	std::string yn;
					  	std::cin >> yn;

					  	if (yn == "y")
					  	{
						  	SavingLoadingIO::SaveProjectToFile(holder, substrings[1], true);

						  	std::cout << "File saved successfully." << std::endl;
					  	}

					  	else
					  		std::cout << "File not saved." << std::endl;
				  	}
				  
				  	// Save error
				  	else 
				    	std::cout << "An error has occurred while trying to save. File not saved." << std::endl;
			  	}
			  
			  	// 'load _____'
			  	else if (substrings[0] == "load")
			  	{
			    	// Load unsuccessful
			    	if (SavingLoadingIO::LoadProject(holder, substrings[1]) == false)
			      		std::cout << "An error has occurred while trying to load. Make sure the file exists and is not currently open." << std::endl;
			    
			    	// Load successful
			    	else
			      		std::cout << "File loaded successfully." << std::endl;
			  	}

			  	// Fail if first substring is not 'save' or 'load'
			  	else
			   		fail();
			  
			  	break;
		  	}

		  	case 3:
		  	{
			  	// '_____ class _____' - Only possible option for the second substring
			  	if (substrings[1] == "class")
			  	{
				  	// 'add class _____' 
				  	if (substrings[0] == "add")
				  	{
				    	// Verify that the class does not already exist
				    	if (holder->CreateNewClass(substrings[2]) == 0)
				      		std::cout << "Class already exists." << std::endl;
				    
				    	// Class does not exist, created successfully
				    	else
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
			  	// 'edit _____ ...'
			  	if (substrings[0] == "edit")
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
			  
			  	else if (substrings[0] == "delete")
			  	{
			    	// delete field [class] [name]
			    	if (substrings[1] == "field")
			    	{
			      		int out = holder->DeleteField(substrings[2], substrings[3]);

						// Class does not exist
						if (out == ClassDoesntExist)
							std::cout << "Could not find a class by that name." << std::endl;
					
						// Field does not exist
						else if (out == ElementDoesntExist)
							std::cout << "Could not find a field by that name." << std::endl;

						// Field removed successfully
						else
							std::cout << "Field removed successfully." << std::endl;
			    	}
			    
			    	// delete method [class] [name]
			    	else if (substrings[1] == "method")
			    	{
						int out = holder->DeleteMethod(substrings[2], substrings[3]);

						// Class does not exist
						if (out == ClassDoesntExist)
							std::cout << "Could not find a class by that name." << std::endl;
					
						// Method does not exist
						else if (out == ElementDoesntExist)
							std::cout << "Could not find a method by that name." << std::endl;

						// Method removed successfully
						else
							std::cout << "Method removed successfully." << std::endl;
			    	}
			    
			    	// 'delete relationship _____ _____' 
			    	else if (substrings[1] == "relationship")
			    	{
			    		// Relationship deletion acceptable
			      		if (holder->DeleteRelationship(substrings[2], substrings[3]))
			        		std::cout << "Relationship deleted successfully." << std::endl;
			      
			      	// Deletion not acceptable
			      	else
			        	std::cout << "An error has occurred, relationship not deleted." << std::endl;
			    	}
			    
			    	// Fail if second substring is not 'method', 'field', or 'relationship'
			    	else
			      		fail();
			  	}
			  
			  	// Fail if first substring is not 'add', 'edit', or 'delete'
			  	else
			    	fail();
			  
			  	break;
	    	} 

		  	case 6:
		  	{
			  	if (substrings[0] == "add")
			  	{
				  	// Check and convert visibility
				  	int vis;
				  	if (substrings[5] == "public" || substrings[5] == "+")
				  		vis = 1;
				  	else if (substrings[5] == "private" || substrings[5] == "-")
				  		vis = 2;
				  	else if (substrings[5] == "protected" || substrings[5] == "#")
				  		vis = 3;
				  	else
				  	{
						std::cout << "Please enter a valid visibility." << std::endl;
						break;
				  	}

				  	// add field [class name] [field name] [type] [visibility]
				  	if (substrings[1] == "field")
				  	{
						int out = holder->AddField(substrings[2], substrings[3], substrings[4], vis);

						// Class does not exists
						if (out == ClassDoesntExist)
							std::cout << "Could not find a class by that name." << std::endl;
					
						// Field already exists in this class
						else if (out == ElementExists)
							std::cout << "This field already exists." << std::endl;

						// Field added successfully
						else
							std::cout << "Field added successfully." << std::endl;

						break;
				  	}

					// add method [class name] [field name] [type] [visibility]
				  	else if (substrings[1] == "method")
				  	{
						int out = holder->AddMethod(substrings[2], substrings[3], substrings[4], vis);

						// Class does not exists
						if (out == ClassDoesntExist)
							std::cout << "Could not find a class by that name." << std::endl;
					
						// Field already exists in this class
						else if (out == ElementExists)
							std::cout << "This method already exists." << std::endl;

						// Field added successfully
						else
							std::cout << "Method added successfully." << std::endl;

						break;
				  	}

				  	else 
				  		fail();
			  	}

				else if (substrings[0] == "edit")
				{
					if (substrings[1] == "field")
					{
						// edit field name [class name] [old field name] [new field name]
						if (substrings[2] == "name")
						{
							int out = holder->EditFieldName(substrings[3], substrings[4], substrings[5]);

							// Class does not exist
							if (out == ClassDoesntExist)
								std::cout << "Could not find a class by that name." << std::endl;
					
							// Error
							else if (out == ElementDoesntExist)
								std::cout << "An error has occurred." << std::endl;

							// Type changed successfully
							else
								std::cout << "Name changed successfully." << std::endl;

							break;
						}

						// edit field type [class name] [field name] [new type]
						else if (substrings[2] == "type")
						{
							int out = holder->EditFieldType(substrings[3], substrings[4], substrings[5]);

							// Class does not exist
							if (out == ClassDoesntExist)
								std::cout << "Could not find a class by that name." << std::endl;
					
							// Error
							else if (out == ElementDoesntExist)
								std::cout << "An error has occurred." << std::endl;

							// Type changed successfully
							else
								std::cout << "Return type changed successfully." << std::endl;

								break;
						}

						// edit field visibility [class name] [field name] [new visibility]
						else if (substrings[2] == "visibility")
						{
							// Check and convert visibility
				  			int out;

							// Check and convert visibility
				  			if (holder->GetVisibilityTypeFromString(substrings[5]))
							{
								out = holder->EditFieldVisibility(substrings[3], substrings[4], holder->GetVisibilityTypeFromString(substrings[5]));
							}

							// Class does not exist
							if (out == ClassDoesntExist)
								std::cout << "Could not find a class by that name." << std::endl;
							
							// Error
							else if (out == ElementDoesntExist)
								std::cout << "An error has occurred." << std::endl;

							// Type changed successfully
							else
								std::cout << "Visibility changed successfully." << std::endl;

							break;
						}

						else
							fail();
					}

					else if (substrings[1] == "method")
					{
						// edit method name [class name] [old method name] [new method name]
						if (substrings[2] == "name")
						{
							int out = holder->EditMethodName(substrings[3], substrings[4], substrings[5]);

							// Class does not exist
							if (out == ClassDoesntExist)
								std::cout << "Could not find a class by that name." << std::endl;
					
							// Error
							else if (out == ElementDoesntExist)
								std::cout << "An error has occurred." << std::endl;

							// Type changed successfully
							else
								std::cout << "Name changed successfully." << std::endl;

							break;
						}
						
						// edit method type [class name] [method name] [new type]
						else if (substrings[2] == "type")
						{
							int out = holder->EditMethodReturnType(substrings[3], substrings[4], substrings[5]);

							// Class does not exist
							if (out == ClassDoesntExist)
								std::cout << "Could not find a class by that name." << std::endl;
					
							// Error
							else if (out == ElementDoesntExist)
								std::cout << "An error has occurred." << std::endl;

							// Type changed successfully
							else
								std::cout << "Type changed successfully." << std::endl;

							break;
						}

						// edit method visibility [class name] [method name] [new visibility]
						else if (substrings[2] == "visibility")
						{
							int out;

							// Check and convert visibility
				  			if (holder->GetVisibilityTypeFromString(substrings[5]))
							{
								out = holder->EditMethodVisibility(substrings[3], substrings[4], holder->GetVisibilityTypeFromString(substrings[5]));
							}

				  			else
				  			{
								std::cout << "Please enter a valid visibility." << std::endl;
								break;
				  			}							

							// Class does not exist
							if (out == ClassDoesntExist)
								std::cout << "Could not find a class by that name." << std::endl;
							
							// Error
							else if (out == ElementDoesntExist)
								std::cout << "An error has occurred." << std::endl;

							// Type changed successfully
							else
								std::cout << "Visibility changed successfully." << std::endl;

							break;
						}

						else
							fail();
					}

					else
						fail();
				}

				else
					fail();
		  	}

			case 7:
			{
				if (substrings[0] == "add")
		    	{ 
				  	// add relationship
				  	if (substrings[1] == "relationship")
				  	{
				    	// Check that the objects are not identical - Object cannot have relationship to itself
				    	if (substrings[2] == substrings[3])
				      		std::cout << "An error has occurred. You cannot create a relationship from an object to itself." << std::endl;

						else if (holder->ValidateRelationshipType(substrings[4]) == false)
							std::cout << "An error has occurred. Please enter a valid relationship type." << std::endl;

						else if (holder->ValidateQuantifier(substrings[5]) == false || holder->ValidateQuantifier(substrings[6]) == false)
							std::cout << "An error has occurred. Please enter a valid relationship quantifier." << std::endl;
				    
					  	// Relationship acceptable
					  	else if (holder->AddRelationship(substrings[2], substrings[3], holder->GetRelationshipTypeFromString(substrings[4]), holder->GetQuantifierFromString(substrings[5]), holder->GetQuantifierFromString(substrings[6])))
						  	std::cout << "Relationship created successfully." << std::endl;

					  	// Relationship not acceptable and not created
					  	else
						  	std::cout << "An error has occurred, relationship not created." << std::endl;
				  	}

				  	// Fail if second substring is not 'relationship'
				  	else
					  	fail();
				}

				else if (substrings[0] == "edit")
				{
					if (substrings[1] == "relationship")
					{
						if (holder->ValidateRelationshipType(substrings[4]) == false)
							std::cout << "An error has occurred. Please enter a valid relationship type." << std::endl;

						else if (holder->ValidateQuantifier(substrings[5]) == false || holder->ValidateQuantifier(substrings[6]) == false)
							std::cout << "An error has occurred. Please enter a valid relationship quantifier." << std::endl;

						else if (holder->EditRelationship(substrings[2], substrings[3], holder->GetRelationshipTypeFromString(substrings[4]), holder->GetQuantifierFromString(substrings[5]), holder->GetQuantifierFromString(substrings[6])))
							std::cout << "Relationship edited successfully." << std::endl;

						else
							fail();
					}

					else	
						fail();
				}

				else 
					fail();
			}
		    
		  	// Fail if too many commands are entered
		  	default:
		  	{
			  	if (substrings.size() > 7 || substrings.size() == 5)
			  		fail();
			  
			  		break;
		  	}
		}
	} while (run);
}