#pragma once

#include <iostream>

#include "Model.h"
#include "SavingLoadingIO.h"

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
	AddRelationshipCommand(const std::string& parent, const std::string& child, const std::string& type);

	virtual void execute() const override;

private:
	std::string mParent;
	std::string mChild;
	RelationshipType mType;
};

class EditRelationshipCommand : public Command {
public:
	EditRelationshipCommand(const std::string& parent, const std::string& child, const std::string& type);

	virtual void execute() const override;

private:
	std::string mParent;
	std::string mChild;
	RelationshipType mType;
};

class DeleteRelationshipCommand : public Command {
public:
	DeleteRelationshipCommand(const std::string& parent, const std::string& child);

	virtual void execute() const override;

private:
	std::string mParent;
	std::string mChild;
};

class AddFieldCommand : public Command {
public:
	AddFieldCommand(const std::string& className, const std::string& fieldName, const std::string& fieldType, const std::string& fieldVisibility);

	virtual void execute() const override;

private:
	std::string mClassName, mFieldName, mFieldType;
	Visibility mFieldVisibility;
};

class EditFieldCommand : public Command {
public:
	EditFieldCommand(const std::string& whichAttr, const std::string& className, const std::string& fieldName, const std::string& newValue);

	virtual void execute() const override;

private:
	std::string mClassName, mFieldName, mNewValue, mWhichAttr;
};

class DeleteFieldCommand : public Command {
public:
	DeleteFieldCommand(const std::string& className, const std::string& fieldName);

	virtual void execute() const override;

private:
	std::string mClassName, mFieldName;
};

class AddMethodCommand : public Command {
public:
	AddMethodCommand(const std::string& className, const std::string& methodName, const std::string& methodType, const std::string& methodVisibility);

	virtual void execute() const override;

private:
	std::string mClassName, mMethodName, mMethodType;
	Visibility mMethodVisibility;
};

class EditMethodCommand : public Command {
public:
	EditMethodCommand(const std::string& whichAttr, const std::string& className, const std::string& methodName, const std::string& newValue);

	virtual void execute() const override;

private:
	std::string mClassName, mMethodName, mNewValue, mWhichAttr;
};

class DeleteMethodCommand : public Command {
public:
	DeleteMethodCommand(const std::string& className, const std::string& methodName);

	virtual void execute() const override;

private:
	std::string mClassName, mMethodName;
};

class AddParameterCommand : public Command {
public:
	AddParameterCommand(const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& ParameterType);

	virtual void execute() const override;

private:
	std::string mClassName, mMethodName, mParameterName, mParameterType;
};

class EditParameterCommand : public Command {
public:
	EditParameterCommand(const std::string& whichAttr, const std::string& className, const std::string& methodName, const std::string& ParameterName, const std::string& NewValue);

	virtual void execute() const override;

private:
	std::string mClassName, mMethodName, mParameterName, mNewValue, mWhichAttr;
};

class DeleteParameterCommand : public Command {
public:
	DeleteParameterCommand(const std::string& className, const std::string& methodName, const std::string& ParameterName);

	virtual void execute() const override;

private:
	std::string mClassName, mMethodName, mParameterName;
};

class ListCommand : public Command {
public:
	ListCommand();

	virtual void execute() const override;
};

class ExitCommand : public Command {
public:
	ExitCommand();

	virtual void execute() const override;
};

class SaveOverwriteCommand : public Command {
public:
	SaveOverwriteCommand(const std::string& name);

	virtual void execute() const override;
private:
	std::string mName;
};

class SaveCommand : public Command {
public:
	SaveCommand(const std::string& name);
	SaveCommand(const std::string& name, const std::string& overwrite);
	virtual void execute() const override;
private:
	std::string mName;
	std::string mOverwrite;
};

class LoadCommand : public Command {
public:
	LoadCommand(const std::string& name);

	virtual void execute() const override;
private:
	std::string mName;
};

class HelpCommand : public Command {
public:
  HelpCommand ();

  virtual void execute() const override;

};

class HelpForCommand : public Command {
public:
  HelpForCommand (const std::string &name);

  virtual void execute() const override;

private:
  std::string mName;
};
