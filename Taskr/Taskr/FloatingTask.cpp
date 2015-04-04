#include "FloatingTask.h"


FloatingTask::FloatingTask() {
	_taskType = 1;
}


FloatingTask::~FloatingTask() {
}

std::string FloatingTask::toString() {
	std::ostringstream oss;
	oss << getDescription();
	return oss.str();
}