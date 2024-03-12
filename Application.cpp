// host-helper.cpp: 定义应用程序的入口点。
//

#include "Application.h"
using namespace std;

int main() {
    printf("Host-Report开始运行，正在获取配置信息...\n");
    try {
        InitConfig initConfigObj = InitConfig();
    } catch (const runtime_error err) {
        printf("%s\n", err.what());
        return 0;
    }
    const char *systemName = SysUtils().getLocalSystemType();
    if (strcmp(systemName, "None") == 0) {
        printf("当前运行环境暂不支持该应用\n");
        return 0;
    }
    Command commandObj = Command();
    commandObj.exec(systemName);
    printf("当前运行环境： %s\n", systemName);

    string fileName = commandObj.outputFileName;
    FileUtils().viewContent(&fileName);

    while (true) {
        printf("%s", "正在等待远程连接获取本机信息，输入exit退出\n");
        string inputStr;
        getline(cin, inputStr);

        if (inputStr == "exit") {
            break;
        }
    }

    return 0;
}