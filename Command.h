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
protected:
  static Model *modelInstance;
};

class ErrorCommand : public Command {

public:
  ErrorCommand(std::ostream& where, const std::string &name);

  virtual void execute() const override;

private:
  std::ostream& mWhere;
  std::string mName;
};


class AddClassCommand : public Command {

public:
  AddClassCommand(const std::string &name);

  virtual void execute() const override;

private:
  std::string mName;
};

class EditClassCommand : public Command {

public:
	EditClassCommand(const std::string &oldname, const std::string &name);

	virtual void execute() const override;

private:
	std::string mOldname;
	std::string mName;
};

class DeleteClassCommand : public Command {

public:
	DeleteClassCommand(const std::string &name);

	virtual void execute() const override;

private:
	std::string mName;
};

class AddRelationshipCommand : public Command {
public:
  AddRelationshipCommand (const std::string &parent, const std::string &child, const std::string &type);

  virtual void execute() const override;

private:
  std::string mParent;
  std::string mChild;
  RelationshipType mType;
};

class ListCommand : public Command {
public:
	ListCommand();

	virtual void execute() const override;
};
