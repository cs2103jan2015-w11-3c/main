#ifndef TASK_H
#define TASK_H


#include<iostream>
#include<string>
#include<vector>
#include "Parser.h"


class Task {
protected:
	std::string _description;
	bool _isDone;
	int _taskType;
	//_taskType = 1: floating
	//_taskType = 2: timed
	//_taskType = 3: deadline.

public:
	Task();
	~Task();
	void setDescription(std::string description);
	void setAsDone();
	std::string getDescription();
	bool isDone();
	int getTaskType();
	
	virtual std::string toString();
	virtual int checkTodayDay();
	virtual int checkTodayMonth();

	//virtual std::string getDateString();
	//virtual std::string getTimeString();
};

#endif