#ifndef DateTime_H_
#define DateTime_H_

#include <string>
#include <vector>

class DateTime			//assumes use input of dates: <day><month>
{
private:
	int _month;
	int _day;
	int _hour;
	int _minute;

public:
	
	static const int NEGATIVE_1;

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

	//time strings 
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
	int identifyDayMonth(std::string input);
	int retrieveMonth(std::string input);

	//setters
	void setMonth(int);
	void setDay(int);
	void setHour(int);
	void setMinute(int);

	//getters
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();
	
};

#endif 
