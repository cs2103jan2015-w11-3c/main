#include "History.h"


History::History() {
}


History::~History() {
}


void History::_deleteOldestState() {
	std::queue< std::vector<Task> > tempQueue;

	while (!_lastThreeStates.empty()) {
		tempQueue.push(_lastThreeStates.top());
		_lastThreeStates.pop();
	}

	//remove the oldest state that is at the front of the queue
	tempQueue.pop();

	while (!tempQueue.empty()) {
		_lastThreeStates.push(tempQueue.front());
		tempQueue.pop();
	}

}


void History::saveState(std::vector<Task> listOfTasks) {
	if (_lastThreeStates.size() == 3) {
		_deleteOldestState();
		_lastThreeStates.push(listOfTasks);
	} else {
		_lastThreeStates.push(listOfTasks);
	}
}


std::vector<Task> History::popLastState() {
	std::vector<Task> lastState = _lastThreeStates.top();
	_lastThreeStates.pop();
	return lastState;
}

bool History::isEmpty() {
	return _lastThreeStates.empty();
}