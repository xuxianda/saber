#include "Net.h"
#include "httplib.h"


std::string Net::post(std::string data, std::string host, std::string path, std::string token, std::string deviceId) {
    httplib::Client client(host.c_str());
    client.set_read_timeout(10, 0);
    httplib::Headers headers;
    headers.insert({"accessToken", token});
    headers.insert({"deviceId", deviceId});

    auto res = client.Post(path.c_str(), headers, data.c_str(), "application/text");
    if (res && res->status == 200) {
        printf("数据上报远程响应：\n%s\n", res->body.c_str());
        return res->body;
    }
    printf("数据上报出现异常：%s\n", to_string(res.error()).c_str());
    if (res) {
        printf("异常状态码：%d\n", res->status);
        switch (res->status) {
            case 400:
                printf("异常信息：Bad Request - 请求无法被服务器理解\n");
                break;
            case 401:
                printf("异常信息：Unauthorized - 请求未经过身份验证\n");
                break;
                // 其他状态码...
            default:
                printf("异常信息：未知异常，请查看状态码%d\n", res->status);
        }
    }
    return "";
}