#include "Storage.h"
#include <fstream>
#include <assert.h>

using namespace std;

Storage::Storage() {
	_filename = "Taskr.txt";
}

Storage::~Storage() {
}

//NOTE: this will only work for our V0.1 implementation. will need to update this when Task has more attributes, probably with
//a getline function and then parse the Task accordingly. I just realized this is what you wanted to do with your readFile() method, so sorry about that..
vector<Task> Storage::getAllTasks() {
	vector<Task> tempVector;
	ifstream inFile(_filename);
	while (true) {
		std::string taskContent;
		std::string thrash;
		int index;
		Task tempTask;

		inFile >> index >> thrash;
		getline(inFile, taskContent);
		tempTask.setDescription(taskContent);
		tempVector.push_back(tempTask);
		if (inFile.eof()) {
			break;
		}
	}
	inFile.close();
	return tempVector;
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

void Storage::saveFile(vector<Task> listOfTasks) {
	ofstream outFile(_filename, ofstream::out);
	for (int i = 0; i < listOfTasks.size(); i++) {
		if (!listOfTasks[i].isDone()) {
			outFile << i + 1 << ". " << listOfTasks[i].getDescription() << endl;
		}
	}
	outFile.close();
}

void Storage::addTask(int index, Task task) {
	fstream outFile;
	outFile.open(_filename, fstream::out | fstream::app);
	outFile << index << ". " << task.toString() << endl;
	outFile.close();
}
