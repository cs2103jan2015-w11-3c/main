#ifndef HISTORY_H
#define HISTORY_H

#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include "Task.h"

class History {
private:
	std::stack< std::vector<Task*> > _lastThreeStates;
	void _deleteOldestState();

public:
	History();
	~History();

	void saveState(std::vector<Task*>);
	std::vector<Task*> popLastState();
	bool isEmpty();

};

#endif