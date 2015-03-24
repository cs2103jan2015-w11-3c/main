#include "Logic.h"


Logic::Logic() {
	_doneTasksCount = 0;
}


Logic::~Logic() {
}


int Logic::executeCommand(std::string userInput) {
	std::string command;
	std::string description;

	_parse = Parser(userInput);
	command = _parse.getCommand();

	if (command != "exit") {

		if (command == "add") {
			Task tempTask;
			tempTask.setDescription(_parse.getDescription());
			_confirmationMessageIndex = addTask(tempTask);
		}
		else if (command == "delete") {
			int indexToDelete;
			indexToDelete = _parse.getIndex();
			_confirmationMessageIndex = deleteTask(indexToDelete);
		}
		else if (command == "display") {
			_confirmationMessageIndex = displayList();
		}
		else if (command == "edit") {
			Task tempTask;
			int indexToEdit;
			indexToEdit = _parse.getIndex();
			tempTask.setDescription(_parse.getDescription());
			_confirmationMessageIndex = editTask(indexToEdit, tempTask);
		}
		else if (command == "done") {
			int indexToSet;
			indexToSet = _parse.getIndex();
			_confirmationMessageIndex = setDone(indexToSet);
		}
		else {
			return USER_COMMAND_INVALID;
		}
		return _confirmationMessageIndex;

	}
	else {
		return USER_INPUT_EXIT;
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

int Logic::addTask(Task tempTask) {
	if (isRepeated(tempTask)) {
		return ERROR_REPEATED_TASK;
	}
	else {
		_listOfTasks.push_back(tempTask);
		_store.addTask(tempTask);
		return SUCCESS;
	}
}

int Logic::editTask(int index, Task task) {
	if (!isValidIndex(index)) {
		return ERROR_INDEX_OUT_OF_RANGE;
	}

	if (task.getDescription() == "") {
		return ERROR_INVALID_DESCRIPTION;
	}

	_listOfTasks[index + _doneTasksCount - 1] = task;
	_store.saveFile(_listOfTasks);
	return SUCCESS;
}


int Logic::displayList() {
	if (!_listOfTasks.empty()) {
		int displayIndex = 1;
		for (int i = 0; i < _listOfTasks.size(); i++) {
			if (!(_listOfTasks[i].isDone())) {
				std::cout << displayIndex++ << ". " << _listOfTasks[i].getDescription() << std::endl;
			}
		}
		return SUCCESS;
	}
	else {
		return ERROR_EMPTY_LIST;
	}
}


int Logic::deleteTask(int index) {
	if (isValidIndex(index)) {
		_listOfTasks.erase(_listOfTasks.begin() + _doneTasksCount + index - 1);
		_store.saveFile(_listOfTasks);
		return SUCCESS;
	}
	else {
		return ERROR_INDEX_OUT_OF_RANGE;
	}
}

int Logic::setDone(int index) {
	if (isValidIndex(index)) {
		_listOfTasks[index + _doneTasksCount - 1].setAsDone();
		_doneTasksCount++;
		sortDoneTasks();
		_store.saveFile(_listOfTasks);
		return SUCCESS;
	}
	else {
		return ERROR_INDEX_OUT_OF_RANGE;
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
