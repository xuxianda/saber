//
// Created by 许显达 on 2024/3/14.
//

#include "StrUtils.h"


std::string StrUtils::uuid() {
    return uuid(16);
}

std::string StrUtils::uuid(int length) {
    std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string result;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, charset.length() - 1);
    for (int i = 0; i < length; i++) {
        result.push_back(charset[dis(gen)]);
    }
    return result;
}