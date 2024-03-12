#include "Net.h"
#include "httplib.h"


string Net::post(std::string *data, string *host, string *path)
{

    httplib::Client client(host->c_str());

    client.set_read_timeout(10, 0);

    auto res = client.Post(path->c_str(), data->c_str(), "application/text");

    if (res && res->status == 200) {
        printf("数据上报远程响应：%s\n", res->body.c_str());
        return res->body;
    }
    cerr << "数据上报失败：: " << res.error() << std::endl;
    if (res) {
        std::cerr << "HTTP状态码： " << res->status << std::endl;
    }

    return NULL;
}