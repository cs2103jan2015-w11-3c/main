#ifndef UI_H
#define UI_H

#include<iostream>;
#include "Logic.h";

using namespace std;

class UI {
private:
	Logic logic;

public:
	UI();
	~UI();

	void readUserInput();
	void printConfirmationMessage();
	void printListOfTasks();
};



#endif