#include "SysUtils.h"
#include "SysCheck.cpp"

SysUtils::SysUtils()
{
}



const char* SysUtils::getLocalSystemType()
{
	const char* returnStr;
	if (isWin32())
	{
		returnStr = "Win32";
	}
	else if (isApple())
	{
		returnStr = "Apple";
	}
	else if (isLinux())
	{
		returnStr = "Linux";
	}
	else
	{
		returnStr = "None";
	}

	return returnStr;
}


