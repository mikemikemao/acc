cmake_minimum_required(VERSION 3.1.3)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
project(zlmedia LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
###最后在呈现形式
##//Default buffer size for socket
##SOCKET_DEFAULT_BUF_SIZE:STRING=262144
set(SOCKET_DEFAULT_BUF_SIZE 262144 CACHE STRING "Default buffer size for socket" FORCE)
message("The default buffer size is: ${SOCKET_DEFAULT_BUF_SIZE}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "编译类型: ${CMAKE_BUILD_TYPE}")

# 方便排查编译问题, 需要 FORCE CACHE, 否则需要命令行设置才生效
# To facilitate the troubleshooting of compilation problems, you need to FORCE CACHE, otherwise you need to set it on the command line to take effect
set(CMAKE_VERBOSE_MAKEFILE ON CACHE INTERNAL "" FORCE)

# TODO: include 当前目录会导致 server 编译出错, 待排除
#set(CMAKE_INCLUDE_CURRENT_DIR OFF)

# 安装路径
# Install path
message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
if(NOT CMAKE_INSTALL_PREFIX)
    if(UNIX)
        set(INSTALL_PATH_LIB     lib${LIB_SUFFIX})
        set(INSTALL_PATH_INCLUDE include)
        set(INSTALL_PATH_RUNTIME bin)
    elseif(WIN32)
        # Windows 下安装到了用户主目录下?
        # Install to the user's home directory under Windows?
        set(INSTALL_PATH_LIB     $ENV{HOME}/${CMAKE_PROJECT_NAME}/lib)
        set(INSTALL_PATH_INCLUDE $ENV{HOME}/${CMAKE_PROJECT_NAME}/include)
    else()
        message(WARNING "该平台(${CMAKE_SYSTEM_NAME})下暂未设置安装路径")
    endif()
else()
    set(INSTALL_PATH_LIB     ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})
    set(INSTALL_PATH_INCLUDE ${CMAKE_INSTALL_PREFIX}/include)
    set(INSTALL_PATH_RUNTIME ${CMAKE_INSTALL_PREFIX}/bin)
endif()

string(TOLOWER ${CMAKE_SYSTEM_NAME} SYSTEM_NAME_LOWER)
message(STATUS "SYSTEM_NAME_LOWER: ${SYSTEM_NAME_LOWER}")
set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/release/${SYSTEM_NAME_LOWER}/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH    ${OUTPUT_DIR})
set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_DIR})
message(STATUS "OUTPUT_DIR: ${OUTPUT_DIR}")

##############################################################################
# 添加 git 版本信息
# Add git version information
set(COMMIT_HASH "Git_Unkown_commit")
set(COMMIT_TIME "Git_Unkown_time")
set(BRANCH_NAME "Git_Unkown_branch")
set(BUILD_TIME "")

string(TIMESTAMP BUILD_TIME "%Y-%m-%dT%H:%M:%S")

find_package(Git QUIET)
if(GIT_FOUND)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short=7 HEAD
            OUTPUT_VARIABLE COMMIT_HASH
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    execute_process(
            COMMAND ${GIT_EXECUTABLE} symbolic-ref --short -q HEAD
            OUTPUT_VARIABLE BRANCH_NAME
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    execute_process(
            COMMAND ${GIT_EXECUTABLE} log --format=format:%aI -1
            OUTPUT_VARIABLE COMMIT_TIME
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()
##拷贝文件
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/ZLMVersion.h.ini
        ${CMAKE_CURRENT_BINARY_DIR}/ZLMVersion.h
        @ONLY)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "Git version is ${BRANCH_NAME} ${COMMIT_HASH}/${COMMIT_TIME} ${BUILD_TIME}")

##############################################################################
# 方便修改全局变量
# Convenient to modify global variables
function(update_cached name value)
    set("${name}" "${value}" CACHE INTERNAL "*** Internal ***" FORCE)
endfunction()

function(update_cached_list name)
    set(_tmp_list "${${name}}")
    list(APPEND _tmp_list "${ARGN}")
    list(REMOVE_DUPLICATES _tmp_list)
    update_cached(${name} "${_tmp_list}")
endfunction()

add_executable(zlmedia main.cpp)