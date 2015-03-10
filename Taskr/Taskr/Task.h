#ifndef TASK_H
#define TASK_H


#include<iostream>
#include<string>
#include<vector>

class Task {
private:
	std::string description;
	bool isDone;
	int dueDate;
	int duration;

public:
	Task();
	~Task();
};

#endif