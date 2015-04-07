#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <cctype>

#include "DateTime.h"

class Parser {
private: 
	std::string _userInput;
	std::string _command;
	std::string _description;
	int _index;

	int _TaskType;		
	DateTime _start;
	DateTime _end;
	
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
	static const std::string FILE;

	static const char WhiteSpace;
	static const int Start_Index;
	static const std::string EMPTY_STRING;

	void trimInput(std::string &input);
	void trimStart(std::string &input);
	void trimEnd(std::string &input);
	void removeWhiteSpaces(std::string &input);
	void removeCommand();
	void retrieveIndex();
	void removeIndex();

	std::string retrieveInfo(std::string input);
	std::string convertLowerCase(std::string input);
	void extractParameters();
	void extractDateTimeTokens();
	void assignDateTime(std::vector<std::string> DateTokens, std::vector<std::string> TimeTokens);
	void compareDateTime();
	
	bool isTimedTask(std::string input, int &matchindex, int &foundIndex);
	bool isDeadlineTask(std::string input, int &index, int &foundIndex);
	std::string extractDate(int DateIndex, int foundIndex);
	std::string extractTime(int TimeIndex, int foundIndex);

	//setters
	void setDescription();
	void setIndex();

	//getters
	std::string getCommand();
	std::string getDescription();
	int getIndex();

	int getTaskType();
	DateTime getEnd();
	DateTime getStart();

	int getStartDateMonth();
	int getStartDateDay();
	int getStartTimeHour();
	int getStartTimeMinute();
	int getEndDateMonth();
	int getEndDateDay();
	int getEndTimeHour();
	int getEndTimeMinute();
	
};
#endif