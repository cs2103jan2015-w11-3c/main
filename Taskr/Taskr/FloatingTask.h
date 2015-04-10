#pragma once

#include "Task.h"
#include "jsoncons/json.hpp"

class FloatingTask : public Task {
public:
	FloatingTask();
	explicit FloatingTask(jsoncons::json taskJson);
	~FloatingTask();
	
	std::string toString();
};