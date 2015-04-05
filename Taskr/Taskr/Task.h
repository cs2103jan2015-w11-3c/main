#ifndef TASK_H
#define TASK_H


#include<iostream>
#include<string>
#include<vector>
#include "Parser.h"

struct DateTime {
	int date[2]; //[dd, mm]
	int time[2]; //[hh, mm]
};

class Task {
private:
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
	void setTaskType(int);

	virtual std::string toString();
};

#endif