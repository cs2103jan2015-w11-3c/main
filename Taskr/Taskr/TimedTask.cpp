#include "TimedTask.h"

using namespace jsoncons;
using namespace std;

TimedTask::TimedTask() {
	_taskType = 2;
	_start.setMonth(0);
	_start.setDay(0);
	_start.setHour(0);
	_start.setMinute(0);
	_end.setMonth(0);
	_end.setDay(0);
	_end.setHour(0);
	_end.setMinute(0);
}

TimedTask::TimedTask(json taskJson):Task(taskJson) {
	setStartDateMonth(taskJson[START_DATE_MONTH].as<int>());
	setStartDateDay(taskJson[START_DATE_DAY].as<int>());
	setStartTimeHour(taskJson[START_TIME_HOUR].as<int>());
	setStartTimeMinute(taskJson[START_TIME_MINUTE].as<int>());
	setEndDateMonth(taskJson[END_DATE_MONTH].as<int>());
	setEndDateMonth(taskJson[END_DATE_DAY].as<int>());
	setEndDateMonth(taskJson[END_TIME_HOUR].as<int>());
	setEndDateMonth(taskJson[END_TIME_MINUTE].as<int>());	
}


TimedTask::~TimedTask() {
}

void TimedTask::setStart(DateTime start) {
	_start = start;
}

void TimedTask::setEnd(DateTime end) {
	_end = end;
}

int TimedTask::getStartTimeHour() {
	return _start.getHour();
}

int TimedTask::getStartTimeMinute() {
	return _start.getMinute();
}

int TimedTask::getStartDateDay() {
	return _start.getDay();
}

int TimedTask::getStartDateMonth() {
	return _start.getMonth();
}

void TimedTask::setStartTimeHour(int startTimeHour) {
	_start.setHour(startTimeHour);
}

void TimedTask::setStartTimeMinute(int startTimeMinute) {
	_start.setMinute(startTimeMinute);
}

void TimedTask::setStartDateDay(int startDateDay) {
	_start.setDay(startDateDay);
}

void TimedTask::setStartDateMonth(int startDateMonth) {
	_start.setMonth(startDateMonth);
}

int TimedTask::getEndTimeHour() {
	return _end.getHour();
}

int TimedTask::getEndTimeMinute() {
	return _end.getMinute();
}

int TimedTask::getEndDateDay() {
	return _end.getDay();
}

int TimedTask::getEndDateMonth() {
	return _end.getMonth();
}

void TimedTask::setEndTimeHour(int endTimeHour) {
	_end.setHour(endTimeHour);
}

void TimedTask::setEndTimeMinute(int endTimeMinute) {
	_end.setMinute(endTimeMinute);
}

void TimedTask::setEndDateDay(int endDateDay) {
	_end.setDay(endDateDay);
}

void TimedTask::setEndDateMonth(int endDateMonth) {
	_end.setMonth(endDateMonth);
}

//std::string TimedTask::getDateString() {
//	std::ostringstream oss;
//	if (isLessThanTen(_start.getDay())) {
//		oss << "0" << _start.getDay();
//	}
//	else {
//		oss << _start.getDay();
//	}
//
//	oss << "/";
//
//	if (isLessThanTen(_start.getMonth())) {
//		oss << "0" << _start.getMonth();
//	}
//	else {
//		oss << _start.getMonth();
//	}
//	return oss.str();
//}
//
//std::string TimedTask::getTimeString() {
//	std::ostringstream oss;
//	if (isLessThanTen(_start.getHour())) {
//		oss << "0" << _start.getHour();
//	}
//	else {
//		oss << _start.getHour();
//	}
//
//	if (isLessThanTen(_start.getMinute())) {
//		oss << "0" << _start.getMinute();
//	}
//	else {
//		oss << _start.getMinute();
//	}
//	return oss.str();
//}

std::string TimedTask::startToString() {
	//std::ostringstream oss;
	//oss << getDateString() << "\n" << getTimeString();
	std::ostringstream oss;
	if (isLessThanTen(_start.getDay())) {
		oss << "0" << _start.getDay();
	}
	else {
		oss << _start.getDay();
	}

	oss << "/";

	if (isLessThanTen(_start.getMonth())) {
		oss << "0" << _start.getMonth();
	}
	else {
		oss << _start.getMonth();
	}

	oss << std::endl;

	if (isLessThanTen(_start.getHour())) {
		oss << "0" << _start.getHour();
	}
	else {
		oss << _start.getHour();
	}

	if (isLessThanTen(_start.getMinute())) {
		oss << "0" << _start.getMinute();
	}
	else {
		oss << _start.getMinute();
	}

	return oss.str();
}

std::string TimedTask::endToString() {
	std::ostringstream oss;
	//oss << _end.date[0] << "/" << _end.date[1] << std::endl;
	//oss << _end.time[0] << _end.time[1] << std::endl;

	if (isLessThanTen(_end.getDay())) {
		oss << "0" << _end.getDay();
	}
	else {
		oss << _end.getDay();
	}

	oss << "/";

	if (isLessThanTen(_end.getMonth())) {
		oss << "0" << _end.getMonth();
	}
	else {
		oss << _end.getMonth();
	}

	oss << std::endl;

	if (isLessThanTen(_end.getHour())) {
		oss << "0" << _end.getHour();
	}
	else {
		oss << _end.getHour();
	}

	if (isLessThanTen(_end.getMinute())) {
		oss << "0" << _end.getMinute();
	}
	else {
		oss << _end.getMinute();
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

int TimedTask::checkDay() {
	return getStartDateDay();
}

int TimedTask::checkMonth() {
	return getStartDateMonth();
}

int TimedTask::checkHour() {
	return getStartTimeHour();
}

int TimedTask::checkMinute() {
	return getStartTimeMinute();
}

json TimedTask::toJson() {
	json taskJson = Task::toJson();
	taskJson[START_DATE_MONTH] = getStartDateMonth();
	taskJson[START_DATE_DAY] = getStartDateDay();
	taskJson[START_TIME_HOUR] = getStartTimeHour();
	taskJson[START_TIME_MINUTE] = getStartTimeMinute();
	taskJson[END_DATE_MONTH] = getEndDateMonth();
	taskJson[END_DATE_DAY] = getEndDateDay();
	taskJson[END_TIME_HOUR] = getEndTimeHour();
	taskJson[END_TIME_MINUTE] = getEndTimeMinute();


	return taskJson;
}