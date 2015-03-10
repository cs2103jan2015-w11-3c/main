#include "UI.h"

UI::UI() {
}


UI::~UI() {
}


void UI::readUserInput(){
	std::cout << MESSAGE_WELCOME << std::endl;
	int confirmationIndex = 0;
	while (confirmationIndex != USER_INPUT_EXIT) {
		std::cout << "command: ";
		std::string userInput;
		std::getline(std::cin, userInput);
		confirmationIndex = logic.executeCommand(userInput);
		printConfirmationMessage(confirmationIndex);
	}
}


void UI::printConfirmationMessage(int confirmationIndex){
	switch (confirmationIndex) {
	case SUCCESS:
		if (logic.getCommand() == "add") {
			std::cout << MESSAGE_ADDED << std::endl;
		}
		else if (logic.getCommand() == "edit") {
			std::cout << MESSAGE_EDITED << std::endl;
		}
		else if (logic.getCommand() == "delete") {
			std::cout << MESSAGE_DELETED << std::endl;
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