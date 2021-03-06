//@author A0116507L
#include "Parser.h"

const std::string Parser::ADD = "add";
const std::string Parser::DEL = "delete";
const std::string Parser::EDIT = "edit";
const std::string Parser::DISPLAY = "display";
const std::string Parser::DONE = "done";
const std::string Parser::EXIT = "exit";
const std::string Parser::SEARCH = "search";
const std::string Parser::UNDO = "undo";
const std::string Parser::FILE = "file";
const std::string Parser::HELP= "help";
const std::string Parser::CommandArray[11] = 
{ADD, DEL, EDIT, DISPLAY, DONE, EXIT, SEARCH, UNDO, FILE, HELP};

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
	checkStartBeforeEnd();
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
	while((endInput > 0) && input[endInput-1] == WhiteSpace) {
		endInput--;
	}

	input = input.substr(Start_Index, endInput);
}

void Parser::removeWhiteSpaces(std::string &input) {   //to remove consecutive white spaces
	int index;
	for (index = Start_Index; index < input.length() - 1; index++) {
		if (input[index] == WhiteSpace && input[index + 1] == WhiteSpace) {
			input.erase(index + 1, 1);
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
		removeCommand();
		setDescription();
	} else if(_command == DEL || _command == DONE) {
		removeCommand();
		setIndex();
	} else if(_command == EDIT) {
		removeCommand();
		setIndex();
		removeIndex();
		setDescription();
	}
}

void Parser::removeCommand() {
	int commandLength = _command.length();
	_userInput = _userInput.substr(commandLength);
}

void Parser::setDescription() {
	trimStart(_userInput);
	_description = _userInput;
	
}

void Parser::setIndex() {
	 trimStart(_userInput);
	 retrieveIndex();
}

void Parser::retrieveIndex() {
	std::istringstream iss(_userInput);
	int temp;
	iss >> temp;
	_index = temp;
}

void Parser::removeIndex() {
	int temp = _index;
	int NumberOfDigits = 0;
	do {
		temp = temp/10;
		NumberOfDigits++;
	} while(temp > 0);

	_userInput.erase(Start_Index, NumberOfDigits);
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
		do {	
			 if(!isTimedTask(temp, matchTime, foundTime) && !isDeadlineTask(temp, matchDate, foundDate)) {		//check if float task
			_TaskType = 1;
			} else if(isTimedTask(temp, matchTime, foundTime) && !isDeadlineTask(temp, matchDate, foundDate)) {	//check if timed task due today
				_TaskType = 2;
				TimeTokens.push_back(extractTime(matchTime, foundTime));

			} else if(isTimedTask(temp, matchTime, foundTime) && isDeadlineTask(temp, matchDate, foundDate)) {	//check if timed task with deadline
				_TaskType = 2;
				TimeTokens.push_back(extractTime(matchTime, foundTime)); 
				int foundIndex;
				temp = _description;
				temp = convertLowerCase(temp);
				findDateIndex(temp, matchDate, foundIndex);
				DateTokens.push_back(extractDate(matchDate, foundIndex));

			} else if(!isTimedTask(temp, matchTime, foundTime) && isDeadlineTask(temp, matchDate, foundDate)) {	//check if only deadline task
				_TaskType = 3;
				DateTokens.push_back(extractDate(matchDate, foundDate));
				}

			removeWhiteSpaces(_description);
			temp = _description;
			temp = convertLowerCase(temp);

		} while((isTimedTask(temp, matchTime, foundTime)) || (isDeadlineTask(temp, matchDate, foundDate)));
		
		 assignDateTime(DateTokens, TimeTokens);
	}	
}

bool Parser::isTimedTask(std::string input, int &matchIndex, int &foundIndex) { //check for time through whole string
	int TimeTokenIndex = findFirstTimeToken(input);
	bool isTimed = false;
	if(TimeTokenIndex > 0) {
		if(checkIfTimeToken(TimeTokenIndex)) {
			isTimed = true;
			int emptySpace = findWhiteSpace(TimeTokenIndex);
			std::string timeKeyWord = _description.substr(TimeTokenIndex);
			timeKeyWord = retrieveInfo(timeKeyWord);
			int index = 0;
			while(timeKeyWord != DateTime::TimeKeyWords[index]) {
				index++;
			}
			
			matchIndex = index;
			foundIndex = TimeTokenIndex;
		}
	}
	
	return isTimed;
}

int Parser::findFirstTimeToken(std::string input) { //return TimeToken index
	int index = -1;
	std::string temp;
	int descriptionLength = _description.length();
	for(int i = Start_Index; i < descriptionLength - 1; i++) {
		temp = input.substr(i, 2);
		if(temp == DateTime::AM || temp == DateTime::PM || temp == DateTime::NOON) {
			index = i;
			break;
		}
	}

	return index;
}

bool Parser::checkIfTimeToken(int timeTokenIndex) { //check if TimeToken has integer values
	/*/////////not used because there is another way to get the start of time string
	int emptySpace = findWhiteSpace(timeTokenStart);
	timeTokenStart = smallerNum(emptySpace, timeTokenStart);*/
	int timeTokenStart = timeTokenIndex - 4;
	int timeTokenLength = timeTokenIndex - timeTokenStart;
	std::string temp = _description.substr(timeTokenStart, timeTokenLength);
	std::string checkString = retrieveTime(temp);
	trimStart(checkString);
	if(isInteger(checkString)) {
		return true;
	}
	
	return false;
}

bool Parser::isInteger(std::string input) {
	char temp = input[0];
	bool isInt = false;
	if(isdigit(temp)) {
		isInt = true;
	}

	return isInt;
}

int Parser::findWhiteSpace(int index) {
	return _description.find_first_of(WhiteSpace, index);
}

std::string Parser::extractTime(int TimeIndex, int foundIndex) {
	std::string timeStringFound = DateTime::TimeKeyWords[TimeIndex];
	int timeStringSize = timeStringFound.length();

	int timeStart = foundIndex - 4;				//assumes max 4 characters away from time string
	std::string time = _description.substr(timeStart, 6);
	std::string timeToken = retrieveTime(time);

	int timeStartIndex = _description.find(timeToken);
	int timeTokenLength = timeToken.length();
	_description.erase(timeStartIndex, timeTokenLength);
	return timeToken;

	/* /////Not used due to difficulty of indexing when time string changes
	int emptySpace = findWhiteSpace(timeStart);
	int timeStartIndex = smallerNum(emptySpace, timeStart);

	emptySpace = _description.find_first_of(WhiteSpace, foundIndex);
	int timeEnd = foundIndex + timeStringSize;
	int timeEndIndex = smallerNum(emptySpace, timeEnd);

	std::string timeToken = _description.substr(timeStartIndex, timeEndIndex - timeStartIndex);
	trimStart(timeToken);								//ensure no white space at start

	_description.erase(timeStartIndex, timeEndIndex - timeStartIndex);		//removes the token from description*/
}

std::string Parser::retrieveTime(std::string input) {
	int index = input.find_first_of(WhiteSpace);
	if(index > 0) {
		input = input.substr(index);
	} 

	trimStart(input);
	return input;
}

bool Parser::isDeadlineTask(std::string input, int &matchIndex, int &foundIndex) {
	std::vector<std::string> Deadline;
	for(int i = 0; i < 15; i++) {
		Deadline.push_back(DateTime::DAY_MONTH[i]);
	}

	bool isDeadline = false;
	for(int index = 0; index < Deadline.size(); index++) {
		std::string temp = Deadline[index];
		int FoundDeadline = input.find(temp);
		if(FoundDeadline > 0) {
			isDeadline = true;
			matchIndex = index;
			foundIndex = FoundDeadline;
			break;
		}
	}

	return isDeadline;
}

void Parser::findDateIndex(std::string input, int dateIndex, int &foundIndex) {
	std::string temp = DateTime::DAY_MONTH[dateIndex];
	foundIndex = input.find(temp);
}

std::string Parser::extractDate(int DateIndex, int foundIndex) {
	std::string dateToken;

	if(DateIndex <= 2) {
		std::string dateStringFound = DateTime::DAY_MONTH[DateIndex];
		int dateStringSize = dateStringFound.length();
		dateToken = _description.substr(foundIndex, dateStringSize);
		_description.erase(foundIndex, dateStringSize);
		
	} else {
		int dateStartIndex = foundIndex - 3;			//assumes number is max 3 characters away from month
		int dateEnd = _description.find_first_of(WhiteSpace, foundIndex);
		
		std::string::iterator it = _description.begin();
		int EndOfString = 0;
		while(it != _description.end()) {
			it++;
			EndOfString++;
		}
		
		int dateEndIndex = smallerNum(dateEnd, EndOfString);
		dateToken = _description.substr(dateStartIndex, dateEndIndex);
		dateToken = convertLowerCase(dateToken);
		_description.erase(dateStartIndex, dateEndIndex - dateStartIndex + 1);		//removes the token from description

	}
	
	return dateToken;
}

int Parser::smallerNum(int x, int y) {
	if( x < y && x > 0) {
		return x;
	} else {
		return y;
	}
}

void Parser::assignDateTime(std::vector<std::string> DateTokens, std::vector<std::string> TimeTokens) {
	if(TimeTokens.size() == 1 && DateTokens.empty()) {
		DateTime End(TimeTokens);
		_end = End;
	}
	
	if(DateTokens.size() == 1  || TimeTokens.size() == 1){
		DateTime End(DateTokens, TimeTokens);
		_end = End;
		_TaskType = 3;
		if(!TimeTokens.empty()) { 
			DateTime Start(TimeTokens);
			_start = Start;
			int endMonth = _end.getMonth();
			int endDay = _end.getDay();
			_start.setMonth(endMonth);
			_start.setDay(endDay);
			_TaskType = 2;
		}
	} else if(DateTokens.size() == 2 || TimeTokens.size() == 2) {
		DateTime End(DateTokens, TimeTokens);
		DateTime Start(DateTokens, TimeTokens);
		_end = End;
		_start = Start;
		
	}
}
//still need to check
void Parser::compareDateTime() {
	int endMonth = _end.getMonth();
	int endHour = _end.getHour();
	int endDay = _end.getDay();
	int startMonth = _start.getMonth();

	if(endMonth != -1 && endHour != -1 && startMonth == -1) {	//when end has date and time, start no date
		_start.setMonth(endMonth);
		_start.setDay(endDay);
	}

}

void Parser::checkStartBeforeEnd() {
	if(checkStartMonthBeforeEndMonth()) {
		swapDateTime();
	} else {
		if(checkStartDayBeforeEndDay()) {
			swapDateTime();
		} else {
			if(checkStartHourBeforeEndHour()) {
				swapDateTime();
			} else {
				if(checkStartMinuteBeforeEndMinute()) {
					swapDateTime();
				}
			}
		}
	}
}

bool Parser::checkStartMonthBeforeEndMonth() {
	return (_start.getMonth() > _end.getMonth());
}

bool Parser::checkStartDayBeforeEndDay() {
	return (_start.getDay() > _end.getDay());
}

bool Parser::checkStartHourBeforeEndHour() {
	return (_start.getHour() > _end.getHour());
}

bool Parser::checkStartMinuteBeforeEndMinute() {
	return (_start.getMinute() > _end.getMinute());
}

void Parser::swapDateTime() {
	DateTime temp;
	temp = _end;
	_end = _start;
	_start = temp;
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

