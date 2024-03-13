// host-helper.cpp: 定义应用程序的入口点。
//

#include <thread>
#include "Application.h"


std::string netInfo;
InitConfig initConfigObj;

int main() {
    startPrint();
    SysUtils sysUtils = SysUtils();
    printf("当前路径：%s\n", sysUtils.getApplicationPath().c_str());
    printf("设备名：%s\n", sysUtils.getDeviceName().c_str());
    printf("MAC：%s\n", sysUtils.getMACAddress().c_str());
    printf("CPU：%s\n", sysUtils.getCPUInfo().c_str());
    printf("GPU：%s\n", sysUtils.getGPUInfo().c_str());
    printf("MEM：%llu %s\n", sysUtils.getMemInfo(), "byte");
    Command commandObj = Command();
    try {
        std::string configName = "config.ini";
        initConfigObj = InitConfig();
        if (!initConfigObj.exist(configName)) {
            initConfigObj.generateConfigFile(configName);
        }
        printf("正在读取配置文件...\n");
        initConfigObj.init(configName);
    }
    catch (const std::runtime_error err) {
        printf("%s\n", err.what());
        return 0;
    }

    std::string systemName;
    try {
        systemName = sysUtils.getLocalSystemType();
        printf("当前运行环境： %s\n", systemName.c_str());
    }
    catch (std::runtime_error error) {
        std::cout << error.what();
        return 0;
    }
    try {
        commandObj.exec(systemName);
        std::string fileName = commandObj.outputFileName;
        netInfo = FileUtils().viewContent(fileName);
        while (true) {
            netTask();
            std::this_thread::sleep_for(std::chrono::milliseconds(initConfigObj.sleep));
        }
    } catch (std::runtime_error e) {
        printf("错误信息：%s\n", e.what());
    } catch (...) {

    }
    return 0;
}


void netTask() {
    AsyncReport asyncReport = AsyncReport();
    asyncReport.openAsyncTask(netInfo, &initConfigObj);
}


void startPrint() {
    printf("Saber 开始运行，正在获取配置信息...\n");


    // 根据不同的编译器，这些宏可能会有所不同
    // 对于GCC和Clang系列编译器
#if defined(__GNUC__) && defined(__cplusplus)
    std::cout << "使用GCC类编译器编译 "
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