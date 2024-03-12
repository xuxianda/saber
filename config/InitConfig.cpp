//
// Created by 许显达 on 2024/3/12.
//
#include "InitConfig.h"
#include "../inih/cpp/INIReader.h"

InitConfig::InitConfig() {
    INIReader reader("config.ini");
    if (reader.ParseError() != 0) {
        throw runtime_error("config.ini文件读取失败");
    }

    type = reader.Get("Remote", "type", "HTTP");
    printf("成功读取到配置文件\n");
    printf("选择上报方式为%s\n", type.c_str());
    if (type.compare("HTTP")) {
        host = reader.Get("remote", "host", "http://127.0.0.1:8080");
        path = reader.Get("remote", "path", "/input");
        sleep = stoi(reader.Get("remote", "sleep", "5000"));
        printf("上报地址为%s\n", host.c_str());
        printf("上报路径为%s\n", path.c_str());
        printf("上报间隔为%dms\n", sleep);
    }
}