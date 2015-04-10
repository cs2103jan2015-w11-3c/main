#pragma once

#include "Task.h"

class TimedTask : public Task {
private:
	DateTime _start;
	DateTime _end;

public:
	TimedTask();
	~TimedTask();

	virtual jsoncons::json toJson();
	explicit TimedTask(jsoncons::json taskJson);

	//to replace individual setters
	void setStart(DateTime);
	void setEnd(DateTime);

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
	int checkDay();
	int checkMonth();
	int checkHour();
	int checkMinute();


	//std::string getDateString();
	//std::string getTimeString();

};

