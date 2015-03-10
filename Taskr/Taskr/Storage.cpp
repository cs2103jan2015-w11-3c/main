#include "Storage.h"
#include <fstream>

using namespace std;

TaskStorage::TaskStorage() {
}

void TaskStorage::readFile() {
	ifstream myFile(_filename, ifstream::in);
	_listOfTasks.clear();

	while (!myFile.eof()) {
		Task task;
		string description;
		int index;
		bool isDone;
		getline(myFile, description);
		myFile >> index >> isDone;

		task.setDescription(description);
		task.setIndex(index);
		if (isDone) {
			task.setAsDone();
		}
		_listOfTasks.push_back(task);
	}
	return;
}

void TaskStorage::saveFile() {
	ofstream outFile(_filename, ofstream::out);
	for (int i = 0; i < _listOfTasks.size(); i++) {
		Task &task = _listOfTasks[i];
		//outFile << task.getDescription() << endl;
		//outFile << task.getIndex() << endl;
		//outFile << task.getIsDone() << endl;
		// outFile << _listOfTasks[i] << endl;
	}
	outFile.close();
	return;
}

bool TaskStorage::addTask(Task task) {
	if (!task.isValid()) {
		return false;
	}
	else {
		_listOfTasks.push_back(task);
		saveFile();
		return true;
	}
}

bool TaskStorage::deleteTask(int index) {
	int i = index;
	if (i <= _listOfTasks.size() && i > 0) {
		_listOfTasks.erase(_listOfTasks.begin() + i - 1);
		saveFile();
		return true;
	}
	else {
		return false;
	}
}
//bool taskstorage::displaytask() {
//	if (!_listoftasks.empty()) {
//		for (int i = 0; i < _listOfTasks.size(); i++) {
//			const task &task = _listoftasks[i];
//			cout << i + 1 << ". " << task.getdescription() << endl;
//			return true;
//		}
//	} else {
//		return false;
//	}
//}

bool TaskStorage::editTask(int index, Task task) {
	if (!isValidIndex(index) || task.getDescription() == "") {
		return false;
	}
	_listOfTasks[index - 1] = task;
	saveFile();
	return true;
}

bool TaskStorage::isValidIndex(int index) {
	return index > 0 && index <= _listOfTasks.size();
}