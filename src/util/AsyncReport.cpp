//
// Created by 许显达 on 2024/3/13.
//

#include <thread>
#include "AsyncReport.h"


void AsyncReport::openAsyncTask(std::string data, InitConfig* initConfig) {
	try {
		printf("开始上报数据...\n");
		Net().post(data, initConfig->host, initConfig->path, initConfig->token,initConfig->id);
	}
	catch (const std::exception& e) {
		printf("上报数据异常: %s\n", e.what());
	}
	catch (...) {
		printf("上报数据异常: 未知错误\n");
	}
}