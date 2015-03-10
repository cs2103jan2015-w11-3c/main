#include "Storage.h"
#include <fstream>

using namespace std;

Storage::Storage() {
}

Storage::~Storage() {
}

//void Storage::readFile() {
//	ifstream myFile(_filename, ifstream::in);
//	_listOfTasks.clear();
//
//	while (!myFile.eof()) {
//		Task task;
//		string description;
//		int index;
//		bool isDone;
//		getline(myFile, description);
//		myFile >> index >> isDone;
//
//		task.setDescription(description);
//		if (isDone) {
//			task.setAsDone();
//		}
//		_listOfTasks.push_back(task);
//	}
//	return;
//}

void Storage::saveFile() {
	ofstream outFile(_filename, ofstream::out);
	for (int i = 0; i < _listOfTasks.size(); i++) {
		if (!_listOfTasks[i].isDone()) {
			outFile << i + 1 << ". " << _listOfTasks[i].getDescription() << endl;
		}
	}
	outFile.close();
}

int Storage::addTask(Task task) {
	if (isRepeated(task)) {
		return ERROR_REPEATED_TASK;
	}
	else {
		_listOfTasks.push_back(task);
		saveFile();
		return SUCCESS;
	}
}

int Storage::deleteTask(int index) {
	if (isValidIndex(index)) {
		_listOfTasks.erase(_listOfTasks.begin() + index - 1);
		saveFile();
		return SUCCESS;
	}
	else {
		return ERROR_INDEX_OUT_OF_RANGE;
	}
}

int Storage::displayList() {
	if (!_listOfTasks.empty()) {
		for (int i = 0; i < _listOfTasks.size(); i++) {
			if (!(_listOfTasks[i].isDone())) {
				cout << i + 1 << ". " << _listOfTasks[i].getDescription() << endl;
			}
		}
		return SUCCESS;
	} else {
		return ERROR_EMPTY_LIST;
	}
}

int Storage::editTask(int index, Task task) {
	if (!isValidIndex(index)) {
		return ERROR_INDEX_OUT_OF_RANGE;
	}

	if (task.getDescription() == "") {
		return ERROR_INVALID_DESCRIPTION;
	}

	_listOfTasks[index - 1] = task;
	saveFile();
	return SUCCESS;
}

bool Storage::isValidIndex(int index) {
	return index > 0 && index <= _listOfTasks.size();
}

bool Storage::isRepeated(Task task) {
	for (int i = 0; i < _listOfTasks.size(); i++) {
		if (task.getDescription() == _listOfTasks[i].getDescription()) {
			return true;
		}
	}
	return false;
}