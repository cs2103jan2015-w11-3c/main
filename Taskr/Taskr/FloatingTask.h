#pragma once

#include "Task.h"

class FloatingTask : public Task {
private:

public:
	FloatingTask();
	~FloatingTask();
	
	std::string toString();
};

