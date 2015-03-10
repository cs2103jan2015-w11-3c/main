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

void Task::setIndex(int index) {
	_index = index;
}

void Task::setAsDone() {
	_isDone = true;
}