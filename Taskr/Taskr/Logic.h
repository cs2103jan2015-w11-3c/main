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
#define SUCCESS 1
#define ERROR_REPEATED_TASK 21
#define ERROR_INDEX_OUT_OF_RANGE 22
#define ERROR_EMPTY_LIST 23
#define ERROR_INVALID_DESCRIPTION 24


class Logic {
private:
	Parser _parse;
	Storage _store;
	//Task _task;
	std::vector<Task> _listOfTasks;
	int _confirmationMessageIndex;

public:
	Logic();
	~Logic();

	int executeCommand(std::string userInput);
	std::string getCommand();
	//WEEK 10 ADDITIONS
	int addTask(Task);
	int displayList();
	int deleteTask(int);
	int editTask(int, Task);
	void initializeListOfTasks();
	bool isValidIndex(int);
	bool isRepeated(Task);
	//_____
};

#endif
