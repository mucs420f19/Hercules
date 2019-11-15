#pragma once

#include <iostream>

#include "Model.h"

class Command {
public:
  virtual void execute() const = 0;

  static void setModelInstance(Model *instance);

  static const std::vector<std::string>& allCommands();

  static const std::string& helpFor(const std::string&)
;
private:
  static Model *modelInstance;
};

class ErrorCommand : public Command {

public:
  ErrorCommand(std::ostream& where, const std::string &name);

  virtual void execute() const override;

private:
  std::ostream& where;
  std::string mName;
};


class AddClassCommand : public Command {

public:
  AddClassCommand(const std::string &name);

  virtual void execute() const override;

private:
  std::string mName;
};

class AddRelationshipCommand : public Command {
  AddRelationshipCommand (const std::string &parent, const std::string &child, const std::string &type);

  virtual void execute() const override;

private:
  std::string mParent;
  std::string mChild;
  std::string mType;
};
