#include "Logic.h"


Logic::Logic() {
}


Logic::~Logic() {
}


std::string Logic::displayAll() {
	std::ostringstream oss;
	oss << std::endl;
	if (_listOfTasks.empty()) {
		oss << "list is empty." << std::endl;
		return oss.str();
	}
	else {
		for (unsigned int i = 0; i < _listOfTasks.size(); i++) {
			oss << (i + 1) << ". " << _listOfTasks[i].toString() << std::endl;
		}
		return oss.str();
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
			_task.Task::setDescription(description);
			_confirmationMessageIndex = _store.addTask(_task);
		}
		else if (command == "delete") {
			int indexToDelete;
			_parse.setIndex();
			indexToDelete = _parse.getIndex();
			_confirmationMessageIndex = _store.deleteTask(indexToDelete);
		}
		else if (command == "display") {
			std::cout << displayAll();
			//_confirmationMessageIndex = _store.displayList();
		}
		else if (command == "edit") {
			_task.Task::setDescription(description);
			int indexToEdit;
			_parse.setIndex();
			indexToEdit = _parse.getIndex();
			_confirmationMessageIndex = _store.editTask(indexToEdit, _task);
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
	//getAllTasks reads in an extra empty last item. popBack to get rid of it.
	_listOfTasks.pop_back();
}