#ifndef TASK_H
#define TASK_H


#include<iostream>
#include<string>
#include<vector>

class Task {
private:
	std::string taskTitle;
	std::string category;
	bool isHighlighted;
	int dueDate;
	int duration;

public:
	Task();
	~Task();
};

#endif