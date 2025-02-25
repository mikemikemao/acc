cmake_minimum_required(VERSION 3.1.3)
project(c11)

#使能c++11
#Enable c++11
set(CMAKE_CXX_STANDARD 11)

#测试程序
#Test program
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(testsnewke)
add_subdirectory(testsLeetcode)


