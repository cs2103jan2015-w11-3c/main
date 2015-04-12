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
{TODAY ,TOMORROW ,TMR , JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

const int DateTime::MONTHS_31DAYS[7] = {0,2,4,6,7,9,11};
const int DateTime::MONTHS_30DAYS[5] = {3,5,8,10};
const int DateTime::FEB_28or29DAYS = 1;

//time constants 
const std::string DateTime::PM = "pm";
const std::string DateTime::AM = "am";
const std::string DateTime::NOON = "noon";

const std::string DateTime::TimeKeyWords[3] = {AM, PM, NOON};

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

DateTime::DateTime(std::vector<std::string> &TimeTokens) {
	std::string temp = TimeTokens[INDEX_ZERO];
	TimeTokens.erase(TimeTokens.begin());
	identifyTimeKeyWordIndex(temp);
	setDate();

	if(checkDash(temp)) {
		std::string startTime = splitTime(temp);
		int timeLength = startTime.length();
		removeDash(temp);

		if(timeLength == 1) {
			_hour = convertDigits(startTime);
			checkPastNoon();
			_minute = INDEX_ZERO;

			} else if(timeLength == 3) {
				int time = convertDigits(startTime);
				_hour = extractHour(time);
				checkPastNoon();
				_minute = extractMinute(time);
			}

		} else {
			std::string time = extractTime(temp);	
			int timeLength = time.length();			

			if(timeLength == 1 || timeLength == 2) {
				_hour = convertDigits(temp);
				checkPastNoon();
				_minute = INDEX_ZERO;

			} else if(timeLength == 3 || timeLength == 4) {
				int time = convertDigits(temp);
				_hour = extractHour(time);
				checkPastNoon();
				_minute = extractMinute(time);
			}

		}
}

DateTime::DateTime(std::vector<std::string> &DateTokens, std::vector<std::string> &TimeTokens) {
	if(!isEmpty(DateTokens)) {
		std::string temp = DateTokens[INDEX_ZERO];
		DateTokens.erase(DateTokens.begin());
		int DayMonthIndex = identifyDayMonth(temp);
			
		if(DayMonthIndex == 0) {		//when user input "today"
			setLocalTime();
			setByMidnight();

		} else if(DayMonthIndex == 1 || DayMonthIndex == 2) {	//when user input "tomorrow" or "tmr"
			setLocalTime();
			setTomorrowTime();
			setByMidnight();
			checkIfNextMonth();

		} else if(DayMonthIndex >= 3) {			//when user input is <day><month> or <month><day>
			setMonth(DayMonthIndex-3);
			_day = identifyDayoftheMonth(temp);
			setByMidnight();

		} 
	}
		
	if(!isEmpty(TimeTokens)) {
		/*if(isEmpty(DateTokens)) {
			setLocalTime();
		}*/
		std::string temp = TimeTokens[INDEX_ZERO];
		TimeTokens.erase(TimeTokens.begin());
		identifyTimeKeyWordIndex(temp);

		if(checkDash(temp)) {
			std::string startTime = splitTime(temp);
			int timeLength = startTime.length();
			removeDash(temp);

			if(timeLength == 1) {
				_hour = convertDigits(startTime);
				checkPastNoon();
				_minute = INDEX_ZERO;

			} else if(timeLength == 3) {
				int time = convertDigits(startTime);
				_hour = extractHour(time);
				checkPastNoon();
				_minute = extractMinute(time);
			}
		
			TimeTokens.push_back(temp);

		} else {
			std::string time = extractTime(temp);	
			int timeLength = time.length();			

			if(timeLength == 1 || timeLength == 2) {
				_hour = convertDigits(temp);
				checkPastNoon();
				_minute = INDEX_ZERO;

			} else if(timeLength == 3 || timeLength == 4) {
				int time = convertDigits(temp);
				_hour = extractHour(time);
				checkPastNoon();
				_minute = extractMinute(time);
			}

		}
	}
}

int DateTime::identifyDayMonth(std::string input) {
	int index = 0;
	int x = input.find(DAY_MONTH[index]);
	while(x == -1) {
		index++;
		x = input.find(DAY_MONTH[index]);
	}

	return index;
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
	_year = localTime.tm_year;
	_month = localTime.tm_mon;
	_day = localTime.tm_mday;
	_hour = NEGATIVE_1;
	_minute = NEGATIVE_1;
}

void DateTime::setDate() {
	time_t currentTime;
	struct tm localTime;
	time(&currentTime);                  
	localtime_s(&localTime, &currentTime);
	_year = localTime.tm_year;
	_month = localTime.tm_mon;
	_day = localTime.tm_mday;
}

void DateTime::setByMidnight() {	//set deadline to 23.59
	_hour = 23;			
	_minute = 59;
}

void DateTime::setTomorrowTime() {
	_day += + 1;
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

	if(_month == FEB_28or29DAYS && _day == 28 && !isLeapYear()) {	//when month of Feb and not leap year
		changeMonth();

	} else if(_month == FEB_28or29DAYS && _day == 29 && isLeapYear()) {
		changeMonth();
	}
}

bool DateTime::isLeapYear() {
	bool LeapYear = false;
	if(_year%4 == 0) {
		LeapYear = true;
	}

	return LeapYear;
}

void DateTime::identifyTimeKeyWordIndex(std::string input) {
	int index = 0;
	int x = input.find(TimeKeyWords[index]);
	while(x == -1) {
		index++;
		x = input.find(TimeKeyWords[index]);
	}

	_timeKeyWordIndex = index;
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
	std::string startTime = input.substr(INDEX_ZERO, dashIndex - INDEX_ZERO);
	input.erase(INDEX_ZERO, dashIndex);

	return startTime;
}

void DateTime::removeDash(std::string &input) {
	int index = input.find(TIME_DASH);
	input.erase(index, 1);
}

std::string DateTime::extractTime(std::string input) {
	int x = input.find(TimeKeyWords[_timeKeyWordIndex]);
	std::string temp = input.substr(INDEX_ZERO, x - INDEX_ZERO);
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
	while(time - 100 > 0) {
		time = time - 100;
		hour++;
	}

	return hour;
}

int DateTime::extractMinute(int time) {
	int minute = time%100;
	return minute;
}

void DateTime::checkPastNoon() {
	if(_timeKeyWordIndex >= 1 && _hour <= 11) {
		_hour += 12;
	} 
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
