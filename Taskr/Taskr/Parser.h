#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

class Parser {
private: 
	std::string _userInput;
	std::string _command;
	std::string _description;
	int _index;
	
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

