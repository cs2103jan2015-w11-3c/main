#include "UI.h"
#include <sstream>

const std::string UI::MESSAGE_WELCOME = "Welcome to Taskr! Taskr is ready to use.";

UI::UI() {
}


UI::~UI() {
}


void UI::processUserInput(){
	std::cout << MESSAGE_WELCOME << std::endl;
	_logic.initializeListOfTasks();
	std::string feedback;
	while (feedback != "exit") {
		std::cout << "command: ";
		std::string userInput = getUserInput();
		feedback = _logic.executeCommand(userInput);
		printConfirmationMessage(feedback);
	}
}

std::string UI::getUserInput(){
	std::string userInput;
	std::getline(std::cin, userInput);
	return userInput;
}

//will be replaced by print(std::string feedback)
void UI::printConfirmationMessage(std::string feedback) {
	std::cout << feedback << std::endl;
}

void UI::print(std::string feedback){
	printSegment(doSegment(feedback));
}

//print today's tasks
void UI::printToday(){

}

//store string feedback into vector<string> tokens line by line
std::vector<std::string> UI::doSegment(std::string feedback)
{
    std::vector<std::string> tokens;
    std::istringstream iss(feedback);
    std::string line;
    
    if (!feedback.empty())
    {
        while(std::getline(iss, line, '\n')){
            tokens.push_back(line);
        }
    }
    return tokens;
}

int UI::findFirstEmptyIndex(std::vector<std::string> tokens){
    for (int i=0; i<tokens.size(); i++){
        if (tokens[i] == "")
            return i;
    }
    return -1;
}

std::vector<std::string> UI::removePrinted(std::vector<std::string> tokens){
    int index = findFirstEmptyIndex(tokens);
    tokens.erase(tokens.begin(), tokens.begin()+index+1);
    return tokens;
}


//C:confirmation message
//F:floating tasks
//D:deadline tasks
//T:timed tasks
void UI::printSegment(std::vector<std::string> tokens){
    while (!tokens.empty()){
        if (tokens[0] == "C"){
            std::cout << tokens[1] << std::endl;
        }
        else if (tokens[0] == "F"){
            std::cout << tokens[1] << "." << "[unscheduled]    " << tokens[2] << std::endl;
        }
        else if (tokens[0] == "D"){
            std::cout << tokens[1] << "." << "[" << tokens[3] << "]           " << tokens[2] << std::endl;
        }
        else if (tokens[0] == "T"){
            std::cout << tokens[1] << "." << "[" << tokens[3] << " " << tokens[4] << "-" << tokens[5] << "] " << tokens[2] << std::endl;
        }
        tokens = removePrinted(tokens);
    }
}

