// host-helper.cpp: 定义应用程序的入口点。
//

#include "Application.h"

int main() {
	printf("Host-Report开始运行，正在获取配置信息...\n");
	InitConfig initConfigObj;
	Command commandObj = Command();
	try {
		initConfigObj = InitConfig();
	}
	catch (const std::runtime_error err) {
		printf("%s\n", err.what());
		initConfigObj.generateConfigFile(commandObj.outputFileName);
	}

	SysUtils sysUtils = SysUtils();
	std::string systemName;

	try {
		systemName = sysUtils.getLocalSystemType();
	}
	catch (std::runtime_error error)
	{
		std::cout << error.what();
		return 0;
	}

	printf("当前路径：%s", sysUtils.getApplicationPath());
	commandObj.exec(systemName);
	printf("当前运行环境： %s\n", systemName);

	std::string fileName = commandObj.outputFileName;
	FileUtils().viewContent(&fileName);

	while (true) {
		printf("%s", "正在等待远程连接获取本机信息，输入exit退出\n");
		std::string inputStr;
		std::getline(std::cin, inputStr);

		if (inputStr == "exit") {
			break;
		}
	}

	return 0;
}