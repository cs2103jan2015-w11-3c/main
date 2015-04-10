//@author A0111966A
#pragma once

#include "Task.h"

class TimedTask : public Task {
private:
	DateTime _start;
	DateTime _end;

public:
	static const int TASK_TYPE_ID = 2;
	TimedTask();
	explicit TimedTask(jsoncons::json taskJson);
	~TimedTask();

	virtual jsoncons::json toJson();

	//setters
	void setStart(DateTime);
	void setEnd(DateTime);
	void setStartTimeHour(int);
	void setStartTimeMinute(int);
	void setStartDateDay(int);
	void setStartDateMonth(int);
	void setEndTimeHour(int);
	void setEndTimeMinute(int);
	void setEndDateDay(int);
	void setEndDateMonth(int);

	//getters
	int getStartTimeHour();
	int getStartTimeMinute();
	int getStartDateDay();
	int getStartDateMonth();
	int getEndTimeHour();
	int getEndTimeMinute();
	int getEndDateDay();
	int getEndDateMonth();
	int checkDay();
	int checkMonth();
	int checkHour();
	int checkMinute();

	//helper functions for polymorphic nature
	std::string toString();
	std::string startToString();
	std::string endToString();
	bool isLessThanTen(int);


};

