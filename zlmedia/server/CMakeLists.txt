message(STATUS "compile MediaServer")
INCLUDE(../cmake/toolchain.cmake)
file(GLOB MediaServer_SRC_LIST ./*.cpp ./*.h)
message(STATUS "BIN_PATH:${BIN_PATH}")
set(COMPILE_DEFINITIONS ${MK_COMPILE_DEFINITIONS})


include_directories(.)
include_directories(../3rdpartSDK/include)


# IOS 不编译可执行程序，只做依赖库
add_executable(MediaServer ${MediaServer_SRC_LIST})

message(STATUS "target_compile_definitions:${COMPILE_DEFINITIONS}  ${COMPILE_OPTIONS_DEFAULT}")
target_compile_definitions(MediaServer
        PRIVATE ${COMPILE_DEFINITIONS})
target_compile_options(MediaServer
        PRIVATE ${COMPILE_OPTIONS_DEFAULT})
target_link_libraries(MediaServer -Wl,--start-group ${3RDPART_SDK}/lib/libZLToolKit.a -Wl,--end-group)


install(TARGETS MediaServer DESTINATION ${BIN_PATH}/)
