cmake_minimum_required(VERSION 3.1.3)
project(c11)

#加载自定义模块
#Load custom modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#设置库文件路径
#Set the library file path
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#设置可执行程序路径
#Set the executable program path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#设置子目录
#Set subdirectories
set(SUB_DIR_LIST "Network" "Poller" "Thread" "Util")

if(WIN32)
    list(APPEND SUB_DIR_LIST "win32")
    #防止Windows.h包含Winsock.h
    #Prevent Windows.h from including Winsock.h
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    if (MSVC)
        add_compile_options("/utf-8")
    endif()
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

#安装目录
#Installation directory
if(WIN32)
    set(INSTALL_PATH_LIB $ENV{HOME}/${PROJECT_NAME}/lib)
    set(INSTALL_PATH_INCLUDE $ENV{HOME}/${PROJECT_NAME}/include)
else()
    set(INSTALL_PATH_LIB lib)
    set(INSTALL_PATH_INCLUDE include)
endif()

foreach(SUB_DIR ${SUB_DIR_LIST})
    #遍历源文件
    #Traverse source file
    aux_source_directory(src/${SUB_DIR} SRC_LIST)
    #安装头文件至系统目录
    #Install header file to system directory
    install(DIRECTORY src/${SUB_DIR} DESTINATION ${INSTALL_PATH_INCLUDE} FILES_MATCHING PATTERN "*.h")
endforeach()

if(WIN32)
    set(LINK_LIB_LIST WS2_32 Iphlpapi shlwapi)
else()
    set(LINK_LIB_LIST)
endif()

#是否使用delete[]替代free，用于解决开启asan后在MacOS上的卡死问题
#use delele[] or free when asan enabled
if(ASAN_USE_DELETE)
    add_definitions(-DASAN_USE_DELETE)
endif()

#使能c++11
#Enable c++11
set(CMAKE_CXX_STANDARD 11)

if(NOT WIN32)
    add_compile_options(-Wno-deprecated-declarations)
    add_compile_options(-Wno-predefined-identifier-outside-function)
endif()

#测试程序
#Test program
add_subdirectory(tests)
add_subdirectory(testsnewke)
add_subdirectory(testsLeetcode)


