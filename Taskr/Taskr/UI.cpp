#include "UI.h"
#include <vector>;

UI::UI() {
}


UI::~UI() {
}

const std::string MESSAGE_WELCOME = "Welcome to Taskr! Taskr is ready to use.";
const std::string MESSAGE_ADDED = "New task added to Taskr";
const std::string MESSAGE_DELETED = "Task deleted from Taskr";
const std::string MESSAGE_EDITED = "Task is edited to new task";
const std::string MESSAGE_TASK_IS_EXISTED = "Task is already existed";
const std::string MESSAGE_ERROR_TASK_NOT_EXIST = "Task does not exist";
const std::string MESSAGE_EMPTY = "Taskr is empty.";

void UI::readUserInput(){
	std::cout << MESSAGE_WELCOME << std::endl;
	int confirmationIndex = 0;
	while (confirmationIndex != USER_INPUT_EXIT) {
		std::string userInput;
		std::getline(std::cin, userInput);
		confirmationIndex = logic.executeCommand(userInput);
		printConfirmationMessage(confirmationIndex);
	}
}

void UI::printConfirmationMessage(std::string message){
	std::cout << message << std::endl;
}

void UI::printListOfTasks(){
	std::vector<Task> task;
	if (!task.empty()){
		for (int i=0; i<task.size(); i++){
			std::cout << i+1 << ".";
			std::cout << task.taskTitle << std::endl;
		}
	}
	else{
		std::cout << MESSAGE_EMPTY << std::endl;
	}
}