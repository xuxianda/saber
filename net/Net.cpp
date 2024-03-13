#include "Net.h"
#include "httplib.h"


std::string Net::post(std::string data, std::string host, std::string path) {
    httplib::Client client(host.c_str());
    client.set_read_timeout(10, 0);
    auto res = client.Post(path.c_str(), data.c_str(), "application/text");
    if (res && res->status == 200) {
        printf("数据上报远程响应：%s\n", res->body.c_str());
        return res->body;
    }
    printf("数据上报出现异常：%s\n", to_string(res.error()).c_str());
    if (res) {
        printf("异常状态码：%d\n", res->status);
    }
    return "";
}