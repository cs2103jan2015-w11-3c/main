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

void Task::setTaskType(int taskType) {
	_taskType = taskType;
}

int Task::checkDay() {
	return -1;
}

int Task::checkMonth() {
	return -1;
}

int Task::checkHour() {
	return -1;
}

int Task::checkMinute() {
	return -1;
}

