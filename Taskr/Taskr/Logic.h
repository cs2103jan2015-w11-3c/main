#ifndef LOGIC_H
#define LOGIC_H


#include<iostream>
#include<string>
#include<vector>
#include "Task.h"
#include "Parser.h"
#include "Storage.h"
#define USER_INPUT_EXIT -1
#define USER_COMMAND_INVALID -2



class Logic {
private:
	Parser _parse;
	Storage _store;
	Task _task;
	std::vector<Task> _listOfTasks;
	int _confirmationMessageIndex;

public:
	Logic();
	~Logic();

	int executeCommand(std::string userInput);
	std::string getCommand();
	//WEEK 10 ADDITIONS
	std::string displayAll();
	void initializeListOfTasks();
	//_____
};

#endif
