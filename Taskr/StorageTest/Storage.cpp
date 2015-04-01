#include "Storage.h"
#include "Storage.h"
#include <fstream>
#include <assert.h>

using namespace std;

Storage::Storage() {
	_filename = "Taskr.txt";
}

Storage::~Storage() {
}

vector<Task> Storage::getAllTasks() {
	ifstream file(_filename, ifstream::in);
	vector<Task> tasks;
	int index = 0;
	while (!file.eof()) {
		Task task;
		string description;
		string emptyLine;
		bool isDone;
		if (!(file >> isDone)) {
			// eof
			break;
		}
		getline(file, emptyLine);
		getline(file, description);
		task.setDescription(description);
		if (isDone) {
			task.setAsDone();
		}
		tasks.push_back(task);
	}
	return tasks;
}

void Storage::saveFile(vector<Task> listOfTasks) {
	ofstream outFile(_filename, ofstream::out);
	for (int i = 0; i < listOfTasks.size(); i++) {
		outFile << listOfTasks[i].isDone() << endl;
		outFile << listOfTasks[i].getDescription() << endl;
	}
	outFile.close();
}

void Storage::addTask(Task task) {
	fstream outFile;
	outFile.open(_filename, fstream::out | fstream::app);
	outFile << task.isDone() << endl;
	outFile << task.getDescription() << endl;
	outFile.close();
}