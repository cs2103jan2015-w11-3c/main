#ifndef TASK_H
#define TASK_H


#include<iostream>
#include<string>
#include<vector>
#include "Parser.h"

class Task {
private:
	std::string _description;
	bool _isDone;
	int _index;
	//std::string category;
	//Date dueDate;
	//Time time;

public:
	Task();
	~Task();
	void setDescription(std::string description);
	void setIndex(int index);
	void setAsDone();

	std::string getDescription();
	bool isValid();
};

#endif