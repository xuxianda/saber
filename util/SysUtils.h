#include <iostream>
#include <codecvt>
#include <string>

class SysUtils {

public:

    SysUtils();


    /// <summary>
    ///		获取当前系统类型
    /// </summary>
    /// <returns>
    ///		系统类型字符串
    /// </returns>
    std::string getLocalSystemType();


    /// <summary>
    /// 获取应用程序运行路径
    /// </summary>
    /// <returns></returns>
    std::string getApplicationPath();


    std::string getDeviceName();


    std::string getCPUInfo();


    std::string getGPUInfo();


    uint64_t getMemInfo();


    std::string getMACAddress();

};