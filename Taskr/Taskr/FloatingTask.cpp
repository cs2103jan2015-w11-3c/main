#include "FloatingTask.h"


FloatingTask::FloatingTask() {
	_taskType = 1;
}


FloatingTask::~FloatingTask() {
}

std::string FloatingTask::toString() {
	std::ostringstream oss;
	oss << "F\n";
	oss << getDescription() << std::endl;
	return oss.str();
}