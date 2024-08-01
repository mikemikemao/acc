cmake_minimum_required(VERSION 3.10.2)

project("demo")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
message(STATUS "LIBRARY_OUTPUT_PATH:" ${LIBRARY_OUTPUT_PATH})
include(${CMAKE_CURRENT_SOURCE_DIR}/AndroidNdkGdb.cmake)
android_ndk_gdb_enable()
option(ANDROID ON)

# 添加可执行文件
add_executable(demo main.cpp)