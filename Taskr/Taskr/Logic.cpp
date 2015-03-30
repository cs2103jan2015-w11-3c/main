#include "Logic.h"


const std::string Logic::MESSAGE_ADDED = " has been added to Taskr!\n";
const std::string Logic::MESSAGE_DELETED = " has been deleted from Taskr.\n";
const std::string Logic::MESSAGE_MARK_DONE = " has been marked done!\n";
const std::string Logic::MESSAGE_ERROR_TASK_NOT_EXIST = " does not exist.\n";
const std::string Logic::MESSAGE_EDITED = " has been edited to ";
const std::string Logic::ERROR_REPEATED_TASK = " is a repeated floating task.\n";
const std::string Logic::ERROR_INDEX_OUT_OF_RANGE = " is an invalid index.\n";
const std::string Logic::ERROR_EMPTY_LIST = "Taskr is currently empty.\n";
const std::string Logic::ERROR_INVALID_DESCRIPTION = " is an invalid task and has not been added.\n";
const std::string Logic::ERROR_USER_COMMAND_INVALID = " is not a valid command. Please enter a valid command.\n";
const std::string Logic::ERROR_NOTHING_TO_UNDO = "There is nothing to undo.\n";


Logic::Logic() {
	_doneTasksCount = 0;
}


Logic::~Logic() {
}


std::string Logic::executeCommand(std::string userInput) {
	std::string command;
	std::string description;
	std::ostringstream oss;

	_parse = Parser(userInput);
	command = _parse.getCommand();

	if (command != "exit") {

		if (command == "add") {
			Task tempTask;
			tempTask.setDescription(_parse.getDescription());
			addTask(tempTask, oss);
		}
		else if (command == "delete") {
			int indexToDelete;
			indexToDelete = _parse.getIndex();
			deleteTask(indexToDelete, oss);
		}
		else if (command == "display") {
			displayList(oss);
		}
		else if (command == "edit") {
			Task tempTask;
			int indexToEdit;
			indexToEdit = _parse.getIndex();
			tempTask.setDescription(_parse.getDescription());
			editTask(indexToEdit, tempTask, oss);
		}
		else if (command == "done") {
			int indexToSet;
			indexToSet = _parse.getIndex();
			setDone(indexToSet, oss);
		}
		else if (command == "undo") {
			undoLastAction(oss);
		}
		else if (command == "search") {
			searchList(_parse.getDescription(), oss);
		}
		else {
			oss << "\"" << command << "\"" << ERROR_USER_COMMAND_INVALID;
		}
		_confirmationMessage = oss.str();
		return _confirmationMessage;

	}
	else {
		return command;
	}
}

std::string Logic::getCommand() {
	return _parse.getCommand();
}

void Logic::initializeListOfTasks() {
	_listOfTasks = _store.getAllTasks();
	for (int i = 0; i < _listOfTasks.size(); i++) {
		if (_listOfTasks[i].isDone()) {
			_doneTasksCount++;
		}
	}
}

void Logic::addTask(Task tempTask, std::ostringstream& oss) {
	if (isRepeated(tempTask)) {
		oss << ERROR_REPEATED_TASK;
	}
	else {
		_history.saveState(_listOfTasks);
		_listOfTasks.push_back(tempTask);
		_store.addTask(tempTask);
		oss << "\"" << tempTask.getDescription() << "\"" << MESSAGE_ADDED;
	}
}

void Logic::editTask(int index, Task task, std::ostringstream& oss) {
	if (!isValidIndex(index)) {
		oss << ERROR_INDEX_OUT_OF_RANGE;
	}

	if (task.getDescription() == "") {
		oss << ERROR_INVALID_DESCRIPTION;
	}
	std::string oldTaskDescription;
	std::string newTaskDescription;
	oldTaskDescription = _listOfTasks[index + _doneTasksCount - 1].getDescription();
	newTaskDescription = task.getDescription();
	_history.saveState(_listOfTasks);
	_listOfTasks[index + _doneTasksCount - 1] = task;
	_store.saveFile(_listOfTasks);
	oss << "\"" << oldTaskDescription << "\"" << MESSAGE_EDITED << "\"" << newTaskDescription << "\"." << std::endl;
}


void Logic::displayList(std::ostringstream& oss) {
	if (!_listOfTasks.empty()) {
		listToString(_listOfTasks, oss);
	} else {
		oss << ERROR_EMPTY_LIST;
	}
}


void Logic::deleteTask(int index, std::ostringstream& oss) {
	if (isValidIndex(index)) {
		std::string taskDescription;
		taskDescription = _listOfTasks[_doneTasksCount + index - 1].getDescription();
		_history.saveState(_listOfTasks);
		_listOfTasks.erase(_listOfTasks.begin() + _doneTasksCount + index - 1);
		_store.saveFile(_listOfTasks);
		oss << "\"" << taskDescription << "\"" << MESSAGE_DELETED;
	}
	else {
		oss << ERROR_INDEX_OUT_OF_RANGE;
	}
}

void Logic::setDone(int index, std::ostringstream& oss) {
	if (isValidIndex(index)) {
		std::string taskDescription;
		taskDescription = _listOfTasks[index + _doneTasksCount - 1].getDescription();
		_history.saveState(_listOfTasks);
		_listOfTasks[index + _doneTasksCount - 1].setAsDone();
		_doneTasksCount++;
		sortDoneTasks();
		_store.saveFile(_listOfTasks);
		oss << "\"" << taskDescription << "\"" << MESSAGE_MARK_DONE;
	}
	else {
		oss << ERROR_INDEX_OUT_OF_RANGE;
	}
}

void Logic::undoLastAction(std::ostringstream& oss) {
	if (_history.isEmpty()) {
		oss << ERROR_NOTHING_TO_UNDO;
	} else {
		_listOfTasks = _history.popLastState();
		_store.saveFile(_listOfTasks);
	}
}

void Logic::searchList(std::string searchString, std::ostringstream& oss) {
	std::vector<Task> tempList;
	if (_listOfTasks.empty()) {
		oss << ERROR_EMPTY_LIST;
	} else {
		for (std::vector<Task>::iterator iter = _listOfTasks.begin(); iter != _listOfTasks.end(); iter++) {
			std::size_t found;
			found = iter->getDescription().find(searchString);
			if (found != std::string::npos) {
				tempList.push_back(*iter);
			}
		}
		listToString(tempList, oss);
	}
}


bool Logic::isValidIndex(int index) {
	return index > 0 && index <= (_listOfTasks.size() - _doneTasksCount);
}

bool Logic::isRepeated(Task task) {
	for (int i = 0; i < _listOfTasks.size(); i++) {
		if (task.getDescription() == _listOfTasks[i].getDescription()) {
			return true;
		}
	}
	return false;
}

void Logic::sortDoneTasks() {
	std::vector<Task> sortedDoneTaskList;
	for (int i = 0; i < _listOfTasks.size(); i++) {
		if (_listOfTasks[i].isDone()) {
			sortedDoneTaskList.push_back(_listOfTasks[i]);
		}
	}
	for (int i = 0; i < _listOfTasks.size(); i++) {
		if (!(_listOfTasks[i].isDone())) {
			sortedDoneTaskList.push_back(_listOfTasks[i]);
		}
	}
	_listOfTasks = sortedDoneTaskList;
}


void Logic::listToString(std::vector<Task> listOfTasks, std::ostringstream& oss) {
	int displayIndex = 1;
	for (int i = 0; i < listOfTasks.size(); i++) {
		if (!(listOfTasks[i].isDone())) {
			oss << displayIndex++ << ". " << listOfTasks[i].getDescription() << std::endl;
		}
	}
}