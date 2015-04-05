#pragma once

#include "Task.h"

class TimedTask : public Task {
private:
	int _taskType;
	DateTime _start;
	DateTime _end;

public:
	TimedTask();
	~TimedTask();

	int getStartTimeHour();
	int getStartTimeMinute();
	int getStartDateDay();
	int getStartDateMonth();
	
	void setStartTimeHour(int);
	void setStartTimeMinute(int);
	void setStartDateDay(int);
	void setStartDateMonth(int);

	int getEndTimeHour();
	int getEndTimeMinute();
	int getEndDateDay();
	int getEndDateMonth();
	
	void setEndTimeHour(int);
	void setEndTimeMinute(int);
	void setEndDateDay(int);
	void setEndDateMonth(int);

	std::string toString();
	std::string startToString();
	std::string endToString();
	bool isLessThanTen(int);

};

