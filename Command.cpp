#include "Command.h"
#include <unordered_map>

Model *Command::modelInstance = nullptr;

void Command::setModelInstance(Model *instance) {
  Command::modelInstance = instance;
}

const std::vector<std::string> &Command::allCommands() {

	std::vector<std::string> commands = { "help", "help_for", "list", "save", "load", "exit", "",
	                                      "add_class", "add_field", "add_method", "add_relationship", "",
										  "edit_class", "edit_field", "edit_method", "edit_relationship", "",
										  "delete_class", "delete_field", "delete_method", "delete_relationship" };

	return commands;
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

	return (*out).second;
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
    : mParent(parent), mChild(child), mType(FromString(type)) {}

void AddRelationshipCommand::execute() const 
{
  Command::modelInstance->addRelationship(mParent, mChild, mType);
}

ListCommand::ListCommand() {}

void ListCommand::execute() const
{
	Command::modelInstance->list();
}

HelpCommand::HelpCommand(const std::vector<std::string> &vectorCommands) : mVector(vectorCommands) {}

void HelpCommand::execute() const
{
	mVector = allCommands();

	for (auto i : mVector)
		std::cout << i << std::endl;
}

HelpForCommand::HelpForCommand(const std::string &name) : mName(name) {}

void HelpForCommand::execute() const
{
	std::cout << helpFor(mName);
}