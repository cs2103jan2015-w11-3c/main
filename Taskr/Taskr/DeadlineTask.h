#pragma once

#include "Task.h"

class DeadlineTask : public Task {
private:
	int _taskType;
	DateTime _due;

public:
	DeadlineTask();
	~DeadlineTask();
	std::string toString();
};

