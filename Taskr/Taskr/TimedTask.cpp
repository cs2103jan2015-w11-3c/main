#include "TimedTask.h"


TimedTask::TimedTask() {
	_taskType = 2;
	_start.date[0] = 0;
	_start.date[1] = 0;
	_start.time[0] = 0;
	_start.time[1] = 0;
	_end.date[0] = 0;
	_end.date[1] = 0;
	_end.time[0] = 0;
	_end.time[1] = 0;
}


TimedTask::~TimedTask() {
}

std::string TimedTask::getStart() {
	std::ostringstream oss;
	oss << _start.date[0] << " " << _start.date[1] << std::endl;
	oss << _start.time[0] << _start.time[1] << std::endl;
	return oss.str();
}

std::string TimedTask::getEnd() {
	std::ostringstream oss;
	oss << _end.date[0] << " " << _end.date[1] << std::endl;
	oss << _end.time[0] << _end.time[1] << std::endl;
	return oss.str();
}

//format of the string that UI needs to read: eg. T 1. meet joe at starbucks 
std::string TimedTask::toString() {
	std::ostringstream oss;
	oss << "T\n";
	oss << getDescription() << std::endl;
	oss << getStart();
	oss << getEnd();
	return oss.str();
}