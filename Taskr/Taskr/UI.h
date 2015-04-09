#ifndef UI_H
#define UI_H

#include<iostream>
#include <vector>
#include <string>
#include "Logic.h"
#include "Task.h"

class UI {
private:
	Logic _logic;

public:
	UI();
	~UI();
	
	static const std::string MESSAGE_WELCOME;

	void processUserInput();
	std::string getUserInput();
	void printConfirmationMessage(std::string);
	std::vector<std::string> doSegment(std::string);
	int findFirstEmptyIndex(std::vector<std::string>);
	std::vector<std::string> removePrinted(std::vector<std::string>);
	void printSegment(std::vector<std::string>);
	void printWholeString(std::string);
	int getNumberOfTasks(std::vector<std::string>);
	std::string getDate(std::vector<std::string>);
	void printWelcome();
	void setColour(int);
	void printDate(std::string);
	void printHelp();
};

#endif