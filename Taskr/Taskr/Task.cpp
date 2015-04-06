#include "Task.h"


Task::Task() {
	_description = "";
	_isDone = false;
}


Task::~Task() {
}


void Task::setDescription(std::string description) {
	_description = description;
}

void Task::setAsDone() {
	_isDone = true;
}

std::string Task::getDescription() {
	return _description;
}

bool Task::isDone() {
	return _isDone;
}

std::string Task::toString() {
	std::ostringstream oss;
	oss << getDescription();
	return oss.str();
	//to implement after polymorphism
	//return "";
}

//std::string Task::getDateString() {
//	return "";
//}
//
//std::string Task::getTimeString() {
//	return "";
//}

int Task::getTaskType() {
	return _taskType;
}

int Task::checkTodayDay() {
	return -1;
}

int Task::checkTodayMonth() {
	return -1;
}

