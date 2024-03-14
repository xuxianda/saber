# CMakeList.txt: host-helper 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.12)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("saber")
include_directories(src/inih)
include_directories(src/cpp-httplib)

# 将源代码添加到此项目的可执行文件。
add_executable (saber  "src/Application.cpp" "src/Application.h"  "src/net/Net.cpp" "src/net/Net.h" "src/util/SysUtils.cpp" "src/util/SysUtils.h" "src/util/SysCheck.cpp" "src/util/Command.cpp" "src/util/Command.h" "src/util/FileUtils.cpp"
        "src/config/InitConfig.cpp" "src/config/InitConfig.h" "src/inih/ini.c" "src/inih/ini.h" "src/inih/cpp/INIReader.cpp" "src/inih/cpp/INIReader.h"  "src/cpp-httplib/httplib.h"
        src/util/AsyncReport.cpp
        src/util/AsyncReport.h)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET saber PROPERTY CXX_STANDARD 20)
endif()