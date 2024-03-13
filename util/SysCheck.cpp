static bool isWin32()
{
#ifdef _WIN32
	return true;
#endif
	return false;
}


static bool isApple()
{
#ifdef _APPLE_
	return true;
#elif  __MACH__
    return true;
#endif
	return false;
}


static bool isLinux()
{
#ifdef _linux_
	return true;
#endif
	return false;
}