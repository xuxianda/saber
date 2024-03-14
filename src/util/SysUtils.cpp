#include "SysUtils.h"
#include "SysCheck.cpp"
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <VersionHelpers.h>
#include <Pdh.h>
#include <intrin.h>
#pragma comment(lib, "IPHLPAPI.lib")
#elif _APPLE_ || __MACH__

#include <unistd.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

#elif __linux__
#include <fstream>
#include <sstream>
#else
#include <unistd.h>

#endif


SysUtils::SysUtils() {
}


std::string SysUtils::getLocalSystemType() {
    std::string returnStr;
    if (isWin32()) {
        returnStr = "Win32";
    } else if (isApple()) {
        returnStr = "Apple";
    } else if (isLinux()) {
        returnStr = "Linux";
    } else {
        throw std::runtime_error("当前环境不支持运行");
    }

    return returnStr;
}


std::string SysUtils::getApplicationPath() {
#ifdef _WIN32
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    std::wstring wpath(buffer);
    std::string path = std::string(wpath.begin(), wpath.end());
    std::string::size_type pos = path.find_last_of("\\/");
#else
    char result[PATH_MAX];
    getcwd(result, PATH_MAX);
    std::string path(result);
#endif
    return path.substr(0, path.find_last_of("/\\"));
}


std::string SysUtils::getDeviceName() {
    std::string deviceName;
#ifdef _WIN32
    // 获取 Windows 计算机名
        char computerName[MAX_COMPUTERNAME_LENGTH + 1];
        DWORD size = sizeof(computerName);
        GetComputerNameA(computerName, &size);
        deviceName = computerName;
#elif __linux__ || __APPLE__
    // 获取 Linux 或 macOS 计算机名
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    deviceName = hostname;
#else
    deviceName = "Unknown";
#endif
    return deviceName;
}


std::string SysUtils::getCPUInfo() {
    std::string cpuName;
#ifdef _WIN32
    HKEY hKey;
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
        {
            char buffer[255];
            DWORD bufSize = sizeof(buffer);
            if (RegQueryValueEx(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE)buffer, &bufSize) == ERROR_SUCCESS)
            {
                cpuName = buffer;
            }
            RegCloseKey(hKey);
        }
#elif __linux__
    std::ifstream cpuinfo("/proc/cpuinfo");
        std::string line;
        while (std::getline(cpuinfo, line)) {
            if (line.substr(0, 10) == "model name") {
                cpuName = line.substr(line.find(":") + 2);
                break;
            }
        }
#elif __APPLE__ || __MACH__
    size_t len = 0;
    sysctlbyname("machdep.cpu.brand_string", NULL, &len, NULL, 0);
    if (len > 0) {
        char *brand = new char[len];
        sysctlbyname("machdep.cpu.brand_string", brand, &len, NULL, 0);
        cpuName = brand;
        delete[] brand;
    }
#endif
    return cpuName;
}

std::string SysUtils::getGPUInfo() {
    return "未知";
}

uint64_t SysUtils::getMemInfo() {
// 获取内存信息
#ifdef _WIN32
    MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx(&statex);
        return statex.ullTotalPhys;
#elif __linux__
    std::ifstream meminfo("/proc/meminfo");
        std::string line;
        while (std::getline(meminfo, line)) {
            if (line.substr(0, 8) == "MemTotal") {
                std::istringstream iss(line);
                std::string memType;
                unsigned long long totalMemory;
                iss >> memType >> totalMemory;
                return totalMemory * 1024;
                break;
            }
        }
#elif __APPLE__ || __MACH__
    int mib[2];
    size_t length;
    uint64_t physicalMemory;
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    length = sizeof(physicalMemory);
    sysctl(mib, 2, &physicalMemory, &length, NULL, 0);
    return physicalMemory;
#endif
}

std::string SysUtils::getMACAddress() {
    std::string macAddress;
#ifdef _WIN32
    // Windows 获取网卡地址
//        PIP_ADAPTER_INFO adapterInfo;
//        ULONG buflen = sizeof(PIP_ADAPTER_INFO);
//        adapterInfo = (IP_ADAPTER_INFO *)malloc(buflen);
//        if (adapterInfo == NULL) {
//            return "Error: Unable to allocate memory needed to call GetAdaptersinfo";
//        }
//        if (GetAdaptersInfo(adapterInfo, &buflen) == ERROR_BUFFER_OVERFLOW) {
//            free(adapterInfo);
//            adapterInfo = (IP_ADAPTER_INFO *)malloc(buflen);
//            if (adapterInfo == NULL) {
//                return "Error: Unable to allocate memory needed to call GetAdaptersinfo";
//            }
//        }
//        if (GetAdaptersInfo(adapterInfo, &buflen) == NO_ERROR) {
//            macAddress = adapterInfo->Address[0];
//            for (DWORD i = 1; i < adapterInfo->AddressLength; i++) {
//                macAddress += ":" + std::to_string(adapterInfo->Address[i]);
//            }
//        }
//        free(adapterInfo);
#elif __linux__
    // Linux 获取网卡地址
        std::ifstream file("/sys/class/net/eth0/address");
        if (file.is_open()) {
            std::getline(file, macAddress);
        }
        file.close();
#elif __APPLE__ || __MACH__
    // macOS 获取网卡地址
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;
    getifaddrs(&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family == AF_LINK) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = new char[18];
            sprintf(addr, "%02X:%02X:%02X:%02X:%02X:%02X",
                    (unsigned char) ifa->ifa_addr->sa_data[0],
                    (unsigned char) ifa->ifa_addr->sa_data[1],
                    (unsigned char) ifa->ifa_addr->sa_data[2],
                    (unsigned char) ifa->ifa_addr->sa_data[3],
                    (unsigned char) ifa->ifa_addr->sa_data[4],
                    (unsigned char) ifa->ifa_addr->sa_data[5]);
            macAddress = addr;
            delete[] addr;
            break;
        }
    }
    freeifaddrs(ifap);
#endif
    return macAddress;
}