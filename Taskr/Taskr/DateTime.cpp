#include "DateTime.h"

const int DateTime::NEGATIVE_1 = -1;
const int DateTime::ZERO_INDEX = 0;

//date strings
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

//time strings 
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
		std::string temp = DateTokens[ZERO_INDEX];
		DateTokens.erase(DateTokens.begin());
		int x = identifyDayMonth(temp);
		if(x <= 11) {
			_month = x;
			_day = identifyDayoftheMonth(temp);
		}

		else if(x == 12) {
			time_t currentTime;
			struct tm localTime;
			time(&currentTime);                   // Get the current time
			localtime_s(&localTime, &currentTime);  // Convert the current time to the local time
			_month = localTime.tm_mon;
			_day = localTime.tm_mday;
		}

		else if(x == 13 || x == 14) {
			//consider refactoring when x == 12
			//consider when tomorrow is the next month
		}
	}
	
	if(!isEmpty(TimeTokens)) {
		std::string temp = TimeTokens[ZERO_INDEX];			//if statement to ensure that both times are not in same token
	}
}

int DateTime::identifyDayMonth(std::string input) {
	int index;
	for(int i = 0; i < 15; i++) {
		int x = input.find(DAY_MONTH[i]);
		if(x != std::string::npos) {
			index = i;
			break;
		}
	}

	return index;
}

int DateTime::identifyDayoftheMonth(std::string input) {
	std::istringstream iss(input);
	int day;
	iss >> day;
	return day;
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