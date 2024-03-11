#include "command.h"

map<const char*, string> systemCommandMap = map<const char*, string>();


command::command()
{
    outputFileName = "net-tools_output.txt";
    systemCommandMap["Win32"] = "ipconfig | findstr /i \"ipv4\" > t" + outputFileName;
	systemCommandMap["Apple"] = R"(ifconfig | grep -v "127.0.0.1" | grep  "inet " > )" + outputFileName;
	systemCommandMap["Linux"] = R"(ifconfig | grep -v "127.0.0.1" | grep  "inet " > )" + outputFileName;
}

bool command::exec(const char* sys)
{
	string commandStr = systemCommandMap[sys];
	if (commandStr.empty())
	{
		return false;
	}

	system(commandStr.c_str());
	return true;
}

