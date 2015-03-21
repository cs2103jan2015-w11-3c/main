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
	//std::string category;
	//Date dueDate;
	//Time time;

public:
	Task();
	~Task();
	void setDescription(std::string description);
	void setAsDone();
	
	//WEEK 10 ADDITIONS
	std::string toString();

	//_____
	std::string getDescription();
	bool isDone();
};

#endif