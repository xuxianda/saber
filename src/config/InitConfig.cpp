//
// Created by 许显达 on 2024/3/12.
//
#include "InitConfig.h"
#include "../inih/cpp/INIReader.h"
#include "fstream"
#include "../util/SysUtils.h"
#include "../util/Command.h"
#include "../util/StrUtils.h"

void InitConfig::generateConfigFile(std::string fileName) {
    std::string applicationPath = SysUtils().getApplicationPath();
    std::string filePath = applicationPath + "/" + fileName;
    std::ofstream configFile(filePath);
    if (configFile.is_open()) {
        // 写入配置文件内容
        configFile << "[Device]\n";
        configFile << "id=" << StrUtils().uuid() << "\n";
        configFile << "\n";
        configFile << "[Remote]\n";
        configFile << "type=HTTP\n";
        configFile << "\n";
        configFile << "[HTTP]\n";
        configFile << "host=http://127.0.0.1:53191\n";
        configFile << "path=/api/v1/device\n";
        configFile << "sleep=15000\n";
        configFile << "token=token123456789\n";
        configFile.flush();
        configFile.close();
        std::cout << "初次启动应用，已创建配置文件'" << filePath << "'\n";
    } else {
        std::cerr << "Unable to open file '" << filePath << "' for writing.\n";
    }
}


void InitConfig::init(std::string fileName) {
    std::string applicationPath = SysUtils().getApplicationPath();
    std::string filePath = applicationPath + "/" + fileName;
    INIReader reader(filePath);
    if (reader.ParseError() != 0) {
        throw std::runtime_error("config.ini 文件读取失败");
    }

    type = reader.Get("Remote", "type", "HTTP");
    printf("成功读取到配置文件\n");
    printf("选择上报方式为：%s\n", type.c_str());
    if (type.compare("HTTP") == 0) {
        host = reader.Get("HTTP", "host", "http://127.0.0.1:53191");
        path = reader.Get("HTTP", "path", "/api/v1/device");
        // 默认15秒上报一次
        sleep = stoi(reader.Get("HTTP", "sleep", "15000"));
        token = reader.Get("HTTP", "token", "token123456789");
        id = reader.Get("Device", "id", StrUtils().uuid());
        printf("上报地址为%s\n", host.c_str());
        printf("上报路径为%s\n", path.c_str());
        printf("上报间隔为%dms\n", sleep);
    }
}


bool InitConfig::exist(std::string fileName) {
    std::string applicationPath = SysUtils().getApplicationPath();
    std::string filePath = applicationPath + "/" + fileName;
    bool result = false;
    std::ifstream file(filePath);
    if (file) {
        // 如果能够成功打开并读取文件，则认为文件存在
        result = true;
    }
    file.close();
    return result;
}