#include "Parser.h"


Parser::Parser(std::string input) {
	UserInput = input;
}

std::string Parser::getCommand() {
	std::string CommandType[] = {"add", "view", "delete", "edit"};
	std::vector<std::string> commands;
	commands.assign(CommandType, CommandType+4);
	int j;
	for(int i = 0; i < commands.size(); i++) {
		size_t found = UserInput.find(commands[i]);
		if(found > 0) {
			j = i;
			break;
		}
	}

	command = commands[j];
	return command;
}

std::string Parser::getDescription() {
	int temp;
	if(command == "add") {
		temp = UserInput.find_first_of(" ");
	}
	else if(command == "edit") {
		temp = UserInput.find_first_of(",");
	}

	description = UserInput.substr(temp+1);		//takes in all input after command
}

int Parser::getIndex() {
	int temp = UserInput.find_first_of(" ");
	char num = UserInput[temp+1];
	index = num;
}

Parser::~Parser() {
}
