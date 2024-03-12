#include "FileUtils.h"

std::string FileUtils::viewContent(std::string* filePath)
{
	std::string total;
	std::ifstream file;
	file.open(filePath->c_str());
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file,line))
		{
			total += line + "\n";
		}
	}
	printf("网络连接信息：\n\n");
	printf("%s \n",total.c_str());
	return total;
}