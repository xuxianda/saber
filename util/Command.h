
#include <map>
#include <iostream>


class Command {

public:

	std::string outputFileName;

	Command();

	bool exec(const char* commandStr);

};


extern 	std::map<const char*, std::string> systemCommandMap;