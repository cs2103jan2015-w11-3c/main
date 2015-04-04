#include "Storage.h"
#include "Storage.h"
#include <fstream>
#include <assert.h>

#include "jsoncons/json.hpp"
using jsoncons::json;
using jsoncons::pretty_print;

using namespace std;

const string DEFAULT_FILE_PATH = "Taskr.txt";

Storage::Storage() {
	_filename = DEFAULT_FILE_PATH;
}

Storage::~Storage() {
}

Storage::Storage(string filename) {
	_filename = filename;
} 

vector<Task> Storage::getAllTasks() {
	vector<Task> tasks;
	try {
		json input = json::parse_file(_filename);
		for (int i = 0; i < input.size(); i++) {
			Task task;
			json &taskJson = input[i];
			task.setDescription(taskJson["task description"].as<string>());
			if (taskJson["isDone"].as<bool>()) {
				task.setAsDone();
			}
			tasks.push_back(task);
		}
	}
	catch (exception ex) {

	}
	return tasks;
}

void Storage::saveFile(vector<Task> listOfTasks) {
	json output(json::an_array);
	for (int i = 0; i < listOfTasks.size(); i++) {
		json taskJson;
		taskJson["task description"] = listOfTasks[i].getDescription();
		taskJson["isDone"] = listOfTasks[i].isDone();
		output.add(taskJson);
	}
	ofstream outFile(_filename, ofstream::out);
	outFile << pretty_print(output) << endl;
	outFile.close();
}