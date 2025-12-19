cmake_minimum_required(VERSION 3.10.2)
project(c11)

#是否使用delete[]替代free，用于解决开启asan后在MacOS上的卡死问题
#use delele[] or free when asan enabled
if(ASAN_USE_DELETE)
    add_definitions(-DASAN_USE_DELETE)
endif()

#使能c++11
#Enable c++11
set(CMAKE_CXX_STANDARD 11)

#测试程序
#Test program
add_subdirectory(tests)

