//@author A0114943H
#include "UI.h"
#include <sstream>
#include <Windows.h>
#include <iomanip>
#include <cstdlib>

const std::string UI::MESSAGE_WELCOME = "Welcome to Taskr! Taskr is ready to use.\n";

UI::UI() {
}


UI::~UI() {
}


void UI::processUserInput(){

	_logic.initializeListOfTasks();
	printWelcome();
	std::string feedback;
	while (feedback != "exit") {
		std::cout << "command: ";
		std::string userInput;
		try{
			userInput = getUserInput();
		}catch(std::runtime_error & e){
			std::cerr << e.what();
		}
		feedback = _logic.executeCommand(userInput);
		assert(!feedback.empty());
		if (feedback!="exit"){
			system("cls");
			printWholeString(feedback);
		}
	}
}

std::string UI::getUserInput(){
	std::string userInput;
	std::getline(std::cin, userInput);
	if (userInput.empty()){
		throw std::runtime_error("error! user input cannot be empty!");
	}
	return userInput;
	
}

void UI::printWholeString(std::string feedback){
	std::vector<std::string> tokens;
    tokens = doSegment(feedback);
	if (tokens.empty()) {
		return;
	}

	if (tokens[0] == "C"){
		std::cout << tokens[1] << std::endl;
	}else if(tokens[0] == "HELP"){
		printHelp();
	}else{
		int number = getNumberOfTasks(tokens);
		std::string date = getDate(tokens);
		printDate(date);
		while (!tokens.empty()){
			for (int i=1; i<=number; i++){
				if ((tokens[0] == "D" && tokens[2] == date)||
					(tokens[0] == "T" && tokens[4] == date)||
					(tokens[0] == "F" && date == "unscheduled")){
					std::cout << i << ".";
					printSegment(tokens);
					tokens = removePrinted(tokens);
					setColour(7);
				}else if((tokens[0] == "D" && tokens[2] != date)||
					(tokens[0] == "T" && tokens[4] != date)||
					(tokens[0] == "F" && date != "unscheduled")){
					std::cout << std::endl;
					date = getDate(tokens);
					printDate(date);
					std::cout << i << ".";
					printSegment(tokens);
					tokens = removePrinted(tokens);
					setColour(7);
				}
			}
		}
	}
}

void UI::printDate(std::string date){
	setColour(15);
	std::cout << "[" << date << "]=========================================================" << std::endl;

	setColour(7);
}

void UI::printWelcome(){
	std::cout << MESSAGE_WELCOME << std::endl;
	std::cout << "List of today's tasks:" << std::endl;
	printWholeString(_logic.executeCommand("display today"));
	std::cout << std::endl;
	std::cout << "Enter \"help\" to see list of possible commands!\n " << std::endl;
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

//return index of the first empty line in vector<string> tokens
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
	else if (tokens[0] == "F"){
		return "unscheduled";
	}
    return date;
}

//F:floating tasks
//D:deadline tasks
//T:timed tasks
void UI::printSegment(std::vector<std::string> tokens){
	if (tokens[0] == "F"){
		setColour(6);
		std::cout << " " << tokens[1] << std::endl;
    }
    else if (tokens[0] == "D"){
		setColour(13);
        std::cout << "[ by " << std::left << std::setw(5) << tokens[3] << "] ";
		setColour(13);
		std::cout << tokens[1] << std::endl;
    }
    else if (tokens[0] == "T"){
		setColour(3);
		std::cout << "[" << std::right << std::setw(4) << tokens[3] << "-" << std::left << std::setw(4) << tokens[5] << "] ";
		setColour(3);
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

void UI::printHelp(){
	std::cout << "You can use Taskr with the following commands: " << std::endl;
	setColour(14);
	std::cout << "Add a floating task" << std::endl;
	setColour(7);
	std::cout << "Enter \"add <task description>\".\n";
	setColour(14);
	std::cout << "Add a timed task" << std::endl;
	setColour(7);
	std::cout << "Enter \"add <task description> <start date and time> <end date and time>\".\n";
	setColour(14);
	std::cout << "Add a deadline task" << std::endl;
	setColour(7);
	std::cout << "Enter \"add <task description> <due date and time>\".\n";
	setColour(14);
	std::cout << "Display" << std::endl;
	setColour(7);
	std::cout << "Enter \"display\" to display all the tasks being tracked.\n";
	std::cout << "Enter \"display <parameter>\". Parameter values include: today, done.\n";
	setColour(14);
	std::cout << "Edit a task" << std::endl;
	setColour(7);
	std::cout << "Enter \"display\" to find the task to edit, then enter \"edit <index> <edited task>\".\n";
	setColour(14);
	std::cout << "Delete task" << std::endl;
	setColour(7);
	std::cout << "Enter \"display\" to find the task to delete, then enter \"delete <index>\".\n";
	setColour(14);
	std::cout << "Mark Done" << std::endl;
	setColour(7);
	std::cout << "Enter \"display\" to find the task to mark done, then enter \"done <index>\" to mark the task as done.\n";
	setColour(14);
	std::cout << "Search for a task" << std::endl;
	setColour(7);
	std::cout << "Enter \"search <word to search>\".\n";
	setColour(14);
	std::cout << "Undo last action" << std::endl;
	setColour(7);
	std::cout << "Enter \"undo\" and confirm your action. Undo action cannot be undone, and is capped at a maximum of 3 undos.\n";
	setColour(14);
	std::cout << "Change file location" << std::endl;
	setColour(7);
	std::cout << "Enter \"file <file path>\"to change the location where your file is saved.\n";
}