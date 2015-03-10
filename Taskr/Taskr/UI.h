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

	const std::string MESSAGE_WELCOME;
	const std::string MESSAGE_ADDED;
	const std::string MESSAGE_DELETED;
	const std::string MESSAGE_EDITED;
	const std::string MESSAGE_TASK_IS_EXISTED;
	const std::string MESSAGE_ERROR_TASK_NOT_EXIST;
	const std::string MESSAGE_EMPTY;

	void readUserInput();
	void printConfirmationMessage(int);
	//void printListOfTasks();
};

#endif