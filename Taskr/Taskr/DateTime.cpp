#include "DateTime.h"

const int DateTime::NEGATIVE_1 = -1;

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

DateTime::DateTime(std::vector<std::string> &DateTokens, std::vector<std::string> &TimeTokens) {
	if(!isEmpty(DateTokens)) {
		
		if(DateTokens.size() == 1) {		//means single date is due date
			for(int i = 0; i < DateTokens.size(); i++) {
				std::string temp = DateTokens[i];
				int x = identifyDayMonth(temp);
				if(x <= 11) {
					_month = x;
				}
				else {
					_day = x;
				}
			}
		}

		else if(DateTokens.size() == 2) {	//means there is start date and end date

			//input into start, then erase start from string, input into end
		}
	}
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

int DateTime::getEndMonth() {
	return _EndMonth;
}

int DateTime::getEndDay() {
	return _EndDay;
}

int DateTime::getEndHour() {
	return _EndHour;
}

int DateTime::getEndMinute() {
	return _EndMinute;
}