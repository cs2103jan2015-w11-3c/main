#include "DeadlineTask.h"


DeadlineTask::DeadlineTask() {
	_taskType = 3;
	_due.setMonth(0);
	_due.setDay(0);
	_due.setHour(0);
	_due.setMinute(0);
}


DeadlineTask::~DeadlineTask() {
}

void DeadlineTask::setDueTimeHour(int dueTimeHour) {
	_due.setHour(dueTimeHour);
}

void DeadlineTask::setDueTimeMinute(int dueTimeMinute) {
	_due.setMinute(dueTimeMinute);
}

void DeadlineTask::setDueDateDay(int dueDateDay) {
	_due.setDay(dueDateDay);
}

void DeadlineTask::setDueDateMonth(int dueDateMonth) {
	_due.setMonth(dueDateMonth);
}

int DeadlineTask::getDueTimeHour() {
	return _due.getHour();
}

int DeadlineTask::getDueTimeMinute() {
	return _due.getMinute();
}

int DeadlineTask::getDueDateDay() {
	return _due.getDay();
}

int DeadlineTask::getDueDateMonth() {
	return _due.getMonth();
}

std::string DeadlineTask::deadlineToString() {
	std::ostringstream oss;
	if (isLessThanTen(_due.getDay())) {
		oss << "0" << _due.getDay();
	}
	else {
		oss << _due.getDay();
	}

	oss << "/";

	if (isLessThanTen(_due.getMonth())) {
		oss << "0" << _due.getMonth();
	}
	else {
		oss << _due.getMonth();
	} 

	oss << ", ";

	if (isLessThanTen(_due.getHour())) {
		oss << "0" << _due.getHour();
	}
	else {
		oss << _due.getHour();
	}

	if (isLessThanTen(_due.getMinute())) {
		oss << "0" << _due.getMinute();
	}
	else {
		oss << _due.getMinute();
	}

	return oss.str();
}

std::string DeadlineTask::toString() {
	std::ostringstream oss;
	oss << "D\n";
	oss << getDescription() << std::endl;
	oss << deadlineToString() << std::endl;
	return oss.str();
}

bool DeadlineTask::isLessThanTen(int value) {
	return value < 10;
}