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
	void setTaskType(int);
	std::string getDescription();
	bool isDone();
	int getTaskType();
	
	virtual std::string toString();
	virtual int checkDay();
	virtual int checkMonth();
	virtual int checkHour();
	virtual int checkMinute();

	virtual int getDueTimeHour();
	virtual int getDueTimeMinute();
	virtual int getDueDateDay();
	virtual int getDueDateMonth();

	virtual int getStartTimeHour();
	virtual int getStartTimeMinute();
	virtual int getStartDateDay();
	virtual int getStartDateMonth();
	virtual int getEndTimeHour();
	virtual int getEndTimeMinute();
	virtual int getEndDateDay();
	virtual int getEndDateMonth();
};

#endif