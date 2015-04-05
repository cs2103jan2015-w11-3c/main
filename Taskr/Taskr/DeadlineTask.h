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

	std::string toString();
	std::string getDeadline();
};

