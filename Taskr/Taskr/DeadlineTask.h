#pragma once

#include "Task.h"

class DeadlineTask : public Task {
private:
	DateTime _due;

public:
	DeadlineTask();
	~DeadlineTask();
	//to replace individual setters
	void setDue(DateTime);
	
	void setDueTimeHour(int);
	void setDueTimeMinute(int);
	void setDueDateDay(int);
	void setDueDateMonth(int);

	int getDueTimeHour();
	int getDueTimeMinute();
	int getDueDateDay();
	int getDueDateMonth();

	std::string toString();
	std::string deadlineToString();
	bool isLessThanTen(int);
	int checkTodayDay();
	int checkTodayMonth();

	//std::string getDateString();
	//std::string getTimeString();
};

