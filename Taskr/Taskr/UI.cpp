#include "UI.h"
#include <sstream>
#include <Windows.h>


const std::string UI::MESSAGE_WELCOME = "Welcome to Taskr! Taskr is ready to use.";

UI::UI() {
}


UI::~UI() {
}


void UI::processUserInput(){
	std::cout << MESSAGE_WELCOME << std::endl;
	//printToday();
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

//print today's tasks, will be implemented later
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
			setColour(8);
            std::cout << tokens[1] << "." << "[unscheduled]    ";
			setColour(3);
			std::cout << tokens[2] << std::endl;
        }
        else if (tokens[0] == "D"){
			setColour(8);
            std::cout << tokens[1] << "." << "[" << tokens[3] << "]           ";
			setColour(3);
			std::cout << tokens[2] << std::endl;
        }
        else if (tokens[0] == "T"){
			setColour(8);
            std::cout << tokens[1] << "." << "[" << tokens[3] << " " << tokens[4] << "-" << tokens[5] << "] ";
			setColour(3);
			std::cout << tokens[2] << std::endl;
        }
        tokens = removePrinted(tokens);
		setColour(7);
    }
}

/*
colour codes:
1: Blue
2: Green
3: Cyan
4: Red
5: Purple
6: Yellow (Dark)
7: Default white
8: Gray/Grey
9: Bright blue
10: Brigth green
11: Bright cyan
12: Bright red
13: Pink/Magenta
14: Yellow
15: Bright white
*/
void UI::setColour(int value){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),value);
}