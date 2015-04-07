#include "Parser.h"

const std::string Parser::CommandArray[10] = 
{ADD, DELETE, DEL, EDIT, DISPLAY, DONE, EXIT, SEARCH, UNDO};
const std::string Parser::ADD = "add";
const std::string Parser::DELETE = "delete";
const std::string Parser::DEL = "del";
const std::string Parser::EDIT = "edit";
const std::string Parser::DISPLAY = "display";
const std::string Parser::DONE = "done";
const std::string Parser::EXIT = "exit";
const std::string Parser::SEARCH = "search";
const std::string Parser::UNDO = "undo";
const std::string Parser::FILE = "file";

const char Parser::WhiteSpace = ' ';
const int Parser::Start_Index = 0;
const std::string Parser::EMPTY_STRING = "";

Parser::Parser() {
}

Parser::~Parser() {
}

Parser::Parser(std::string input) {
	trimInput(input);
	removeWhiteSpaces(input);
	_userInput = input;
	
	std::string command = retrieveInfo(input);
	command = convertLowerCase(command);
	_command = command;
	extractParameters();
	extractDateTimeTokens();
	
}

void Parser::trimInput(std::string &input) {
	trimStart(input);
	trimEnd(input);
	
}

void Parser::trimStart(std::string &input) {
	int StartInput = Start_Index;
	while(input[StartInput] == WhiteSpace) {
		StartInput++;
	}

	input = input.substr(StartInput);
}

void Parser::trimEnd(std::string &input) {
	int endInput = input.length();
	while((endInput > 0) && input[endInput] == WhiteSpace) {
		endInput--;
	}

	input = input.substr(Start_Index, endInput);
}
void Parser::removeWhiteSpaces(std::string &input) {   //to remove consecutive white spaces
	int index;
	int end = input.length();

	for(index = Start_Index; index < end; index++) {
		if((input[index] == WhiteSpace) && (input[index+1] == WhiteSpace)) {
			input.erase(index + 1, 1);
			index--;
		}
	}
}

std::string Parser::retrieveInfo(std::string input) {
	std::istringstream iss(input);
	std::string tempInfo;
	iss >> tempInfo;
	return tempInfo;
}

std::string Parser::convertLowerCase(std::string input) {
	int index;
	int commandEnd = input.length();

	for(index = Start_Index; index < commandEnd; index++) {
		input[index] = tolower(input[index]);
	}

	return input;
}

void Parser::extractParameters() {
	if(_command == ADD || _command == SEARCH || _command == DISPLAY || _command == FILE) {
		setDescription();
	}

	else if(_command == DELETE || _command == DONE) {
		setIndex();
	}

	else if(_command == EDIT) {
		setIndex();
		removeIndex();
		setDescription();
	}
}

void Parser::removeCommand() {
	int x = _userInput.find(_command);
	if(x != std::string::npos) {
		int commandSize = _command.length();
		_userInput.erase(x, commandSize);
	}
}

void Parser::setDescription() {
	removeCommand();
	trimStart(_userInput);
	_description = _userInput;
	
}

void Parser::setIndex() {
	 removeCommand();
	 trimStart(_userInput);
	 retrieveIndex();
}

void Parser::retrieveIndex() {
	int temp = _userInput[Start_Index] - '0';
	_index = temp;

}

void Parser::removeIndex() {
	_userInput.erase(Start_Index, 1);
	trimStart(_userInput);
}

void Parser::extractDateTimeTokens() {
	if(_command == ADD || _command == EDIT) {

		std::vector<std::string> DateTokens;
		std::vector<std::string> TimeTokens;
		std::string temp = _description;
		temp = convertLowerCase(temp);
		int matchTime;
		int matchDate;
		int foundTime;
		int foundDate;
		 {	
			
			 if(!isTimedTask(temp, matchTime, foundTime) && !isDeadlineTask(temp, matchDate, foundDate)) {			//check if float task
			_TaskType = 1;
			}

			else if(isTimedTask(temp, matchTime, foundTime) && !isDeadlineTask(temp, matchDate, foundDate)) {		//check if timed task due today
				_TaskType = 2;
				TimeTokens.push_back(extractTime(matchTime, foundTime));
			}
			
			else if(isTimedTask(temp, matchTime, foundTime) && isDeadlineTask(temp, matchDate, foundDate)) {		//check if timed task with deadline
				_TaskType = 2;
				TimeTokens.push_back(extractTime(matchTime, foundTime));
				DateTokens.push_back(extractDate(matchDate, foundDate));
			}
			
			else if(!isTimedTask(temp, matchTime, foundTime) && isDeadlineTask(temp, matchDate, foundDate)) {		//check if only deadline task
				_TaskType = 3;
				DateTokens.push_back(extractDate(matchDate, foundDate));
			}

			temp = _description;
			temp = convertLowerCase(temp);

		} while((isTimedTask(temp, matchTime, foundTime)) || (isDeadlineTask(temp, matchDate, foundDate)));
		
		 assignDateTime(DateTokens, TimeTokens);
	}	
}

bool Parser::isTimedTask(std::string input, int &matchIndex, int &foundIndex) {
	std::vector<std::string> Time;
	for(int i = 0; i < 3; i++) {
		Time.push_back(DateTime::TimeKeyWords[i]);
	}

	bool isTimed = false;
	for(int index = 0; index < Time.size(); index++) {
		int TimeFound = input.find(Time[index]);
		if(TimeFound > 0) {
			isTimed = true;
			break;
		}
	}

	return isTimed;
}

bool Parser::isDeadlineTask(std::string input, int &matchIndex, int &foundIndex) {
	std::vector<std::string> Deadline;
	for(int i = 0; i < 15; i++) {
		Deadline.push_back(DateTime::DAY_MONTH[i]);
	}

	bool isDeadline = false;
	for(int index = 0; index < Deadline.size(); index++) {
		int FoundDeadline = input.find(Deadline[index]);
		if(FoundDeadline > 0) {
			isDeadline = true;
			break;
		}
	}

	return isDeadline;
}

std::string Parser::extractDate(int DateIndex, int foundIndex) {
	std::string dateStringFound = DateTime::DAY_MONTH[DateIndex];
	int dateStringSize = dateStringFound.length();

	int dateStartIndex = DateIndex - 3;			//assumes number is max 3 characters away from month
	int dateEndIndex = DateIndex + dateStringSize - 1;

	std::string dateToken = _description.substr(dateStartIndex, dateEndIndex);
	_description.erase(dateStartIndex, dateEndIndex - dateStartIndex);		//removes the token from description

	return dateToken;
}

std::string Parser::extractTime(int TimeIndex, int foundIndex) {
	std::string timeStringFound = DateTime::TimeKeyWords[TimeIndex];
	int timeStringSize = timeStringFound.length();

	int timeStartIndex = TimeIndex - 4;				//assumes max 4 characters away from time string
	int timeEndIndex = TimeIndex + timeStringSize;
	std::string timeToken = _description.substr(timeStartIndex, timeEndIndex);
	int checkSpace = timeToken.find_first_of(" ");
	if(checkSpace != std::string::npos) {			//ensure no white space in timeToken
		timeToken.erase(checkSpace, 1);
	}

	_description.erase(timeStartIndex, timeEndIndex - timeStartIndex);		//removes the token from description
	return timeToken;
}

void Parser::assignDateTime(std::vector<std::string> DateTokens, std::vector<std::string> TimeTokens) {
	if(DateTokens.size() == 1  || TimeTokens.size() == 1){
		DateTime End(DateTokens, TimeTokens);
		_end = End;
	}

	else if(DateTokens.size() == 2 || TimeTokens.size() == 2) {
		DateTime End(DateTokens, TimeTokens);
		DateTime Start(DateTokens, TimeTokens);
		_end = End;
		_start = Start;
		compareDateTime();
	}
}

void Parser::compareDateTime() {
		
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

int Parser::getTaskType() {
	return _TaskType;
}

DateTime Parser::getEnd() {
	return _end;
}

DateTime Parser::getStart() {
	return _start;
}

int Parser::getEndDateMonth() {
	return _end.getMonth();
}

int Parser::getEndDateDay() {
	return _end.getDay();
}

int Parser::getEndTimeHour() {
	return _end.getHour();
}

int Parser::getEndTimeMinute() {
	return _end.getMinute();
}

int Parser::getStartDateMonth() {
	return _start.getMonth();
}

int Parser::getStartDateDay() {
	return _start.getDay();
}

int Parser::getStartTimeHour() {
	return _start.getHour();
}

int Parser::getStartTimeMinute() {
	return _start.getMinute();
}