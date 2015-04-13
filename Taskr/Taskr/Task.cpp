//@author A0111966A
#include "Task.h"

using namespace jsoncons;
using namespace std;

const std::string Task::TASK_TYPE = "task type";
const std::string Task::TASK_DESCRIPTION = "TASK_DESCRIPTION";
const std::string Task::IS_DONE = "isDone";
const std::string Task::START_DATE_MONTH = "start date month";
const std::string Task::START_DATE_DAY = "start date day";
const std::string Task::START_TIME_HOUR = "start time hour";
const std::string Task::START_TIME_MINUTE = "start time minute";
const std::string Task::END_DATE_MONTH = "end date month";
const std::string Task::END_DATE_DAY = "end date day";
const std::string Task::END_TIME_HOUR = "end time hour";
const std::string Task::END_TIME_MINUTE = "end time minute";
const std::string Task::DUE_DATE_MONTH = "due date month";
const std::string Task::DUE_DATE_DAY = "due date day";
const std::string Task::DUE_TIME_HOUR = "due time hour";
const std::string Task::DUE_TIME_MINUTE = "due time minute";

Task::Task() {
	_description = "";
	_isDone = false;
}

//@author A0114077L
Task::Task(json taskJson)  {
	setTaskType(taskJson[TASK_TYPE].as<int>());
	setDescription(taskJson[TASK_DESCRIPTION].as<string>());
	_isDone = taskJson[IS_DONE].as<bool>();
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
	return "";
}

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

int Task::getDueTimeHour() {
	return -1;
}

int Task::getDueTimeMinute() {
	return -1;
}

int Task::getDueDateDay() {
	return -1;
}

int Task::getDueDateMonth() {
	return -1;
}

int Task::getStartTimeHour() {
	return -1;
}

int Task::getStartTimeMinute() {
	return -1;
}

int Task::getStartDateDay() {
	return -1;
}

int Task::getStartDateMonth() {
	return -1;
}

int Task::getEndTimeHour() {
	return -1;
}

int Task::getEndTimeMinute() {
	return -1;
}

int Task::getEndDateDay() {
	return -1;
}

int Task::getEndDateMonth() {
	return -1;
}

json Task::toJson() {
	json taskJson;
	taskJson[TASK_TYPE] = getTaskType();
	taskJson[TASK_DESCRIPTION] = getDescription();
	taskJson[IS_DONE] = isDone();
	return taskJson;
}