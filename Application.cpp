// host-helper.cpp: 定义应用程序的入口点。
//

#include "Application.h"

int main() {
	printf("Host-Report开始运行，正在获取配置信息...\n");
	printCPPVersion();
	InitConfig initConfigObj;
	Command commandObj = Command();
	try {
		initConfigObj = InitConfig();
		if (!initConfigObj.exist(commandObj.outputFileName))
		{
			initConfigObj.generateConfigFile(commandObj.outputFileName);
		}
	}
	catch (const std::runtime_error err) {
		printf("%s\n", err.what());
		return 0;
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



void printCPPVersion() {
	// 根据不同的编译器，这些宏可能会有所不同
	// 对于GCC和Clang系列编译器
#if defined(__GNUC__) && defined(__cplusplus)
	std::cout << "使用GCC类编译器编译。C++版本: "
		<< __cplusplus << std::endl;

#elif defined(_MSC_VER)  // 对于Microsoft Visual C++
#if _MSVC_LANG >= 201402L
	std::cout << "使用Microsoft Visual C++编译器编译。C++版本: C++14或更高" << std::endl;
#elif _MSVC_LANG == 201103L
	std::cout << "使用Microsoft Visual C++编译器编译。C++版本: C++11" << std::endl;
#else
	std::cout << "使用Microsoft Visual C++编译器编译。" << std::endl;
#endif

#else
	std::cout << "未知编译器。可能无法准确检测C++版本。" << std::endl;
#endif

	printf("%d", __cplusplus);
	// 更精确地映射C++标准版本
	if (__cplusplus >= 202002L)
		std::cout << "检测到的C++版本: C++20" << std::endl;
	else if (__cplusplus >= 201703L)
		std::cout << "检测到的C++版本: C++17" << std::endl;
	else if (__cplusplus >= 201402L)
		std::cout << "检测到的C++版本: C++14" << std::endl;
	else if (__cplusplus >= 201103L)
		std::cout << "检测到的C++版本: C++11" << std::endl;
	else
		std::cout << "早于C++11的标准" << std::endl;
}