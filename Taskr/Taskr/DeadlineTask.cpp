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

std::string DeadlineTask::getDeadline() {
	std::ostringstream oss;
	oss << _due.date[0] << " " << _due.date[1] << ", " << _due.time[0] << _due.time[1];
	return oss.str();
}

std::string DeadlineTask::toString() {
	std::ostringstream oss;
	oss << "D\n";
	oss << getDescription() << std::endl;
	oss << getDeadline() << std::endl;
	return oss.str();
}