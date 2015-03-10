#ifndef UI_H
#define UI_H


#include<iostream>
#include <vector>
#include "Logic.h"
#include "Task.h"

class UI {
private:
	Logic logic;

public:
	UI();
	~UI();

	//const std::string MESSAGE_WELCOME;
	//const std::string MESSAGE_ADDED;
	//const std::string MESSAGE_DELETED;
	//const std::string MESSAGE_EDITED;
	//const std::string MESSAGE_TASK_IS_EXISTED;
	//const std::string MESSAGE_ERROR_TASK_NOT_EXIST;
	//const std::string MESSAGE_EMPTY;

	const std::string MESSAGE_WELCOME = "Welcome to Taskr! Taskr is ready to use.";
	const std::string MESSAGE_ADDED = "New task added to Taskr";
	const std::string MESSAGE_DELETED = "Task deleted from Taskr";
	const std::string MESSAGE_EDITED = "Task has been edited to new task";
	const std::string MESSAGE_TASK_EXISTS = "Task already exists";
	const std::string MESSAGE_ERROR_TASK_NOT_EXIST = "Task does not exist";
	const std::string MESSAGE_EMPTY = "Taskr is empty.";
	const std::string MESSAGE_USER_COMMAND_INVALID = "Command is invalid.";
	const std::string MESSAGE_INDEX_INVALID = "Index entered is invalid.";



	void readUserInput();
	void printConfirmationMessage(int);
	//void printListOfTasks();
};

#endif