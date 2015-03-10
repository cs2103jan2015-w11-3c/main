#include "Logic.h"


Logic::Logic() {
}


Logic::~Logic() {
}


int Logic::executeCommand(std::string userInput) {
	std::string command;
	std::string description;

	_parse = Parser(userInput);

	command = _parse.getCommand();

	if (command != "exit") {
		description = _parse.getDescription();

		if (command == "add") {
			_task.Task::setDescription(description);
			_confirmationMessageIndex = _store.addTask(_task);
		}
		else if (command == "delete") {
			int indexToDelete;
			indexToDelete = _parse.getIndex();
			_confirmationMessageIndex = _store.deleteTask(indexToDelete);
		}
		else if (command == "view") {
			_confirmationMessageIndex = _store.displayTask();
		}
		else if (command == "edit") {
			_task.Task::setDescription(description);
			int indexToEdit;
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