//@author A0111966A
#ifndef TASK_H
#define TASK_H


#include<iostream>
#include<string>
#include<vector>
#include "Parser.h"
#include "jsoncons/json.hpp"

class Task {
protected:
	std::string _description;
	bool _isDone;
	int _taskType;


public:
	static const std::string TASK_TYPE;
	static const std::string TASK_DESCRIPTION;
	static const std::string IS_DONE;
	static const std::string START_DATE_MONTH;
	static const std::string START_DATE_DAY;
	static const std::string START_TIME_HOUR;
	static const std::string START_TIME_MINUTE;
	static const std::string END_DATE_MONTH;
	static const std::string END_DATE_DAY;
	static const std::string END_TIME_HOUR;
	static const std::string END_TIME_MINUTE;
	static const std::string DUE_DATE_MONTH;
	static const std::string DUE_DATE_DAY;
	static const std::string DUE_TIME_HOUR;
	static const std::string DUE_TIME_MINUTE;

	Task();
	explicit Task(jsoncons::json taskJson);
	~Task();
	virtual std::string toString();

	//setters for attributes common to all Task child classes
	void setDescription(std::string description);
	void setAsDone();
	void setTaskType(int);

	//getters for attributes common to all Task child classes
	std::string getDescription();
	bool isDone();
	int getTaskType();

	//getters for different types of child classes (floating/timed/deadline) for polymorphism.
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

	virtual jsoncons::json toJson();
};

#endif