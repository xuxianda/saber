#include "SysUtils.h"
#include "SysCheck.cpp"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

SysUtils::SysUtils()
{
}



std::string SysUtils::getLocalSystemType()
{
	std::string returnStr;
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
		throw std::runtime_error("当前环境不支持运行");
	}

	return returnStr;
}



std::string SysUtils::getApplicationPath()
{
#ifdef _WIN32
	wchar_t buffer[MAX_PATH];
	GetModuleFileNameW(NULL, buffer, MAX_PATH);
	std::wstring wpath(buffer);
	std::string path = std::string(wpath.begin(), wpath.end());
	std::string::size_type pos = path.find_last_of("\\/");
#else
	char result[PATH_MAX];
	getcwd(result, PATH_MAX);
	std::string path(result);
#endif
	return path.substr(0, path.find_last_of("/\\"));
}


