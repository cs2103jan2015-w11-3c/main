#ifndef PARSER_H
#define PARSER_H

#include <string>
using namespace std;

class Parser {
private: 
	string command;

public:
	string getCommand();
	string getDescription();
	int getIndex();
	string getDate();
	string getStartTime();
	string getEndTime();
	string getCategory();

};
#endif
