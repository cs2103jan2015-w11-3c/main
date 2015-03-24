#include "Logic.h"


Logic::Logic() {
}


Logic::~Logic() {
}


int Logic::displayList() {
	if (!_listOfTasks.empty()) {
		for (int i = 0; i < _listOfTasks.size(); i++) {
			if (!(_listOfTasks[i].isDone())) {
				std::cout << i + 1 << ". " << _listOfTasks[i].getDescription() << std::endl;
			}
		}
		return SUCCESS;
	}
	else {
		return ERROR_EMPTY_LIST;
	}
}

int Logic::executeCommand(std::string userInput) {
	std::string command;
	std::string description;

	_parse = Parser(userInput);
	_parse.setCommand();
	command = _parse.getCommand();

	if (command != "exit") {
		_parse.setDescription();
		description = _parse.getDescription();

		if (command == "add") {
			Task tempTask;
			tempTask.setDescription(description);
			_confirmationMessageIndex = addTask(tempTask);
		}
		else if (command == "delete") {
			int indexToDelete;
			_parse.setIndex();
			indexToDelete = _parse.getIndex();
			_confirmationMessageIndex = deleteTask(indexToDelete);
		}
		else if (command == "display") {
			_confirmationMessageIndex = displayList();
		}
		else if (command == "edit") {
			Task tempTask;
			tempTask.setDescription(description);
			int indexToEdit;
			_parse.setIndex();
			indexToEdit = _parse.getIndex();
			_confirmationMessageIndex = editTask(indexToEdit, tempTask);
		}
		else if (command == "done") {
			int indexToSet;
			_parse.setIndex();
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
}

int Logic::addTask(Task tempTask) {
	if (isRepeated(tempTask)) {
		return ERROR_REPEATED_TASK;
	}
	else {
		_listOfTasks.push_back(tempTask);
		_store.addTask(_listOfTasks.size(), tempTask);
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

	_listOfTasks[index - 1] = task;
	_store.saveFile(_listOfTasks);
	return SUCCESS;
}

int Logic::deleteTask(int index) {
	if (isValidIndex(index)) {
		_listOfTasks.erase(_listOfTasks.begin() + index - 1);
		_store.saveFile(_listOfTasks);
		return SUCCESS;
	}
	else {
		return ERROR_INDEX_OUT_OF_RANGE;
	}
}

int Logic::setDone(int index) {
	if (isValidIndex(index)) {
		_listOfTasks[index - 1].setAsDone();
		_store.saveFile(_listOfTasks);
		return SUCCESS;
	}
	else {
		return ERROR_INDEX_OUT_OF_RANGE;
	}
}

bool Logic::isValidIndex(int index) {
	return index > 0 && index <= _listOfTasks.size();
}

bool Logic::isRepeated(Task task) {
	for (int i = 0; i < _listOfTasks.size(); i++) {
		if (task.getDescription() == _listOfTasks[i].getDescription()) {
			return true;
		}
	}
	return false;
}