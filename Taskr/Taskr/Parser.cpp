#include "Parser.h"

Parser::Parser() {
}

Parser::Parser(std::string input) {
	_userInput = input;
}

Parser::~Parser() {
}

std::string Parser::getCommand() {
	std::string CommandType[] = {"add", "view", "delete", "edit"};
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
	return _command;
}

std::string Parser::getDescription() {
	int temp;
	if(_command == "add") {
		temp = _userInput.find_first_of(" ");
	}
	else if(_command == "edit") {
		temp = _userInput.find_first_of(",");
	}

	_description = _userInput.substr(temp+1);		//takes in all input after command
	return _description;
}

int Parser::getIndex() {
	int temp = _userInput.find_first_of(" ");
	char num = _userInput[temp+1];
	_index = num;
	return _index;
}

