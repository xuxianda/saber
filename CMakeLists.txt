# CMakeList.txt: host-helper 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.12)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("host-report")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inih)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cpp-httplib)

# 将源代码添加到此项目的可执行文件。
add_executable (host-helper  "Application.cpp" "Application.h"  "net/Net.cpp" "net/Net.h" "util/SysUtils.cpp" "util/SysUtils.h" "util/SysCheck.cpp" "util/Command.cpp" "util/Command.h" "util/FileUtils.cpp"
        "config/InitConfig.cpp" "config/InitConfig.h" "inih/ini.c" "inih/ini.h" "inih/cpp/INIReader.cpp" "inih/cpp/INIReader.h"  "cpp-httplib/httplib.h"
        util/AsyncReport.cpp
        util/AsyncReport.h)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET host-helper PROPERTY CXX_STANDARD 20)
endif()