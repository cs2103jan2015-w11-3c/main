#pragma once

#include "Task.h"

class DeadlineTask : public Task {
private:
	DateTime _due;

public:
	static const int TASK_TYPE_ID = 3;
	DeadlineTask();
	explicit DeadlineTask(jsoncons::json taskJson);
	~DeadlineTask();
	//to replace individual setters
	void setDue(DateTime);
	
	void setDueTimeHour(int);
	void setDueTimeMinute(int);
	void setDueDateDay(int);
	void setDueDateMonth(int);

	int getDueTimeHour();
	int getDueTimeMinute();
	int getDueDateDay();
	int getDueDateMonth();

	std::string toString();
	std::string deadlineToString();
	bool isLessThanTen(int);
	int checkDay();
	int checkMonth();
	int checkHour();
	int checkMinute();

	virtual jsoncons::json toJson();

	//std::string getDateString();
	//std::string getTimeString();
};

