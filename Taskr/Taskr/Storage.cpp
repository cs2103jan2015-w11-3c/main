//@author A0114077L
#include "Storage.h"
#include <fstream>
#include <assert.h>

#include "jsoncons/json.hpp"

using jsoncons::json;
using jsoncons::pretty_print;
using namespace std;

const string DEFAULT_FILE_PATH = "";
const string DEFAULT_FILE_NAME = "Taskr.txt";
const string DEFAULT_FILE_CONFIG = "FileConfigurations.txt";

Storage::Storage() {
	_filepath = DEFAULT_FILE_PATH;
	_filename = DEFAULT_FILE_NAME;
	_fileConfig = DEFAULT_FILE_CONFIG;
}

Storage::~Storage() {
}

void Storage::setFileConfig() {
	ifstream inFile(_fileConfig);
	if (!getline(inFile, _filename)) {
		inFile.close();
		updateFileConfig();
		ifstream inFile(_fileConfig);
	}
	getline(inFile, _filepath);

	inFile.close();
}


void Storage::updateFileConfig() {
	ofstream outFile(_fileConfig);
	outFile << _filename << endl;
	outFile << _filepath << endl;
	outFile.close();
}


void Storage::setFilePath(std::string filepath) {
	_filepath = filepath;
	updateFileConfig();
}


string Storage::getFullFileName() {
	if (_filepath == "") {
		return _filename;
	} else {
		return (_filepath + "//" + _filename);
	}
}


vector<Task*> Storage::getAllTasks() {
	setFileConfig();

	vector<Task*> tasks;
	try {
		json input = json::parse_file(getFullFileName());
		for (int i = 0; i < input.size(); i++) {
			json &taskJson = input[i];
			int taskType = taskJson[Task::TASK_TYPE].as<int>();
			Task *task;
			switch (taskType)
			{
			case FloatingTask::TASK_TYPE_ID:
				task = new FloatingTask(taskJson);
				break;
			case TimedTask::TASK_TYPE_ID:
				task = new TimedTask(taskJson);
				break;
			case DeadlineTask::TASK_TYPE_ID:
				task = new DeadlineTask(taskJson);
				break;
			}
			tasks.push_back(task);
		}
	}
	catch (exception ex) {

	}
	return tasks;
}


void Storage::saveFile(vector<Task*> listOfTasks) {
	json output(json::an_array);
	for (int i = 0; i < listOfTasks.size(); i++) {
		json taskJson = listOfTasks[i]->toJson();
		output.add(taskJson);
	}
	ofstream outFile(getFullFileName(), ofstream::out);
	outFile << pretty_print(output) << endl;
	outFile.close();
}