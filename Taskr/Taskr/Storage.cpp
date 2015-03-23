#include "Storage.h"
#include <fstream>
#include <assert.h>

using namespace std;

Storage::Storage() {
	_filename = "Taskr.txt";
	readFile();
}

Storage::~Storage() {
}

//NOTE: this will only work for our V0.1 implementation. will need to update this when Task has more attributes, probably with
//a getline function and then parse the Task accordingly. I just realized this is what you wanted to do with your readFile() method, so sorry about that..
vector<Task> Storage::getAllTasks() {
	return _listOfTasks;
}

void Storage::readFile() {
  ifstream file(_filename, ifstream::in);
  _listOfTasks.clear();
  
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
    _listOfTasks.push_back(task);
  }
  return;
}

void Storage::saveFile(vector<Task> listOfTasks) {
	ofstream outFile(_filename, ofstream::out);
	for (int i = 0; i < listOfTasks.size(); i++) {
		outFile << listOfTasks[i].isDone() << endl;
		outFile << listOfTasks[i].getDescription() << endl;
	}
	outFile.close();
}

void Storage::addTask(int index, Task task) {
	_listOfTasks.push_back(task);
	saveFile(_listOfTasks);
}

