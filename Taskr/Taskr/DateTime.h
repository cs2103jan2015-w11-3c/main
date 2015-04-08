#ifndef DateTime_H_
#define DateTime_H_

#include <string>
#include <vector>
#include <ctime>
#include <sstream>

class DateTime			
	//assumes user input of dates: <day><month>
	//assumes user input to be according to 12 hour clock format
	//assumes user to input the date if start time and end time are on different days
	//if non exact hour, need to separate different time i.e 515pm - 615pm (not 515-6pm)
{
private:
	int _month;
	int _day;
	int _hour;
	int _minute;

public:
	
	static const int NEGATIVE_1;
	static const int INDEX_ZERO;
	static const std::string TIME_DASH;

	//date strings
	static const std::string JAN;
	static const std::string FEB;
	static const std::string MAR;
	static const std::string APR;
	static const std::string MAY;
	static const std::string JUN;
	static const std::string JUL;
	static const std::string AUG;
	static const std::string SEP;
	static const std::string OCT;
	static const std::string NOV;
	static const std::string DEC;
	static const std::string TODAY;
	static const std::string TOMORROW;
	static const std::string TMR;
	static const std::string DAY_MONTH[15];
	static const int MONTHS_31DAYS[7];
	static const int MONTHS_30DAYS[5];
	static const int FEB_28DAYS;

	//time constants 
	static const std::string PM;
	static const std::string AM;
	static const std::string NOON;
	static const std::string TimeKeyWords[3];

	static const std::string HOUR_1;
	static const std::string HOUR_2;
	static const std::string HOUR_3;
	static const std::string HOUR_4;
	static const std::string HOUR_5;
	static const std::string HOUR_6;
	static const std::string HOUR_7;
	static const std::string HOUR_8;
	static const std::string HOUR_9;
	static const std::string HOUR_10;
	static const std::string HOUR_11;
	static const std::string HOUR_12;
	static const std::string HOURS[12];

	DateTime();
	DateTime(std::vector<std::string> &DateTokens, std::vector<std::string> &TimeTokens);
	~DateTime();

	bool isEmpty(std::vector<std::string> tokens);
	bool identifyDayMonth(std::string input,int &x);
	int identifyDayoftheMonth(std::string temp);
	int retrieveMonth(std::string input);

	void setLocalTime();
	void checkIfNextMonth();
	void changeMonth();
	bool checkDash(std::string input);
	int findDash(std::string input);
	std::string splitTime(std::string &input);
	std::string extractTime(std::string input);
	int convertDigits(std::string input);
	int extractHour(int time);
	int extractMinute(int time);

	//setters
	void setMonth(int month);
	void setDay(int day);
	void setHour(int hour);
	void setMinute(int minute);

	//getters
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();
	
};

#endif 
