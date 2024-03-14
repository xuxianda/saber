//
// Created by 许显达 on 2024/3/14.
//

#ifndef SABER_STRUTILS_H
#define SABER_STRUTILS_H

#include <string>
#include <random>


class StrUtils {
public:
    std::string uuid();

    std::string uuid(int length);
};


#endif //SABER_STRUTILS_H
