#ifndef LOGIC_H
#define LOGIC_H


#include<iostream>
#include<string>
#include<vector>
#include "Task.h"


class Logic {
private:
	std::string userInput;
	std::string userCommand;
	Task task;
	std::vector<Task> listOfTasks;

	Task retrieveTask(std::string);

public:
	Logic();
	~Logic();

	int getParameter(std::string&, std::string&);
	int displayTask(std::string);
	int updateTask(Task);
	int addTask(Task); //Task object here instead?
	int deletetask(std::string);
	int clearList();

	Task splitTask(std::string);

};

#endif
