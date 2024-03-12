
#include <map>
#include <iostream>

using namespace std;

class Command {

public:

	string outputFileName;

	Command();

	bool exec(const char* commandStr);

};


extern 	map<const char*, string> systemCommandMap;