#pragma once

#include "Task.h"

class FloatingTask : public Task {
private:
	int _taskType;

public:
	FloatingTask();
	~FloatingTask();
	std::string toString();
};

