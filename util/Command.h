
#include <map>
#include <iostream>


class Command {

public:

	std::string outputFileName;

	Command();

	bool exec(std::string commandStr);

};


extern 	std::map<std::string, std::string> systemCommandMap;