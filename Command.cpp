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
		{"exit", "exit\n"
                  "  quits the application\n"
                  "    parameters: none\n"},
        {"add_class", "add_class (className)\n"
                     "  adds a new class to the UML diagram\n"
                     "    parameters:\n"
                     "    - className: name for the new class\n"}

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
	if (Command::modelInstance == nullptr)
	{
		Model * test = new Model;
		setModelInstance(test);
	}
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
}

LoadCommand::LoadCommand(const std::string& name)
	: mName(name) {}

void LoadCommand::execute() const
{
}

SaveCommand::SaveCommand(const std::string& name)
	: mName(name) {}

void SaveCommand::execute() const
{
}
