#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <cctype>

struct Date 
{int month; int day;};

struct Time
{int hour; int minute;};

struct Deadline
{Date date; Time time;};

class Parser {
private: 
	std::string _userInput;
	std::vector<std::string> tokens;	//for further parameters
	std::string _command;
	std::string _description;
	int _index;
	
public:
	Parser();
	Parser(std::string input);
	~Parser();

	//command strings
	static const std::string CommandArray[10];
	static const std::string ADD;
	static const std::string DELETE;
	static const std::string DEL;
	static const std::string EDIT;
	static const std::string DISPLAY;
	static const std::string DONE;
	static const std::string EXIT;
	static const std::string SEARCH;
	static const std::string UNDO;

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
	static const std::string MONTH[12];

	static const char WhiteSpace;
	static const int Start_Index;
	static const std::string EMPTY_STRING;

	//time strings 
	static const std::string PM;
	static const std::string pm;
	static const std::string AM;
	static const std::string am;
	static const std::string NOON;
	static const std::string TODAY;
	static const std::string TOMORROW;
	static const std::string TMR;
	static const std::string TimeKeyWords[10];

	static const std::string FROM;
	
	std::string trimInput(std::string input);
	std::string trimEnd(std::string input);
	std::string removeWhiteSpaces(std::string input);

	std::string retrieveCommand();
	std::string convertCase(std::string command);
	void extractParameters();
	Date initializeDate();
	Time intializeTime();
	Deadline initializeDeadline(Date date, Time time);

	void setDescription();
	void setIndex();

	std::string getCommand();
	std::string getDescription();
	int getIndex();
	/*std::string getDate();
	std::string getStartTime();
	std::string getEndTime();
	std::string getCategory();
	*/
};
#endif