#include "Parser.h"

Parser::Parser() {
}

Parser::Parser(std::string input) {
	_userInput = input;
}

Parser::~Parser() {
}

void Parser::splitTokens() {
	std::string temp = _userInput;
	int previousNum = 0;
	while(temp != "\0") {
		size_t found = temp.find(",");
		std::string token = temp.substr(previousNum, found);
		tokens.push_back(token);
		previousNum = found;
	}
}
void Parser::setCommand() {
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
}

std::string Parser::getCommand() {
	return _command;
}

std::string Parser::getDescription() {
	return _description;
}

int Parser::getIndex() {
	return _index;
}