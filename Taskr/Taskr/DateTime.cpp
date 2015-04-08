#include "DateTime.h"

const int DateTime::NEGATIVE_1 = -1;
const int DateTime::INDEX_ZERO = 0;
const std::string DateTime::TIME_DASH = "-";

//date constants
const std::string DateTime::JAN = "jan";
const std::string DateTime::FEB = "feb";
const std::string DateTime::MAR = "mar";
const std::string DateTime::APR = "apr";
const std::string DateTime::MAY = "may";
const std::string DateTime::JUN = "jun";
const std::string DateTime::JUL = "jul";
const std::string DateTime::AUG = "aug";
const std::string DateTime::SEP = "sep";
const std::string DateTime::OCT = "oct";
const std::string DateTime::NOV = "nov";
const std::string DateTime::DEC = "dec";
const std::string DateTime::TODAY = "today";
const std::string DateTime::TOMORROW = "tomorrow";
const std::string DateTime::TMR = "tmr";
const std::string DateTime::DAY_MONTH[15] = 
{JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, TODAY, TOMORROW, TMR};

const int DateTime::MONTHS_31DAYS[7] = {0,2,4,6,7,9,11};
const int DateTime::MONTHS_30DAYS[5] = {3,5,8,10};
const int DateTime::FEB_28DAYS = 1;

//time constants 
const std::string DateTime::PM = "pm";
const std::string DateTime::AM = "am";
const std::string DateTime::NOON = "noon";

const std::string DateTime::TimeKeyWords[3] = {PM, AM, NOON};

const std::string DateTime::HOUR_1 = "1";
const std::string DateTime::HOUR_2 = "2";
const std::string DateTime::HOUR_3 = "3";
const std::string DateTime::HOUR_4 = "4";
const std::string DateTime::HOUR_5 = "5";
const std::string DateTime::HOUR_6 = "6";
const std::string DateTime::HOUR_7 = "7";
const std::string DateTime::HOUR_8 = "8";
const std::string DateTime::HOUR_9 = "9";
const std::string DateTime::HOUR_10 = "10";
const std::string DateTime::HOUR_11 = "11";
const std::string DateTime::HOUR_12 = "12";
const std::string DateTime::HOURS[12] = 
{HOUR_1, HOUR_2, HOUR_3, HOUR_4, HOUR_5,HOUR_6, HOUR_7, HOUR_8, HOUR_9, HOUR_10, HOUR_11, HOUR_12};

DateTime::DateTime() {	
	_month = NEGATIVE_1;
	_day = NEGATIVE_1;
	_hour = NEGATIVE_1;
	_minute = NEGATIVE_1;
}

DateTime::~DateTime() {
}

DateTime::DateTime(std::vector<std::string> &DateTokens, std::vector<std::string> &TimeTokens) {
	if(!isEmpty(DateTokens)) {
		std::string temp = DateTokens[INDEX_ZERO];
		DateTokens.erase(DateTokens.begin());
		int x;
		if(identifyDayMonth(temp,x)) {
			if(x <= 11) {			//when user input is <day><month> or <month><day>
				_month = x;
				_day = identifyDayoftheMonth(temp);
			}

			else if(x == 12) {		//when user input "today"
				setLocalTime();
			}

			else if(x == 13 || x == 14) {	//when user input "tomorrow" or "tmr"
				setLocalTime();
				checkIfNextMonth();
			}
		}
		}
		
	
	if(!isEmpty(TimeTokens)) {
		std::string temp = TimeTokens[INDEX_ZERO];
		TimeTokens.erase(TimeTokens.begin());

		if(checkDash(temp)) {
			std::string startTime = splitTime(temp);
		}

		else {
			std::string time = extractTime(temp);
			int timeLenth = time.length();
			if(timeLenth == 1) {
				_hour = convertDigits(temp);
				_minute = INDEX_ZERO;
			}

			else if(timeLenth == 3) {
				int time = convertDigits(temp);
				_hour = extractHour(time);
				_minute = extractMinute(time);
			}
		}
	}
}

bool DateTime::identifyDayMonth(std::string input, int &x) {
	bool DayMonthFound = false;
	for(int i = 0; i < 15; i++) {
		int x = input.find(DAY_MONTH[i]);
		if(x != std::string::npos) {
			x = i;
			break;
		}
	}

	return DayMonthFound;
}

int DateTime::identifyDayoftheMonth(std::string input) {
	std::istringstream iss(input);
	int day;
	iss >> day;
	return day;
}

void DateTime::setLocalTime() {
	time_t currentTime;
	struct tm localTime;
	time(&currentTime);                  
	localtime_s(&localTime, &currentTime);
	_month = localTime.tm_mon;
	_day = localTime.tm_mday;
	_hour = localTime.tm_hour;
	
}

void DateTime::checkIfNextMonth() {			//check if tomorrow is first day of next month
	for(int i = 0; i < 7; i++) {
		if(_month == MONTHS_31DAYS[i] && _day == 31) {
			changeMonth();
		}
	}

	for(int j = 0; j < 4; j++) {
		if(_month == MONTHS_30DAYS[j] && _day == 30) {
			changeMonth();
		}
	}

	if(_month == FEB_28DAYS && _day == 28) {
		changeMonth();
	}
}

bool DateTime::checkDash(std::string input) {		//ensure both times are not in same token
	bool foundDash = false;
	int x = findDash(input);
	if(x != std::string::npos) {
		foundDash = true;
	}

	return foundDash;
}

int DateTime::findDash(std::string input) {		//returns index of dash
	int x = input.find(TIME_DASH);
	return x;
}

std::string DateTime::splitTime(std::string &input) {
	int dashIndex = findDash(input);
	std::string startTime = input.substr(INDEX_ZERO, dashIndex - INDEX_ZERO- 1);
	input.erase(INDEX_ZERO, dashIndex);

	return startTime;
}

std::string DateTime::extractTime(std::string input) {
	int index;
	for(int i = 0; i < 3; i++) {
		int x = input.find(DAY_MONTH[i]);
		if(x != std::string::npos) {
			index = i;
			break;
		}
	}	
	std::string temp = input.substr(INDEX_ZERO, index - INDEX_ZERO);
	return temp;
}

int DateTime::convertDigits(std::string input) {
	std::istringstream iss(input);
	int number;
	iss >> number;
	return number;
}

int DateTime::extractHour(int time) {
	int hour = 0;
	while(time/100 > 0) {
		time = time/100;
		hour++;
	}

	return hour;
}

int DateTime::extractMinute(int time) {
	int minute = time%100;
	return minute;
}

void DateTime::changeMonth() {
	_month += 1;
	_day = 1;
}

bool DateTime::isEmpty(std::vector<std::string> tokens) {
	return (tokens.empty());
}

int DateTime::getMonth() {
	return _month;
}

int DateTime::getDay() {
	return _day;
}

int DateTime::getHour() {
	return _hour;
}

int DateTime::getMinute() {
	return _minute;
}

void DateTime::setMonth(int month) {
	_month = month;
}

void DateTime::setDay(int day) {
	_day = day;
}

void DateTime::setHour(int hour) {
	_hour = hour;
}

void DateTime::setMinute(int minute) {
	_minute = minute;
}