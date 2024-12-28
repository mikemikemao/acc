cmake_minimum_required(VERSION 3.28)
project(design)

set(CMAKE_CXX_STANDARD 17)
option(ENABLE_FACTORY_METHOD "Enable Factory Method" ON)

add_executable(design main.cpp)
