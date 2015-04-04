#pragma once

#include "Task.h"

class TimedTask : public Task {
private:
	int _taskType;
	DateTime _start;
	DateTime _end;

public:
	TimedTask();
	~TimedTask();
	std::string toString();
};

