#include "Command.h"
#include <unordered_map>

Model *Command::modelInstance = nullptr;

void Command::setModelInstance(Model *instance) {
  Command::modelInstance = instance;
}

const std::vector<std::string> &Command::allCommands() {
	//TODO
	std::vector<std::string> temp = { "temp" };
	return temp;
}

const std::string &Command::helpFor(const std::string &name) {
	static std::unordered_map<std::string, std::string> HELP{
		{{"exit", "exit\n"
				  "  quits the application\n"
				  "    parameters: none\n"},
	   {"add_class", "add_class (className)\n"
					 "  adds a new class to the UML diagram\n"
					 "    parameters:\n"
					 "    - className: name for the new class\n"}

      }};
	//TODO
	return "temp";
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
	RelationshipType &type)
    : mParent(parent), mChild(child), mType(type) {}

void AddRelationshipCommand::execute() const 
{
  Command::modelInstance->addRelationship(mParent, mChild, mType);
}
