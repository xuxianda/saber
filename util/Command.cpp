#include "Command.h"

std::map<std::string, std::string> systemCommandMap = std::map<std::string, std::string>();


Command::Command()
{
    outputFileName = "Net-tools_output.txt";
    systemCommandMap["Win32"] = "ipconfig | findstr /i \"ipv4\" > " + outputFileName;
	systemCommandMap["Apple"] = R"(ifconfig | grep -v "127.0.0.1" | grep  "inet " > )" + outputFileName;
	systemCommandMap["Linux"] = R"(ifconfig | grep -v "127.0.0.1" | grep  "inet " > )" + outputFileName;
}

bool Command::exec(std::string sys)
{
	std::string commandStr = systemCommandMap[sys];
	if (commandStr.empty())
	{
		return false;
	}

	system(commandStr.c_str());
	return true;
}

