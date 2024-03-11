
#include <map>
#include <iostream>

using namespace std;

class command {

public:

	string outputFileName;

	command();

	bool exec(const char* commandStr);

};


extern 	map<const char*, string> systemCommandMap;