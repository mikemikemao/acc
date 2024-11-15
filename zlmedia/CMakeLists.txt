cmake_minimum_required(VERSION 3.1.3)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
project(zlmedia LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)

###设置编译类型
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "编译类型: ${CMAKE_BUILD_TYPE}")

# 方便排查编译问题, 需要 FORCE CACHE, 否则需要命令行设置才生效
###########################
# TODO: 测试未发现问题 可能没遇到错误
###########################
# To facilitate the troubleshooting of compilation problems, you need to FORCE CACHE, otherwise you need to set it on the command line to take effect
set(CMAKE_VERBOSE_MAKEFILE ON CACHE INTERNAL "" FORCE)

###最后在呈现形式 相当于设置了一个宏
##//Default buffer size for socket
##SOCKET_DEFAULT_BUF_SIZE:STRING=262144
set(SOCKET_DEFAULT_BUF_SIZE 262144 CACHE STRING "Default buffer size for socket" FORCE)
message("The default buffer size is: ${SOCKET_DEFAULT_BUF_SIZE}")

# TODO: include 当前目录会导致 server 编译出错, 待排除
###########################
# TODO: 未测试
###########################
set(CMAKE_INCLUDE_CURRENT_DIR OFF)

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
# 设置编译选项
# Add git version information
if(UNIX)
    # UNIX/Linux/Darwin
    set(COMPILE_OPTIONS_DEFAULT
            "-fPIC"
            "-Wall;-Wextra"
            "-Wno-unused-function;-Wno-unused-parameter;-Wno-unused-variable;-Wno-deprecated-declarations"
            "-Wno-error=extra;-Wno-error=missing-field-initializers;-Wno-error=type-limits;-Wno-comment")

    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(COMPILE_OPTIONS_DEFAULT ${COMPILE_OPTIONS_DEFAULT} "-g3")
    else()
        set(COMPILE_OPTIONS_DEFAULT ${COMPILE_OPTIONS_DEFAULT} "-g0")
    endif()
elseif(WIN32)
    if (MSVC)
        set(COMPILE_OPTIONS_DEFAULT
                # TODO: /wd4819 应该是不会生效
                "/wd4566;/wd4819;/utf-8"
                # warning C4530: C++ exception handler used, but unwind semantics are not enabled.
                "/EHsc")
        # disable Windows logo
        list(APPEND COMPILE_OPTIONS_DEFAULT "/nologo")
        list(APPEND CMAKE_STATIC_LINKER_FLAGS "/nologo")
    endif()
endif()

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
        include_directories(SYSTEM "/opt/homebrew/include")
    endif()
endif()


if(ENABLE_MEM_DEBUG)
    update_cached_list(MK_LINK_LIBRARIES
            "-Wl,-wrap,free;-Wl,-wrap,malloc;-Wl,-wrap,realloc;-Wl,-wrap,calloc")
    update_cached_list(MK_COMPILE_DEFINITIONS ENABLE_MEM_DEBUG)
    message(STATUS "Memory debugging enabled")
endif()

if(ENABLE_ASAN)
    list(APPEND COMPILE_OPTIONS_DEFAULT
            "-fsanitize=address;-fno-omit-frame-pointer")
    # https://github.com/google/sanitizers/wiki/AddressSanitizer#using-addresssanitizer
    # > In order to use AddressSanitizer you will need to
    # > compile and link your program using clang with the -fsanitize=address switch.
    update_cached_list(MK_LINK_LIBRARIES "-fsanitize=address")
    message(STATUS "Address Sanitize enabled")
endif()

if(MSVC AND ENABLE_MSVC_MT)
    set(CompilerFlags
            CMAKE_CXX_FLAGS
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_C_FLAGS
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELEASE)
    # TODO: 通常应该不需要替换
    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
endif()
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
############################################################################################################################################################
##自定义函数区
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

##############################################################################
# TODO:未测试
function(set_file_group prefix)
    message(STATUS "set_file_group " ${prefix} " " ${ARGC})
    foreach(FILE IN LISTS ARGN 1)
        # Get the directory of the source file
        get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

        # Remove common directory prefix to make the group
        string(REPLACE "${prefix}" "" GROUP "${PARENT_DIR}")

        # Make sure we are using windows slashes
        string(REPLACE "/" "\\" GROUP "${GROUP}")

        source_group("${GROUP}" FILES "${FILE}")
    endforeach()
endfunction()

##############################################################################
# TODO:未测试
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK    ccache)
endif()

############################################################################################################################################################
##应用配置区
##############################################################################
# mediakit 以及各个 runtime 依赖
# mediakit and various runtime dependencies
update_cached(MK_LINK_LIBRARIES "")
update_cached(MK_COMPILE_DEFINITIONS ENABLE_VERSION)

if (DISABLE_REPORT)
    update_cached_list(MK_COMPILE_DEFINITIONS DISABLE_REPORT)
endif ()


if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    include(CheckCXXSourceCompiles)
    file(READ ${CMAKE_CURRENT_SOURCE_DIR}/cmake/checks/atomic_check.cpp atomic_check_cpp)
    check_cxx_source_compiles("${atomic_check_cpp}" HAVE_CXX_ATOMICS_WITHOUT_LIB)
    if(NOT HAVE_CXX_ATOMICS_WITHOUT_LIB)
        # cmake --help-policy CMP0075
        list(APPEND CMAKE_REQUIRED_LIBRARIES "atomic")
        check_cxx_source_compiles("${atomic_check_cpp}" HAVE_CXX_ATOMICS_WITH_LIB)
        if(NOT HAVE_CXX_ATOMICS_WITH_LIB)
            message(WARNING "Compiler doesn't support std::atomic<long long>")
        else()
            update_cached_list(MK_LINK_LIBRARIES atomic)
        endif()
    endif()
endif()

# 多个模块依赖 ffmpeg 相关库, 统一查找
# Multiple modules depend on ffmpeg related libraries, unified search
if(ENABLE_FFMPEG)
    find_package(PkgConfig QUIET)
    # 查找 ffmpeg/libutil 是否安装
    # find ffmpeg/libutil installed
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(AVUTIL QUIET IMPORTED_TARGET libavutil)
        if(AVUTIL_FOUND)
            update_cached_list(MK_LINK_LIBRARIES PkgConfig::AVUTIL)
            message(STATUS "found library: ${AVUTIL_LIBRARIES}")
        endif()
    endif()

    # 查找 ffmpeg/libavcodec 是否安装
    # find ffmpeg/libavcodec installed
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(AVCODEC QUIET IMPORTED_TARGET libavcodec)
        if(AVCODEC_FOUND)
            update_cached_list(MK_LINK_LIBRARIES PkgConfig::AVCODEC)
            message(STATUS "found library: ${AVCODEC_LIBRARIES}")
        endif()
    endif()

    # 查找 ffmpeg/libswscale 是否安装
    # find ffmpeg/libswscale installed
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(SWSCALE QUIET IMPORTED_TARGET libswscale)
        if(SWSCALE_FOUND)
            update_cached_list(MK_LINK_LIBRARIES PkgConfig::SWSCALE)
            message(STATUS "found library: ${SWSCALE_LIBRARIES}")
        endif()
    endif()

    # 查找 ffmpeg/libswresample 是否安装
    # find ffmpeg/libswresample installed
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(SWRESAMPLE QUIET IMPORTED_TARGET libswresample)
        if(SWRESAMPLE_FOUND)
            update_cached_list(MK_LINK_LIBRARIES PkgConfig::SWRESAMPLE)
            message(STATUS "found library: ${SWRESAMPLE_LIBRARIES}")
        endif()
    endif()

    # 查找 ffmpeg/libutil 是否安装
    # find ffmpeg/libutil installed
    if(NOT AVUTIL_FOUND)
        find_package(AVUTIL QUIET)
        if(AVUTIL_FOUND)
            include_directories(SYSTEM ${AVUTIL_INCLUDE_DIR})
            update_cached_list(MK_LINK_LIBRARIES ${AVUTIL_LIBRARIES})
            message(STATUS "found library: ${AVUTIL_LIBRARIES}")
        endif ()
    endif ()

    # 查找 ffmpeg/libavcodec 是否安装
    # find ffmpeg/libavcodec installed
    if(NOT AVCODEC_FOUND)
        find_package(AVCODEC QUIET)
        if(AVCODEC_FOUND)
            include_directories(SYSTEM ${AVCODEC_INCLUDE_DIR})
            update_cached_list(MK_LINK_LIBRARIES ${AVCODEC_LIBRARIES})
            message(STATUS "found library: ${AVCODEC_LIBRARIES}")
        endif()
    endif()

    # 查找 ffmpeg/libswscale 是否安装
    # find ffmpeg/libswscale installed
    if(NOT SWSCALE_FOUND)
        find_package(SWSCALE QUIET)
        if(SWSCALE_FOUND)
            include_directories(SYSTEM ${SWSCALE_INCLUDE_DIR})
            update_cached_list(MK_LINK_LIBRARIES ${SWSCALE_LIBRARIES})
            message(STATUS "found library: ${SWSCALE_LIBRARIES}")
        endif()
    endif()

    # 查找 ffmpeg/libswresample 是否安装
    # find ffmpeg/libswresample installed
    if(NOT SWRESAMPLE_FOUND)
        find_package(SWRESAMPLE QUIET)
        if(SWRESAMPLE_FOUND)
            include_directories(SYSTEM ${SWRESAMPLE_INCLUDE_DIRS})
            update_cached_list(MK_LINK_LIBRARIES ${SWRESAMPLE_LIBRARIES})
            message(STATUS "found library: ${SWRESAMPLE_LIBRARIES}")
        endif()
    endif()

    if(AVUTIL_FOUND AND AVCODEC_FOUND AND SWSCALE_FOUND AND SWRESAMPLE_FOUND)
        update_cached_list(MK_COMPILE_DEFINITIONS ENABLE_FFMPEG)
        update_cached_list(MK_LINK_LIBRARIES ${CMAKE_DL_LIBS})
    else()
        set(ENABLE_FFMPEG OFF)
        message(WARNING "ffmpeg related functions not found")
    endif()
endif()


# 下载jemalloc后静态编译
# Static compilation after downloading jemalloc
set(DEP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdpart/external-${CMAKE_SYSTEM_NAME})
if(ENABLE_JEMALLOC_STATIC)
    if(NOT EXISTS ${DEP_ROOT_DIR})
        file(MAKE_DIRECTORY ${DEP_ROOT_DIR})
    endif()
    if (ENABLE_JEMALLOC_DUMP)
        set(ENABLE_JEMALLOC_STAT ON)
    else ()
        set(ENABLE_JEMALLOC_STAT OFF)
    endif ()
    include(Jemalloc)
    include_directories(SYSTEM ${DEP_ROOT_DIR}/${JEMALLOC_NAME}/include)
    link_directories(${DEP_ROOT_DIR}/${JEMALLOC_NAME}/lib)
    # 用于影响后续查找过程
    # Used to affect subsequent lookup process
    set(JEMALLOC_ROOT_DIR "${DEP_ROOT_DIR}/${JEMALLOC_NAME}")
endif()

# 默认链接 jemalloc 库避免内存碎片
# Link the jemalloc library by default to avoid memory fragmentation
find_package(JEMALLOC QUIET)
if(JEMALLOC_FOUND)
    message(STATUS "found library: ${JEMALLOC_LIBRARIES}")
    include_directories(${JEMALLOC_INCLUDE_DIR})
    update_cached_list(MK_LINK_LIBRARIES ${JEMALLOC_LIBRARIES})
    add_definitions(-DUSE_JEMALLOC)
    message(STATUS "jemalloc will be used to avoid memory fragmentation")
    if (ENABLE_JEMALLOC_DUMP)
        add_definitions(-DENABLE_JEMALLOC_DUMP)
        message(STATUS "jemalloc will save memory usage statistics when the program exits")
    endif ()
endif()

# 查找 openssl 是否安装
# find openssl installed
find_package(OpenSSL QUIET)
if(OPENSSL_FOUND AND ENABLE_OPENSSL)
    message(STATUS "found library: ${OPENSSL_LIBRARIES}, ENABLE_OPENSSL defined")
    include_directories(${OPENSSL_INCLUDE_DIR})
    update_cached_list(MK_COMPILE_DEFINITIONS ENABLE_OPENSSL)
    update_cached_list(MK_LINK_LIBRARIES ${OPENSSL_LIBRARIES})
    if(CMAKE_SYSTEM_NAME MATCHES "Linux" AND OPENSSL_USE_STATIC_LIBS)
        update_cached_list(MK_LINK_LIBRARIES ${CMAKE_DL_LIBS})
    elseif(CMAKE_SYSTEM_NAME MATCHES "Windows" AND OPENSSL_USE_STATIC_LIBS)
        update_cached_list(MK_LINK_LIBRARIES Crypt32)
    endif()
else()
    set(ENABLE_OPENSSL OFF)
    set(ENABLE_WEBRTC OFF)
    message(WARNING "openssl 未找到, rtmp 将不支持 flash 播放器, https/wss/rtsps/rtmps/webrtc 也将失效")
endif()

# 查找 mysql 是否安装
# find mysql installed
find_package(MYSQL QUIET)
if(MYSQL_FOUND AND ENABLE_MYSQL)
    message(STATUS "found library: ${MYSQL_LIBRARIES}, ENABLE_MYSQL defined")
    include_directories(SYSTEM
            ${MYSQL_INCLUDE_DIR}
            ${MYSQL_INCLUDE_DIR}/mysql)

    update_cached_list(MK_COMPILE_DEFINITIONS ENABLE_MYSQL)
    update_cached_list(MK_LINK_LIBRARIES ${MYSQL_LIBRARIES})
endif()

# 查找 x264 是否安装
# find x264 installed
find_package(X264 QUIET)
if(X264_FOUND AND ENABLE_X264)
    message(STATUS "found library: ${X264_LIBRARIES}, ENABLE_X264 defined")
    include_directories(SYSTEM ${X264_INCLUDE_DIRS})

    update_cached_list(MK_COMPILE_DEFINITIONS ENABLE_X264)
    update_cached_list(MK_LINK_LIBRARIES ${X264_LIBRARIES})
endif()

# 查找 faac 是否安装
# find faac installed
find_package(FAAC QUIET)
if(FAAC_FOUND AND ENABLE_FAAC)
    message(STATUS "found library:${FAAC_LIBRARIES}, ENABLE_FAAC defined")
    include_directories(SYSTEM ${FAAC_INCLUDE_DIR})
    update_cached_list(MK_COMPILE_DEFINITIONS ENABLE_FAAC)
    update_cached_list(MK_LINK_LIBRARIES ${FAAC_LIBRARIES})
endif()


if(WIN32)
    update_cached_list(MK_LINK_LIBRARIES WS2_32 Iphlpapi shlwapi)
elseif(ANDROID)
    update_cached_list(MK_LINK_LIBRARIES log)
elseif(NOT ANDROID OR IOS)
    update_cached_list(MK_LINK_LIBRARIES pthread)
endif()


if(ENABLE_VIDEOSTACK)
    if(ENABLE_FFMPEG AND ENABLE_X264)
        message(STATUS "ENABLE_VIDEOSTACK defined")
        update_cached_list(MK_COMPILE_DEFINITIONS ENABLE_VIDEOSTACK)
    else()
        message(WARNING "ENABLE_VIDEOSTACK requires ENABLE_FFMPEG and ENABLE_X264")
    endif ()
endif ()

# ----------------------------------------------------------------------------
# Solution folders:
# ----------------------------------------------------------------------------
if(USE_SOLUTION_FOLDERS)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
endif()


############################################################################################################################################################
##工程编译区
##############################################################################
# for version.h
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# for assert.h
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdpart)

add_subdirectory(3rdpart)

add_subdirectory(src)

#add_subdirectory(ext-codec)

if(ENABLE_SRT)
    add_subdirectory(srt)
endif()

if(ENABLE_WEBRTC)
    add_subdirectory(webrtc)
endif()

if(ENABLE_API)
    add_subdirectory(api)
endif()

if(ENABLE_PLAYER AND ENABLE_FFMPEG)
    add_subdirectory(player)
endif()

#MediaServer主程序
#MediaServer main program
if(ENABLE_SERVER)
    add_subdirectory(server)
endif()

# Android 会 add_subdirectory 并依赖该变量
# Android will add_subdirectory and depend on this variable
if(ENABLE_SERVER_LIB AND NOT CMAKE_PARENT_LIST_FILE STREQUAL CMAKE_CURRENT_LIST_FILE)
    set(MK_LINK_LIBRARIES ${MK_LINK_LIBRARIES} PARENT_SCOPE)
endif()


#cpp测试demo程序
#cpp test demo program
if (ENABLE_TESTS)
    add_subdirectory(tests)
endif ()

# 拷贝www文件夹、配置文件、默认证书
# Copy www folder, configuration file, default certificate
#file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/www" DESTINATION ${EXECUTABLE_OUTPUT_PATH})
#file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/conf/config.ini" DESTINATION ${EXECUTABLE_OUTPUT_PATH})
#file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/default.pem" DESTINATION ${EXECUTABLE_OUTPUT_PATH})

# 拷贝VideoStack 无视频流时默认填充的背景图片
# Copy the default background image used by VideoStack when there is no video stream
if (ENABLE_VIDEOSTACK AND ENABLE_FFMPEG AND ENABLE_X264)
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/conf/novideo.yuv" DESTINATION ${EXECUTABLE_OUTPUT_PATH})
endif ()


add_executable(zlmedia main.cpp)