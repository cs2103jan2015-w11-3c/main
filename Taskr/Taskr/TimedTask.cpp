#include "TimedTask.h"


TimedTask::TimedTask() {
	_taskType = 2;
	_start.date[0] = 0;
	_start.date[1] = 0;
	//_start.date[2] = 0;
	_start.time[0] = 0;
	_start.time[1] = 0;
	_end.date[0] = 0;
	_end.date[1] = 0;
	//_end.date[2] = 0;
	_end.time[0] = 0;
	_end.time[1] = 0;
}


TimedTask::~TimedTask() {
}

//format of the string that UI needs to read: eg. T 1. meet joe at starbucks 
std::string TimedTask::toString() {
	std::ostringstream oss;
	oss << getDescription();
	return oss.str();
}