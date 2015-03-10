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
	description = _parse.getDescription();

	while (command != "exit") {
		
		if (command == "add") {
			removeLeadingSpaces(userInput);
			inputVector.Task::addTask(userInput, outputMessageOSS);
		}
		else if (command == "delete") {
			inputVector.Task::deleteTask(outputMessageOSS);
		}
		else if (command == "view") {
			inputVector.Task::displayList(outputMessageOSS);
		}
		else if (command == "edit") {
			inputVector.Task::clearList(outputMessageOSS);
		}
		else {
			return ERRORCODE_0;
		}

		inputVector.Task::writeToFile();
		printOutputMessage(outputMessageOSS);
		parseUserCommand(command);
	}
}