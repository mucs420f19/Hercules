#include "Command.h"
#include <unordered_map>

Model *Command::modelInstance = nullptr;

void Command::setModelInstance(Model *instance) {
  Command::modelInstance = instance;
}

const std::vector<std::string>& Command::allCommands() {
	static std::vector<std::string> myvector{ "help", "help_for", "list", "save", "load", "exit", "",
	                                      "add_class", "add_field", "add_method", "add_parameter", "add_relationship", "",
										  "edit_class", "edit_field", "edit_method", "edit_parameter", "edit_relationship", "",
								  "delete_class", "delete_field", "delete_method", "delete_parameter", "delete_relationship"};
	return myvector;
}

const std::string &Command::helpFor(const std::string &name) {
	static std::unordered_map<std::string, std::string> HELP{
		{"help", "help\n"
		         "  Displays a list of usable commands.\n"
				 "    Parameters: N/A\n"},
		{"help_for", "help_for (command)\n"
		             "  Displays information relating to a given command.\n"
					 "    Paramaters:\n"
					 "    - command: Information will be shown about this given command.\n"},
		{"list", "list\n"
		         "  Displays all existing classes, their attributes, and relationships.\n"
				 "    Paramaters: N/A\n"},
		{"save", "save (fileName)\n"
		         "  Saves the current UML project to a file.\n"
				 "    Parameters:\n"
				 "    - fileName: The file that the project will be saved to.\n"},
		{"load", "load (fileName)\n"
		         "  Loads a UML project from a file.\n"
				 "    Paramters:\n"
				 "    - fileName: The file containing the project to be loaded.\n"},
		{"exit", "exit\n"
                 "  Quits the application.\n"
                 "    Parameters: N/A\n"},

        {"add_class", "add_class (className)\n"
                      "  Adds a new class to the UML diagram.\n"
                      "    Parameters:\n"
                      "    - className: Name of the new class.\n"},
		{"add_field", "add_field (className) (fieldName) (type) (visibility)\n"
                      "  Adds a new field to an existing class.\n"
                      "    Parameters:\n"
                      "    - className: The new field will be added to this class.\n"
					  "    - fieldName: The name of the new field.\n"
					  "    - type: The return type of the new field.\n"
					  "    - visibility: The visibility of the new field.\n"},
		{"add_method", "add_method (className) (methodName) (type) (visibility)\n"
                      "  Adds a new method to an existing class.\n"
                      "    Parameters:\n"
                      "    - className: The name of the class containing the method.\n"
					  "    - methodName: The name of the new method.\n"
					  "    - type: The return type of the new method.\n"
					  "    - visibility: The visibility of the new method.\n"},
		{"add_parameter", "add_parameter (className) (methodName) (parameterName) (type)\n"
						  "  Adds a new parameter to an existing method.\n"
						  "    Parameters:\n"
						  "    - className: The name of the class containing the method.\n"
						  "    - methodName: The name of the method containing the parameter.\n"
						  "    - parameterName: The name of the new parameter.\n"
						  "    - type: The return type of the new parameter.\n"},
		{"add_relationship", "add_relationship (parent) (child) (type)\n"
						  "  Adds a relationship between two classes.\n"
						  "    Parameters:\n"
						  "    - parent: The class that will be the parent in the relationship"
						  "    - type: The return type of the new parameter.\n"},
		{"edit_class",	"edit_class (className) (newName)\n"
						  "	Edits the name of an existing class.\n"
						  "    Parameters:\n"
						  "    - classname: The currently existing class.\n"
						  "    - newName:  The name to change the current class too.\n"},
	    {"edit_field",  "edit_field (attr) (className) (fieldName) (newValue)\n"
	    				"  Edits an existing field in a class.\n"
	    				"  Parameters:\n"
	    				"  - attr:  Type, name, visibility\n"
	    				"  - className: Name of the class where a field can be edited.\n"
	    				"  - fieldName: Name of the field to be edited.\n"
	    				"  - newValue: Name of the new field attr.\n"},
	    {"edit_method",  "edit_method (attr) (className) (methodName) (newValue)\n"
	    				"  Edits an existing method in a class.\n"
	    				"  Parameters:\n"
	    				"	-attr:  Type, name, visibility\n"
	    				"	-className: Name of the class where a method can be editing.\n"
	    				"	-methodName: Name of the method to be edited.\n"
	    				"	-newValue: Name of the new method attr\n."},
		{"edit_parameter", "edit_parameter (attr) (className) (methodName) (parameterName) (newValue)\n"
						"  Edits the parameter of an existing class.\n"
						"  Parameters:\n"
						"	-attr: Type, name\n"
						"	-className:  Name of the class.\n"
						"	-methodName: Name of method.\n"
						"	-parameterName:  Name of the parameter.\n"
						"	-newValue:  Name of the new parameter attr.\n"},
		{"edit_relationship",	"edit_relationship (classOne) (classTwo) (newType)\n"
						"	Edits the relationship between two classes.\n"
						"	Parameters:\n"
						"	 -classOne: Name of first class.\n"
						"	 -classTwo: Name of second class.\n"
						"	 -newType:  New type of relationship. Aggregation, Composition, Association, Dependency.\n"},
		{"delete_class",	"delete_class (name)\n"
						"  Deletes an existing class.\n"
						"  Parameters:\n"
						"	-name: Name of the class to delete.\n"},
		{"delete_field",	"delete_field (class) (fieldName)\n"
						"  Deletes a field from an existing class.\n"
						"  Parameters:\n"
						"	-class:  The class to delete the field from.\n"
						"	-fieldName:  The field to delete from the class.\n"},
		{"delete_method",	"delete_method (class) (methodName)\n"
						"  Deletes a method from an existing class.\n"
						"  Parameters:\n"
						"	-class:  The class to delete the method from.\n"
						"	-methodName:  The method to dlete from the class.\n"},
		{"delete_parameter",	"delete_parameter (class) (methodName) (paramName)\n"
						"  Deletes a parameter from a method exisiting within a class.\n"
						"  Parameters:\n"
						"	-class:  The class to delete the method from.\n"
						"	-methodName:  The method to delete the parameter from.\n"
						"	-paramName:  The parameter to delete.\n"},
		{"delete_relationship",	"delete_relationship (classOne) (classTwo)\n"
						"  Deletes a relationship between two classes.\n"
						"  Parameters:\n"
						"	-classOne:  The first class from the relationship.\n"
						"	-classTwo:  The second class from the relationship.\n"}
					
      };
	
	auto out = HELP.find(name);
	if (out == HELP.end())
	{
		return "Invalid command";
	}
	return out->second;
}

ErrorCommand::ErrorCommand(std::ostream &where, const std::string &name): mWhere(where), mName (name) {}

void ErrorCommand::execute() const
{
  mWhere << mName << std::flush;
}


AddClassCommand::AddClassCommand(const std::string &name) : mName(name) {}

void AddClassCommand::execute() const
{
  Command::modelInstance->addClass(mName);
}

EditClassCommand::EditClassCommand(const std::string &oldname, const std::string &name) : mOldname(oldname) ,mName(name) {}

void EditClassCommand::execute() const
{
	Command::modelInstance->editClass(mOldname,mName);
}

DeleteClassCommand::DeleteClassCommand(const std::string &name) : mName(name) {}

void DeleteClassCommand::execute() const
{
	Command::modelInstance->removeClass(mName);
}

AddRelationshipCommand::AddRelationshipCommand(const std::string &parent,
                                        const std::string &child,
	const std::string &type)
    : mParent(parent), mChild(child), mType(RelationshipFromString(type)) {}

void AddRelationshipCommand::execute() const 
{
  Command::modelInstance->addRelationship(mParent, mChild, mType);
}

ListCommand::ListCommand() {}

void ListCommand::execute() const
{
	Command::modelInstance->list();
}

HelpCommand::HelpCommand(){}

void HelpCommand::execute() const
{
	const std::vector<std::string>& test = allCommands();
	for (auto & i : test)
	{
		std::cout << i << std::endl;
	}
}
HelpForCommand::HelpForCommand(const std::string &name) : mName(name) {}

void HelpForCommand::execute() const
{
	std::cout << helpFor(mName) << std::endl;
}

EditRelationshipCommand::EditRelationshipCommand(const std::string& parent, const std::string& child, const std::string& type)
	: mParent(parent), mChild(child), mType(RelationshipFromString(type)) {}

void EditRelationshipCommand::execute() const
{
	Command::modelInstance->editRelationship(mParent, mChild, mType);
}

DeleteRelationshipCommand::DeleteRelationshipCommand(const std::string& parent, const std::string& child)
	: mParent(parent), mChild(child) {}

void DeleteRelationshipCommand::execute() const
{
	Command::modelInstance->removeRelationship(mParent, mChild);
}

AddFieldCommand::AddFieldCommand(const std::string& className, const std::string& fieldName, const std::string& fieldType, const std::string& fieldVisibility)
	: mClassName(className), mFieldName(fieldName), mFieldType(fieldType), mFieldVisibility(VisibilityFromString(fieldVisibility)) {}

void AddFieldCommand::execute() const
{
	Command::modelInstance->addField(mClassName, mFieldName, mFieldType, mFieldVisibility);
}

EditFieldCommand::EditFieldCommand(const std::string& whichAttr, const std::string& className, const std::string& fieldName, const std::string& newValue)
	: mClassName(className), mFieldName(fieldName), mNewValue(newValue), mWhichAttr(whichAttr) {}

void EditFieldCommand::execute() const
{
	Command::modelInstance->editField(mWhichAttr, mClassName, mFieldName, mNewValue);
}

DeleteFieldCommand::DeleteFieldCommand(const std::string& className, const std::string& fieldName)
	: mClassName(className), mFieldName(fieldName) {}

void DeleteFieldCommand::execute() const
{
	Command::modelInstance->deleteField(mClassName, mFieldName);
}

AddMethodCommand::AddMethodCommand(const std::string& className, const std::string& methodName, const std::string& methodType, const std::string& methodVisibility)
	: mClassName(className), mMethodName(methodName), mMethodType(methodType), mMethodVisibility(VisibilityFromString(methodVisibility)) {}

void AddMethodCommand::execute() const
{
	Command::modelInstance->addMethod(mClassName, mMethodName, mMethodType, mMethodVisibility);
}

EditMethodCommand::EditMethodCommand(const std::string& whichAttr, const std::string& className, const std::string& methodName, const std::string& newValue)
	: mClassName(className), mMethodName(methodName), mNewValue(newValue), mWhichAttr(whichAttr) {}

void EditMethodCommand::execute() const
{
	Command::modelInstance->editMethod(mWhichAttr, mClassName, mMethodName, mNewValue);
}

DeleteMethodCommand::DeleteMethodCommand(const std::string& className, const std::string& methodName)
	: mClassName(className), mMethodName(methodName) {}

void DeleteMethodCommand::execute() const
{
	Command::modelInstance->deleteMethod(mClassName, mMethodName);
}

AddParameterCommand::AddParameterCommand(const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& ParameterType)
	: mClassName(className), mMethodName(methodName), mParameterName(ParameterName), mParameterType(ParameterType) {}

void AddParameterCommand::execute() const
{
	Command::modelInstance->addParameter(mClassName, mMethodName, mParameterName, mParameterType);
}

EditParameterCommand::EditParameterCommand(const std::string& whichAttr, const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& NewValue)
	: mClassName(className), mMethodName(methodName), mParameterName(ParameterName), mNewValue(NewValue), mWhichAttr(whichAttr) {}

void EditParameterCommand::execute() const
{
	Command::modelInstance->editParameter(mClassName, mMethodName, mParameterName, mNewValue, mWhichAttr);
}

DeleteParameterCommand::DeleteParameterCommand(const std::string& className, const std::string& methodName, const std::string& ParameterName)
	: mClassName(className), mMethodName(methodName), mParameterName(ParameterName) {}

void DeleteParameterCommand::execute() const
{
	Command::modelInstance->deleteParameter(mClassName, mMethodName, mParameterName);
}

ExitCommand::ExitCommand()
{
}

void ExitCommand::execute() const
{
	//TODO ask user if they want to save any unsaved work
	exit(0);
}

SaveOverwriteCommand::SaveOverwriteCommand(const std::string& name)
	: mName(name) {}

void SaveOverwriteCommand::execute() const
{
	SavingLoadingIO::SaveProjectToFile(modelInstance, mName, true);
}

LoadCommand::LoadCommand(const std::string& name)
	: mName(name) {}

void LoadCommand::execute() const
{
	if (Command::modelInstance == nullptr)
	{
		Model * test = new Model;
		setModelInstance(test);
	}
	SavingLoadingIO::LoadProject(modelInstance, mName);
}

SaveCommand::SaveCommand(const std::string& name)
	: mName(name) {}

SaveCommand::SaveCommand(const std::string& name, const std::string& overwrite)
	: mName(name),mOverwrite(overwrite) {}

void SaveCommand::execute() const
{
	if (mOverwrite == "yes")
	{
		SavingLoadingIO::SaveProjectToFile(modelInstance, mName, true);
	}
	else 
	{

		SavingLoadingIO::SaveProjectToFile(modelInstance, mName);
	}
}
