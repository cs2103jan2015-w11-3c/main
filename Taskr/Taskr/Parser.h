#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <cctype>

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

	/*void setCommand();
	void setDescription();
	void setIndex();*/
	static const std::string ADD;
	static const std::string DELETE;
	static const std::string EDIT;
	static const std::string DISPLAY;
	static const std::string DONE;
	static const std::string EXIT;

	static const char WhiteSpace;
	static const int Start_Index;

	std::string trimInput(std::string input);
	std::string trimStart(std::string input);
	std::string trimEnd(std::string input);
	std::string removeWhiteSpaces(std::string input);

	std::string retrieveCommand();
	std::string convertCase(std::string command);
	void extractParameters();

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

