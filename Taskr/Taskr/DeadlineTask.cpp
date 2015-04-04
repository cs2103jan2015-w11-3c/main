#include "DeadlineTask.h"


DeadlineTask::DeadlineTask() {
	_taskType = 3;
	_due.date[0] = 0;
	_due.date[1] = 0;
	//_due.date[2] = 0;
	_due.time[0] = 0;
	_due.time[1] = 0;
}


DeadlineTask::~DeadlineTask() {
}


std::string DeadlineTask::toString() {
	std::ostringstream oss;
	oss << getDescription();
	return oss.str();
}