#include "Parser.h"

const std::string Parser::CommandArray[10] = {ADD, DELETE, DEL, EDIT, DISPLAY, DONE, EXIT, SEARCH, UNDO};
const std::string Parser::ADD = "add";
const std::string Parser::DELETE = "delete";
const std::string Parser::DEL = "del";
const std::string Parser::EDIT = "edit";
const std::string Parser::DISPLAY = "display";
const std::string Parser::DONE = "done";
const std::string Parser::EXIT = "exit";
const std::string Parser::SEARCH = "search";
const std::string Parser::UNDO = "undo";

//date strings
const std::string Parser::JAN = "jan";
const std::string Parser::FEB = "feb";
const std::string Parser::MAR = "mar";
const std::string Parser::APR = "apr";
const std::string Parser::MAY = "may";
const std::string Parser::JUN = "jun";
const std::string Parser::JUL = "jul";
const std::string Parser::AUG = "aug";
const std::string Parser::SEP = "sep";
const std::string Parser::OCT = "oct";
const std::string Parser::NOV = "nov";
const std::string Parser::DEC = "dec";
const std::string Parser::MONTH[12] = {JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

//time strings 
const std::string Parser::PM = "pm";
const std::string Parser::AM = "am";
const std::string Parser::NOON = "noon";
const std::string Parser::TODAY = "today";
const std::string Parser::TOMORROW = "tomorrow";
const std::string Parser::TMR = "tmr";
const std::string Parser::TimeKeyWords[10] = {PM, AM, NOON, TODAY, TOMORROW, TMR};

const std::string Parser::FROM = "from";

const char Parser::WhiteSpace = ' ';
const int Parser::Start_Index = 0;
const std::string Parser::EMPTY_STRING = "";

Parser::Parser() {
}

Parser::Parser(std::string input) {
	/*input = trimInput(input);
	input = removeWhiteSpaces(input);*/
	_userInput = input;
	
	std::string command = retrieveInfo(input);
	command = convertCase(command);
	_command = command;
	extractParameters();
	Date date = initializeDate();
	Time time = intializeTime();
	date = findDate(date);

}

std::string Parser::trimInput(std::string input) {
	input = trimEnd(input);
	return input;
}

std::string Parser::trimEnd(std::string input) {
	int endInput = input.length();
	while((endInput > 0) && input[endInput] == WhiteSpace) {
		endInput--;
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

std::string Parser::retrieveInfo(std::string input) {
	std::istringstream iss(input);
	std::string tempInfo;
	iss >> tempInfo;
	return tempInfo;
}

std::string Parser::convertCase(std::string input) {
	int index;
	int commandEnd = input.length();

	for(index = Start_Index; index < commandEnd; index++) {
		input[index] = tolower(input[index]);
	}

	return input;
}

void Parser::extractParameters() {
	if(_command == ADD || _command == SEARCH) {
		setDescription();
	}

	else if(_command == DELETE || _command == DONE) {
		setIndex();
	}

	else if(_command == EDIT) {
		setIndex();
		setDescription();
	}

	else if(_command == DISPLAY) {  //further functions later
			
	}
}

Date Parser::initializeDate() {
	Date date;
	date.month = -1;
	date.day = -1;
	return date;
}

Time Parser::intializeTime() {
	Time time;
	time.hour = -1;
	time.minute = -1;
	return time;
}

Deadline Parser::initializeDeadline(Date date, Time time) {
	Deadline deadline;
	deadline.date = date;
	deadline.time = time;
	return deadline;
}

Date Parser::findDate(Date date) {
	if(_command == ADD || _command == EDIT) {
		_description = convertCase(_description);
		std::string temp = _description;

		std::vector<std::string> stringList;
		stringList.assign(MONTH, MONTH+12);
		int foundString = findCommonString(temp,stringList);			//returns index of commmon string, -1 if not found
	}

	return date;
}

int Parser::findCommonString(std::string input, std::vector<std::string> stringList) {
	unsigned int x;
	int size = stringList.size();
	for(int i = 0; i < size; i++) {
		bool found = false;
		x = input.find(stringList[i]);
		if( x > 0) {
			return x;
		}
		else {
			return -1;
		}

	}
}


void Parser::setDescription() {
	int temp = _userInput.find_first_of(" ");
	_description = _userInput.substr(temp+1);
}

void Parser::setIndex() {
	int temp = _userInput.find_first_of(" ");
	char num = _userInput[temp+1];
	_index = num - '0';
	_userInput = _userInput.substr(temp+1);
}

Parser::~Parser() {
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