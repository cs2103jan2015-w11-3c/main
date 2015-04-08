#include "UI.h"
#include <sstream>
#include <Windows.h>
#include <iomanip>

const std::string UI::MESSAGE_WELCOME = "Welcome to Taskr! Taskr is ready to use.";

UI::UI() {
}


UI::~UI() {
}


void UI::processUserInput(){
	//std::cout << MESSAGE_WELCOME << std::endl;
	printWelcome();
	_logic.initializeListOfTasks();
	std::string feedback;
	while (feedback != "exit") {
		std::cout << "command: ";
		std::string userInput = getUserInput();
		feedback = _logic.executeCommand(userInput);
		if (feedback!="exit"){
			printWholeString(feedback);
		}
	}
}

std::string UI::getUserInput(){
	std::string userInput;
	std::getline(std::cin, userInput);
	return userInput;
}

/*
void UI::printConfirmationMessage(std::string feedback) {
	std::cout << feedback << std::endl;
}
*/

void UI::printWholeString(std::string feedback){
	std::vector<std::string> tokens;
	//std::string buffer;
	//std::vector<std::string> temp;
    tokens = doSegment(feedback);
	if (tokens[0] == "C"){
		std::cout << tokens[1] << std::endl;
		//buffer += tokens[1];
		//temp.push_back(buffer);
	}
	else{
		int number = getNumberOfTasks(tokens);
		std::string date = getDate(tokens);
		std::cout << "[ " << date << " ]=======================================================" << std::endl;
		while (!tokens.empty()){
			for (int i=1; i<=number; i++){
				std::cout << i << ". ";
				printSegment(tokens);
				tokens = removePrinted(tokens);
				setColour(7);
			}
		}
	}
}


void UI::printWelcome(){
	std::cout << MESSAGE_WELCOME << std::endl;
	printWholeString(_logic.executeCommand("display today"));
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
	tokens.pop_back();
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

int UI::getNumberOfTasks(std::vector<std::string> tokens){
    int number=0;
    for (int i=0; i<tokens.size(); i++){
        if (tokens[i] == "")
            number++;
    }
    return number;
}

std::string UI::getDate(std::vector<std::string> tokens){
	std::string date;
	if (tokens[0] == "D"){
        date = tokens[2];
        return date;
    }
    else if (tokens[0] == "T"){
        date = tokens[4];
        return date;
    }
	else
		return date;
}

//C:confirmation message
//F:floating tasks
//D:deadline tasks
//T:timed tasks
void UI::printSegment(std::vector<std::string> tokens){
	if (tokens[0] == "F"){
		setColour(8);
        std::cout <<"[ unscheduled ] ";
		setColour(3);
		std::cout << tokens[1] << std::endl;
    }
    else if (tokens[0] == "D"){
		setColour(8);
        std::cout << "[ by " << std::left << std::setw(9) << tokens[3] << "] ";
		setColour(13);
		std::cout << tokens[1] << std::endl;
    }
    else if (tokens[0] == "T"){
		setColour(8);
		std::cout << "[" << std::right << std::setw(6) << tokens[3] << "-" << std::left << std::setw(6) << tokens[5] << "] ";
		setColour(6);
		std::cout << tokens[1] << std::endl;
    }
	//setColour(7);
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

