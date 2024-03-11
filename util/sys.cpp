#include "sys.h"
#include "sys_check.cpp"

sys::sys()
{
}



const char* sys::getLocalSystemType()
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


