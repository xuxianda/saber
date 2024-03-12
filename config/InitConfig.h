//
// Created by 许显达 on 2024/3/12.
//

#include <string>
#include <iostream>

class InitConfig {


public:

	std::string type;

	int port;

	std::string host;

	std::string path;

	int sleep;

	InitConfig();


	/// <summary>
	/// 加载配置文件
	/// </summary>
	/// <param name="fileName"></param>
	void init(std::string fileName);

	/// <summary>
	/// 初始化配置文件
	/// </summary>
	void generateConfigFile(std::string fileName);


	/// <summary>
	/// 判断文件是否存在
	/// </summary>
	/// <returns></returns>
	bool exist();

};

