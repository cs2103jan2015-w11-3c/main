#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

class Parser {
private: 
	std::string UserInput;
	std::string command;
	std::string description;
	int index;
	
public:
	Parser(std::string input);
	~Parser();

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

