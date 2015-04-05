#include "DeadlineTask.h"


DeadlineTask::DeadlineTask() {
	_taskType = 3;
	_due.date[0] = 0;
	_due.date[1] = 0;
	_due.time[0] = 0;
	_due.time[1] = 0;
}


DeadlineTask::~DeadlineTask() {
}

void DeadlineTask::setDueTimeHour(int dueTimeHour) {
	_due.time[0] = dueTimeHour;
}

void DeadlineTask::setDueTimeMinute(int dueTimeMinute) {
	_due.time[1] = dueTimeMinute;
}

void DeadlineTask::setDueDateDay(int dueDateDay) {
	_due.date[0] = dueDateDay;
}

void DeadlineTask::setDueDateMonth(int dueDateMonth) {
	_due.date[1] = dueDateMonth;
}

int DeadlineTask::getDueTimeHour() {
	return _due.time[0];
}

int DeadlineTask::getDueTimeMinute() {
	return _due.time[1];
}

int DeadlineTask::getDueDateDay() {
	return _due.date[0];
}

int DeadlineTask::getDueDateMonth() {
	return _due.date[1];
}

std::string DeadlineTask::deadlineToString() {
	std::ostringstream oss;
	if (isLessThanTen(_due.date[0])) {
		oss << "0" << _due.date[0];
	}
	else {
		oss << _due.date[0];
	}

	oss << "/";

	if (isLessThanTen(_due.date[1])) {
		oss << "0" << _due.date[1];
	}
	else {
		oss << _due.date[1];
	} 

	oss << ", ";

	if (isLessThanTen(_due.time[0])) {
		oss << "0" << _due.time[0];
	}
	else {
		oss << _due.time[0];
	}

	if (isLessThanTen(_due.time[1])) {
		oss << "0" << _due.time[1];
	}
	else {
		oss << _due.time[1];
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