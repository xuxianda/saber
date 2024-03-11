#include <iostream>

using namespace std;

class sys {

public:

	sys();


	/// <summary>
	///		获取当前系统类型
	/// </summary>
	/// <returns>
	///		系统类型字符串
	/// </returns>
	const char* getLocalSystemType();

};