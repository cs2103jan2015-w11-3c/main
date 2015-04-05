#pragma once

#include "Task.h"

class DeadlineTask : public Task {
private:
	int _taskType;
	DateTime _due;

public:
	DeadlineTask();
	~DeadlineTask();

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

};

