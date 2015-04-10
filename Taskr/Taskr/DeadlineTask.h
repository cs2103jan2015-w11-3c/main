//@author A0111966A
#pragma once

#include "Task.h"

class DeadlineTask : public Task {
private:
	DateTime _due;

public:
	static const int TASK_TYPE_ID = 3;
	DeadlineTask();
	explicit DeadlineTask(jsoncons::json taskJson);
	~DeadlineTask();

	//setters
	void setDue(DateTime);
	void setDueTimeHour(int);
	void setDueTimeMinute(int);
	void setDueDateDay(int);
	void setDueDateMonth(int);
	
	//getters
	int getDueTimeHour();
	int getDueTimeMinute();
	int getDueDateDay();
	int getDueDateMonth();
	int checkDay();
	int checkMonth();
	int checkHour();
	int checkMinute();

	//helper functions for polymorphic nature
	std::string toString();
	std::string deadlineToString();
	bool isLessThanTen(int);


	virtual jsoncons::json toJson();
};

