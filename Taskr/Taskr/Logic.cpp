#include "Logic.h"


Logic::Logic() {
}


Logic::~Logic() {
}


int Logic::executeCommand(std::string userInput) {
	std::string command;
	_parse = Parser(userInput);

	command = _parse.getCommand();


	while (command != "exit") {
		std::string userInput;
		std::ostringstream outputMessageOSS;

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
			undefinedCommandError(outputMessageOSS);
		}

		inputVector.Task::writeToFile();
		printOutputMessage(outputMessageOSS);
		parseUserCommand(command);
	}
}