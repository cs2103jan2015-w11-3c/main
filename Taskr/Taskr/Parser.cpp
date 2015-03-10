#include "Parser.h"

Parser::Parser() {
}

Parser::Parser(std::string input) {
	_userInput = input;
}

Parser::~Parser() {
}

void Parser::setCommand() {
	std::istringstream in(_userInput);
	in >> _command;
	//std::string CommandType[] = {"add", "display", "delete", "edit", "exit"};
	//std::vector<std::string> commands;
	//commands.assign(CommandType, CommandType+4);
	//int j;
	//for(int i = 0; i < commands.size(); i++) {
	//	size_t found = _userInput.find(commands[i]);
	//	if(found > 0) {
	//		j = i-1;
	//		break;
	//	}
	//}
	//_command = commands[j];
}

void Parser::setDescription() {
	int temp;
	//if(_command == "add") {
	//	temp = _userInput.find_first_of(" ");
	//}
	//else {
	//	temp = _userInput.find_first_of(",");
	//}
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