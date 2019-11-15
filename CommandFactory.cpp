#include <unordered_map>

#include "CommandFactory.h"

namespace {

using namespace std::string_literals;

static const std::unordered_map<std::string, int> PARAM_COUNTS{{

    // core
    {"help"s, 1},
    {"list"s, 1},
    {"exit"s, 1},
    {"save"s, 2},
    {"load"s, 2},
    // add
    {"add_class"s, 2},
    {"add_field"s, 5},
    {"add_method"s, 6},
    {"add_relationship"s, 4}

    // edit_class <className> <newName>
    {"edit_class"s, 3},
    // edit_field <attr> <className> <fieldName> <newValue>
    {"edit_field"s, 5},
    // edit_method <attr> <className> <methodName> <newValue>
    {"edit_method"s, 5},
    // edit_relationship <class1> <class2> <newType>
    {"edit_relationship"s, 4},

    // delete_class <name>
    {"delete_class"s, 2},
    // delete_field <class> <name>
    {"delete_field"s, 3},
    // delete_method <class> <name>
    {"delete_method"s, 3},
    // delete_relationship <class1> <class2>
    {"delete_relationship"s, 3}}};

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
  if (!checkParameterCount(cmdLine)) {
    return make_unique<ErrorCommand>(os, "invalid parameter count");
  }
  if (cmdName == "add_class"s) {
    return make_unique<AddClassCommand>(cmdLineArgs[1]);
  }
  // and for each other command
}
