#include "file_utils.h"

string file_utils::viewContent(string* filePath)
{
	string total;
	ifstream file;
	file.open(filePath->c_str());
	if (file.is_open())
	{
		string line;
		while (getline(file,line))
		{
			total += line + "\n";
		}
	}
	printf("网络连接信息：\n\n");
	printf("%s \n",total.c_str());
	return total;
}