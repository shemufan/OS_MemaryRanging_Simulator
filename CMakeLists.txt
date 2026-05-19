cmake_minimum_required(VERSION 3.10)
project(MemorySimulator)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 指定头文件搜索目录
include_directories(include)

# 收集 src 目录下的所有 .cpp 文件
file(GLOB SOURCES "src/*.cpp")

# 生成可执行文件
add_executable(simulator ${SOURCES})