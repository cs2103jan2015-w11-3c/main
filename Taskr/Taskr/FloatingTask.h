//@author A0111966A
#pragma once

#include "Task.h"
#include "jsoncons/json.hpp"

class FloatingTask : public Task {
public:
	static const int TASK_TYPE_ID = 1;

	FloatingTask();
	explicit FloatingTask(jsoncons::json taskJson);
	~FloatingTask();
	
	std::string toString();
};