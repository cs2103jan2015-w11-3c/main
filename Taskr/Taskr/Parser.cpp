#include "Parser.h"

Parser::Parser() {
}

Parser::Parser(std::string input) {
	_userInput = input;
}

Parser::~Parser() {
}

void Parser::setCommand() {
	std::string CommandType[] = {"add", "display", "delete", "edit"};
	std::vector<std::string> commands;
	commands.assign(CommandType, CommandType+4);
	int j;
	for(int i = 0; i < commands.size(); i++) {
		size_t found = _userInput.find(commands[i]);
		if(found > 0) {
			j = i;
			break;
		}
	}

	_command = commands[j];
}

void Parser::setDescription() {
	int temp;
	if(_command == "add") {
		temp = _userInput.find_first_of(" ");
	}
	else {
		temp = _userInput.find_first_of(",");
	}

	_description = _userInput.substr(temp+1);		//takes in all input after command
}

void Parser::setIndex() {
	int temp = _userInput.find_first_of(" ");
	char num = _userInput[temp+1];
	_index = num;
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