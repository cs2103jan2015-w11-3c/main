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

int TimedTask::getStartTimeHour() {
	return _start.time[0];
}

int TimedTask::getStartTimeMinute() {
	return _start.time[1];
}

int TimedTask::getStartDateDay() {
	return _start.date[0];
}

int TimedTask::getStartDateMonth() {
	return _start.date[1];
}

void TimedTask::setStartTimeHour(int startTimeHour) {
	_start.time[0] = startTimeHour;
}

void TimedTask::setStartTimeMinute(int startTimeMinute) {
	_start.time[1] = startTimeMinute;
}

void TimedTask::setStartDateDay(int startDateDay) {
	_start.date[0] = startDateDay;
}

void TimedTask::setStartDateMonth(int startDateMonth) {
	_start.date[1] = startDateMonth;
}

int TimedTask::getEndTimeHour() {
	return _end.time[0];
}

int TimedTask::getEndTimeMinute() {
	return _end.time[1];
}

int TimedTask::getEndDateDay() {
	return _end.date[0];
}

int TimedTask::getEndDateMonth() {
	return _end.date[1];
}

void TimedTask::setEndTimeHour(int endTimeHour) {
	_end.time[0] = endTimeHour;
}

void TimedTask::setEndTimeMinute(int endTimeMinute) {
	_end.time[1] = endTimeMinute;
}

void TimedTask::setEndDateDay(int endDateDay) {
	_end.date[0] = endDateDay;
}

void TimedTask::setEndDateMonth(int endDateMonth) {
	_end.date[1] = endDateMonth;
}

std::string TimedTask::startToString() {
	std::ostringstream oss;
	//oss << _start.date[0] << "/" << _start.date[1] << std::endl;
	//oss << _start.time[0] << _start.time[1] << std::endl;

	if (isLessThanTen(_start.date[0])) {
		oss << "0" << _start.date[0];
	}
	else {
		oss << _start.date[0];
	}

	oss << "/";

	if (isLessThanTen(_start.date[1])) {
		oss << "0" << _start.date[1];
	}
	else {
		oss << _start.date[1];
	}

	oss << std::endl;

	if (isLessThanTen(_start.time[0])) {
		oss << "0" << _start.time[0];
	}
	else {
		oss << _start.time[0];
	}

	if (isLessThanTen(_start.time[1])) {
		oss << "0" << _start.time[1];
	}
	else {
		oss << _start.time[1];
	}

	return oss.str();
}

std::string TimedTask::endToString() {
	std::ostringstream oss;
	//oss << _end.date[0] << "/" << _end.date[1] << std::endl;
	//oss << _end.time[0] << _end.time[1] << std::endl;

	if (isLessThanTen(_end.date[0])) {
		oss << "0" << _end.date[0];
	}
	else {
		oss << _end.date[0];
	}

	oss << "/";

	if (isLessThanTen(_end.date[1])) {
		oss << "0" << _end.date[1];
	}
	else {
		oss << _end.date[1];
	}

	oss << std::endl;

	if (isLessThanTen(_end.time[0])) {
		oss << "0" << _end.time[0];
	}
	else {
		oss << _end.time[0];
	}

	if (isLessThanTen(_end.time[1])) {
		oss << "0" << _end.time[1];
	}
	else {
		oss << _end.time[1];
	}

	return oss.str();
}

//example format of the string that UI needs to read:
//T
//meet joe at starbucks
//04/05
//1600
//04/05
//1800
std::string TimedTask::toString() {
	std::ostringstream oss;
	oss << "T\n";
	oss << getDescription() << std::endl;
	oss << startToString();
	oss << endToString();
	return oss.str();
}

bool TimedTask::isLessThanTen(int value) {
	return value < 10;
}