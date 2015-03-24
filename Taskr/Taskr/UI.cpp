#include "UI.h"

const std::string UI::MESSAGE_WELCOME = "Welcome to Taskr! Taskr is ready to use.";
const std::string UI::MESSAGE_ADDED = "New task added to Taskr";
const std::string UI::MESSAGE_DELETED = "Task deleted from Taskr";
const std::string UI::MESSAGE_EDITED = "Task has been edited to new task";
const std::string UI::MESSAGE_TASK_EXISTS = "Task already exists";
const std::string UI::MESSAGE_ERROR_TASK_NOT_EXIST = "Task does not exist";
const std::string UI::MESSAGE_EMPTY = "Taskr is empty.";
const std::string UI::MESSAGE_USER_COMMAND_INVALID = "Command is invalid.";
const std::string UI::MESSAGE_INDEX_INVALID = "Index entered is invalid.";
const std::string UI::MESSAGE_MARK_DONE = "Great you've done the task!";

UI::UI() {
}


UI::~UI() {
}


void UI::readUserInput(){
	std::cout << MESSAGE_WELCOME << std::endl;
	_logic.initializeListOfTasks();
	int confirmationIndex = 0;
	while (confirmationIndex != USER_INPUT_EXIT) {
		std::cout << "command: ";
		std::string userInput;
		std::getline(std::cin, userInput);
		confirmationIndex = _logic.executeCommand(userInput);
		printConfirmationMessage(confirmationIndex);
	}
}


void UI::printConfirmationMessage(int confirmationIndex){
	switch (confirmationIndex) {
	case SUCCESS:
		if (_logic.getCommand() == "add") {
			std::cout << MESSAGE_ADDED << std::endl;
		}
		else if (_logic.getCommand() == "edit") {
			std::cout << MESSAGE_EDITED << std::endl;
		}
		else if (_logic.getCommand() == "delete") {
			std::cout << MESSAGE_DELETED << std::endl;
		}
		else if (_logic.getCommand() == "done") {
			std::cout << MESSAGE_MARK_DONE << std::endl;
		}
		break;

	case USER_COMMAND_INVALID:
		std::cout << MESSAGE_USER_COMMAND_INVALID << std::endl;
		break;
	
	case ERROR_REPEATED_TASK:
		std::cout << MESSAGE_TASK_EXISTS << std::endl;
		break;

	case ERROR_INDEX_OUT_OF_RANGE:
		std::cout << MESSAGE_INDEX_INVALID << std::endl;
		break;

	case ERROR_EMPTY_LIST:
		std::cout << MESSAGE_EMPTY << std::endl;
		break;

	case ERROR_INVALID_DESCRIPTION:
		std::cout << MESSAGE_USER_COMMAND_INVALID << std::endl;
		break;


	default:
		break;
	}
	
}

//void UI::printListOfTasks(){
//	std::vector<Task> task;
//	if (!task.empty()){
//		for (int i=0; i<task.size(); i++){
//			std::cout << i+1 << ".";
//			std::cout << task.taskTitle << std::endl;
//		}
//	}
//	else{
//		std::cout << MESSAGE_EMPTY << std::endl;
//	}
//}