#ifndef LOGIC_H
#define LOGIC_H


#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include "Task.h"
#include "FloatingTask.h"
#include "TimedTask.h"
#include "DeadlineTask.h"
#include "Parser.h"
#include "Storage.h"
#include "History.h"


class Logic {
private:
	Parser _parse;
	History _history;
	Storage _store;
	std::vector<Task*> _listOfTasks;
	std::string _confirmationMessage;
	int _doneTasksCount;

public:
	Logic();
	~Logic();

	std::string executeCommand(std::string userInput);
	std::string getCommand();
	void executeAdd(std::ostringstream&);

	void addTask(Task*, std::ostringstream&);
	void displayList(std::ostringstream&);
	void deleteTask(std::ostringstream&);
	void editTask(int, Task*, std::ostringstream&);
	void setDone(std::ostringstream&);
	void undoLastAction(std::ostringstream&);
	void searchList(std::string, std::ostringstream&);
	void changeFilePath(std::string, std::ostringstream&);
	void showHelp(std::ostringstream&);

	void initializeListOfTasks();
	bool isValidIndex(int);
	bool isRepeated(Task*);
	bool isActionConfirmed();
	void sortDoneTasks();
	void listToString(std::vector<Task*>, std::ostringstream&);
	void sortTasksByTime(std::vector<Task*>);
	bool checkTiming(Task*, Task*);
	void swapTasks(Task*, Task*);

	static const std::string MESSAGE_ADDED;
	static const std::string MESSAGE_DELETED;
	static const std::string MESSAGE_MARK_DONE;
	static const std::string MESSAGE_ERROR_TASK_NOT_EXIST;
	static const std::string MESSAGE_EDITED;
	static const std::string MESSAGE_UNDO;
	static const std::string MESSAGE_FILEPATH_CHANGED;
	static const std::string MESSAGE_OPERATION_NOT_EXECUTED;
	static const std::string MESSAGE_CONFIRM_ACTION;
	static const std::string MESSAGE_HELP;

	static const std::string ERROR_REPEATED_TASK;
	static const std::string ERROR_INDEX_OUT_OF_RANGE;
	static const std::string ERROR_EMPTY_LIST;
	static const std::string ERROR_INVALID_DESCRIPTION;
	static const std::string ERROR_USER_COMMAND_INVALID;
	static const std::string ERROR_NOTHING_TO_UNDO;

	static const int FLOATING_TASK;
	static const int TIMED_TASK;
	static const int DEADLINE_TASK;


};

#endif
