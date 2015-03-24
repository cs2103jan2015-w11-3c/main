#include "Parser.h"

const std::string Parser::ADD = "add";
const std::string Parser::DELETE = "delete";
const std::string Parser::EDIT = "edit";
const std::string Parser::DISPLAY = "display";
const std::string Parser::DONE = "done";
const std::string Parser::EXIT = "exit";

const char Parser::WhiteSpace = ' ';
const int Parser::Start_Index = 0;

Parser::Parser() {
}

Parser::Parser(std::string input) {
	/*input = trimInput(input);
	input = removeWhiteSpaces(input);*/
	_userInput = input;
	
	std::string command = retrieveCommand();
	command = convertCase(command);
	_command = command;
	extractParameters();
}

std::string Parser::trimInput(std::string input) {
	input = trimStart(input);
	input = trimEnd(input);
	return input;
}

std::string Parser::trimStart(std::string input) {
	int startInput = Start_Index;
	while((input[startInput] < input.length()) && input[startInput] == WhiteSpace) {
		startInput++;
	}

	return input.substr(startInput);
}

std::string Parser::trimEnd(std::string input) {
	int endInput = input.length();
	while((endInput > 0) && input[endInput] == WhiteSpace) {
		endInput++;
	}

	return input.substr(Start_Index, endInput);
}
std::string Parser::removeWhiteSpaces(std::string input) {   //to remove consecutive white spaces
	int index;
	int end = input.length();

	for(index = Start_Index; index < end; index++) {
		if((input[index] == WhiteSpace) && (input[index+1] == WhiteSpace)) {
			input.erase(index, 1);
		}
	}

	return input;
}

std::string Parser::retrieveCommand() {
	std::istringstream iss;
	iss >> _userInput;

	return iss.str();
}

std::string Parser::convertCase(std::string command) {
	int index;
	int commandEnd = command.length();

	for(index = Start_Index; index < commandEnd; index++) {
		command[index] = tolower(command[index]);
	}

	return command;
}

void Parser::extractParameters() {
	if(_command == ADD) {
		int temp = _userInput.find_first_of(" ");
		_description = _userInput.substr(temp+1);
	}

	else if(_command == DELETE || _command == DONE) {
		int temp = _userInput.find_first_of(" ");
		char num = _userInput[temp+1];
		_index = num - '0';
	}

	else if(_command == EDIT) {
		std::string input = _userInput;
		int temp = input.find_first_of(" ");
		char num = input[temp+1];
		_index = num - '0';

		input = input.substr(temp+1);
		temp = input.find_first_of(" ");
		_description = input.substr(temp+1);
	}

	else if(_command == DISPLAY) {  //further functions later
			
	}
}

Parser::~Parser() {
}

/*void Parser::setCommand() {
	std::istringstream in(_userInput);
	in >> _command;
}

void Parser::setDescription() {
	int temp;
	if (_command == "add") {
		temp = _userInput.find_first_of(" ");
		_description = _userInput.substr(temp + 1);		//takes in all input after command
	}
	else if (_command == "edit") {
		temp = _userInput.find_first_of(" ");
		_description = _userInput.substr(temp + 1);
		temp = _description.find_first_of(" ");
		_description = _description.substr(temp + 1);
	}
}

void Parser::setIndex() {
	int temp = _userInput.find_first_of(" ");
	char num = _userInput[temp+1];
	_index = num - '0';
}*/

std::string Parser::getCommand() {
	return _command;
}

std::string Parser::getDescription() {
	return _description;
}

int Parser::getIndex() {
	return _index;
}