#include <unordered_map>

#include "CommandFactory.h"

namespace {

using namespace std::string_literals;

static const std::unordered_map<std::string, int> PARAM_COUNTS{{

    // core
    {"help", 1},
    {"list", 1},
    {"exit", 1},
    {"save", 2},
    {"load", 2},
    // add
    {"add_class", 2},
    {"add_field", 5},
    {"add_method", 6},
    {"add_relationship", 4},

    // edit_class <className> <newName>
    {"edit_class", 3},
    // edit_field <attr> <className> <fieldName> <newValue>
    {"edit_field", 5},
    // edit_method <attr> <className> <methodName> <newValue>
    {"edit_method", 5},
    // edit_relationship <class1> <class2> <newType>
    {"edit_relationship", 4},

    // delete_class <name>
    {"delete_class", 2},
    // delete_field <class> <name>
    {"delete_field", 3},
    // delete_method <class> <name>
    {"delete_method", 3},
    // delete_relationship <class1> <class2>
    {"delete_relationship", 3}}};

bool checkParameterCount(const std::vector<std::string> &cmdLine) {
  if (cmdLine.empty())
    return false;
  auto iter = PARAM_COUNTS.find(cmdLine.front());
  if (iter == PARAM_COUNTS.end()) {
    return false;
  }
  return iter->second == cmdLine.size();
}

} // namespace

std::unique_ptr<Command>
make_command(std::ostream& os, const std::vector<std::string> &cmdLineArgs) {
  const std::string &cmdName = cmdLineArgs.front();
  if (!checkParameterCount(cmdLineArgs)) {
    return std::make_unique<ErrorCommand>(os, "invalid parameter count");
  }
  if (cmdName == "add_class") {
    return std::make_unique<AddClassCommand>(cmdLineArgs[1]);
  }
  // and for each other command
  if (cmdName == "edit_class") {
	  return std::make_unique<EditClassCommand>(cmdLineArgs[1], cmdLineArgs[2]);
  }
  if (cmdName == "delete_class") {
	  return std::make_unique<DeleteClassCommand>(cmdLineArgs[1]);
  }
  if (cmdName == "add_field") {
	  return std::make_unique<AddFieldCommand>(cmdLineArgs[1], cmdLineArgs[2], cmdLineArgs[3], cmdLineArgs[4]);
  }
  if (cmdName == "edit_field") {
	  return std::make_unique<EditFieldCommand>(cmdLineArgs[1], cmdLineArgs[2], cmdLineArgs[3], cmdLineArgs[4]);
  }
  if (cmdName == "delete_field") {
	  return std::make_unique<DeleteFieldCommand>(cmdLineArgs[1], cmdLineArgs[2]);
  }
  if (cmdName == "add_method") {
	  return std::make_unique<AddMethodCommand>(cmdLineArgs[1], cmdLineArgs[2], cmdLineArgs[3], cmdLineArgs[4]);
  }
  if (cmdName == "edit_method") {
	  return std::make_unique<EditMethodCommand>(cmdLineArgs[1], cmdLineArgs[2], cmdLineArgs[3], cmdLineArgs[4]);
  }
  if (cmdName == "delete_method") {
	  return std::make_unique<DeleteMethodCommand>(cmdLineArgs[1], cmdLineArgs[2]);
  }
  if (cmdName == "add_relationship") {
	  return std::make_unique<AddRelationshipCommand>(cmdLineArgs[1], cmdLineArgs[2], cmdLineArgs[3]);
  }
  if (cmdName == "edit_relationship") {
	  return std::make_unique<EditRelationshipCommand>(cmdLineArgs[1], cmdLineArgs[2], cmdLineArgs[3]);
  }
  if (cmdName == "delete_relationship") {
	  return std::make_unique<DeleteRelationshipCommand>(cmdLineArgs[1], cmdLineArgs[2]);
  }
  if (cmdName == "help") {
	  return std::make_unique<HelpCommand>();
  }
  if (cmdName == "list") {
	  return std::make_unique<ListCommand>();
  }
  if (cmdName == "exit") {
	  return std::make_unique<ExitCommand>();
  }
  if (cmdName == "save") {
	  return std::make_unique<SaveCommand>(cmdLineArgs[1]);
  }
  if (cmdName == "load") {
	  return std::make_unique<LoadCommand>(cmdLineArgs[1]);
  }
}
