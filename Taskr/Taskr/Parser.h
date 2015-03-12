#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>

class Parser {
private: 
	std::string _userInput;
	std::vector<std::string> tokens;
	std::string _command;
	std::string _description;
	int _index;
	
public:
	Parser();
	Parser(std::string input);
	~Parser();

	void splitTokens();
	void setCommand();
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

