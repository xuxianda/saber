static bool isWin32()
{
#ifdef defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
	return true;
#endif
	return false;
}


static bool isApple()
{
#ifdef __APPLE__
	return true;
#elif  __MACH__
    return true;
#endif
	return false;
}


static bool isLinux()
{
#ifdef __linux__
	return true;
#endif
	return false;
}