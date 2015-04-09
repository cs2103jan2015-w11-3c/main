#include "Storage.h"
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
			int taskType = taskJson["task type"].as<int>();

			if (taskType == 1) {
				FloatingTask* floatingTask = new FloatingTask;
				floatingTask->setTaskType(taskJson["task type"].as<int>());
				floatingTask->setDescription(taskJson["task description"].as<string>());
				if (taskJson["isDone"].as<bool>()) {
					floatingTask->setAsDone();
				}

				tasks.push_back(floatingTask);

			} else if (taskType == 2) {
				TimedTask* timedTask = new TimedTask;
				timedTask->setTaskType(taskJson["task type"].as<int>());
				timedTask->setDescription(taskJson["task description"].as<string>());
				if (taskJson["isDone"].as<bool>()) {
					timedTask->setAsDone();
				}
				timedTask->setStartDateMonth(taskJson["start date month"].as<int>());
				timedTask->setStartDateDay(taskJson["start date day"].as<int>());
				timedTask->setStartTimeHour(taskJson["start time hour"].as<int>());
				timedTask->setStartTimeMinute(taskJson["start date minute"].as<int>());
				timedTask->setEndDateMonth(taskJson["end date month"].as<int>());
				timedTask->setEndDateMonth(taskJson["end date day"].as<int>());
				timedTask->setEndDateMonth(taskJson["end time hour"].as<int>());
				timedTask->setEndDateMonth(taskJson["end time minute"].as<int>());

				tasks.push_back(timedTask);

			} else if (taskType == 3) {
				DeadlineTask* deadlineTask = new DeadlineTask;
				deadlineTask->setTaskType(taskJson["task type"].as<int>());
				deadlineTask->setDescription(taskJson["task description"].as<string>());
				if (taskJson["isDone"].as<bool>()) {
					deadlineTask->setAsDone();
				}
				deadlineTask->setDueDateMonth(taskJson["due date month"].as<int>());
				deadlineTask->setDueDateDay(taskJson["due date day"].as<int>());
				deadlineTask->setDueTimeHour(taskJson["due time hour"].as<int>());
				deadlineTask->setDueTimeMinute(taskJson["due time minute"].as<int>());

				tasks.push_back(deadlineTask);
			}



		}
	}
	catch (exception ex) {

	}
	return tasks;
}


void Storage::saveFile(vector<Task*> listOfTasks) {
	json output(json::an_array);
	for (int i = 0; i < listOfTasks.size(); i++) {
		json taskJson;
		if (listOfTasks[i]->getTaskType() == 1) {   //floating tasks
			taskJson["task type"] = listOfTasks[i]->getTaskType();
			taskJson["task description"] = listOfTasks[i]->getDescription();
			taskJson["isDone"] = listOfTasks[i]->isDone();
		}

		if (listOfTasks[i]->getTaskType() == 2) {   //timed tasks
			taskJson["task type"] = listOfTasks[i]->getTaskType();
			taskJson["task description"] = listOfTasks[i]->getDescription();
			taskJson["isDone"] = listOfTasks[i]->isDone();
			taskJson["start date month"] = listOfTasks[i]->getStartDateMonth();
			taskJson["start date day"] = listOfTasks[i]->getStartDateDay();
			taskJson["start time hour"] = listOfTasks[i]->getStartTimeHour();
			taskJson["start time minute"] = listOfTasks[i]->getStartTimeMinute();
			taskJson["end date month"] = listOfTasks[i]->getEndDateMonth();
			taskJson["end date day"] = listOfTasks[i]->getEndDateDay();
			taskJson["end time hour"] = listOfTasks[i]->getEndTimeHour();
			taskJson["end time minute"] = listOfTasks[i]->getEndTimeMinute();
		}

		if (listOfTasks[i]->getTaskType() == 3) {   //deadline tasks
			taskJson["task type"] = listOfTasks[i]->getTaskType();
			taskJson["task description"] = listOfTasks[i]->getDescription();
			taskJson["isDone"] = listOfTasks[i]->isDone();
			taskJson["due date month"] = listOfTasks[i]->getDueDateMonth();
			taskJson["due date day"] = listOfTasks[i]->getDueDateDay();
			taskJson["due time hour"] = listOfTasks[i]->getDueTimeHour();
			taskJson["due time minute"] = listOfTasks[i]->getDueTimeMinute();
		}
		output.add(taskJson);
	}
	ofstream outFile(getFullFileName(), ofstream::out);
	outFile << pretty_print(output) << endl;
	outFile.close();
}