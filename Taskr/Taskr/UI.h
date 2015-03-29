#ifndef UI_H
#define UI_H

#include<iostream>
#include <vector>
#include "Logic.h"
#include "Task.h"

class UI {
private:
	Logic _logic;

public:
	UI();
	~UI();

	static const std::string MESSAGE_WELCOME;
	static const std::string MESSAGE_ADDED;
	static const std::string MESSAGE_DELETED;
	static const std::string MESSAGE_EDITED;
	static const std::string MESSAGE_TASK_EXISTS;
	static const std::string MESSAGE_ERROR_TASK_NOT_EXIST;
	static const std::string MESSAGE_EMPTY;
	static const std::string MESSAGE_USER_COMMAND_INVALID;
	static const std::string MESSAGE_INDEX_INVALID;
	static const std::string MESSAGE_MARK_DONE;

	void readUserInput();
	void printConfirmationMessage(std::string);
	//void printListOfTasks();
};

#endif