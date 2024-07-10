message(STATUS "compile MediaServer")
file(GLOB MediaServer_SRC_LIST ./*.cpp ./*.h)
message(STATUS "COMPILE_DEFINITIONS:${MK_COMPILE_DEFINITIONS}")
set(COMPILE_DEFINITIONS ${MK_COMPILE_DEFINITIONS})

if(ENABLE_SERVER_LIB)
    list(APPEND COMPILE_DEFINITIONS DISABLE_MAIN)
    add_library(MediaServer STATIC ${MediaServer_SRC_LIST})
    target_compile_definitions(MediaServer
            PRIVATE ${COMPILE_DEFINITIONS})
    target_compile_options(MediaServer
            PRIVATE ${COMPILE_OPTIONS_DEFAULT})
    target_link_libraries(MediaServer
            PRIVATE ${MK_LINK_LIBRARIES})
    update_cached_list(MK_LINK_LIBRARIES MediaServer)
    return()
endif()

# IOS 不编译可执行程序，只做依赖库
if(IOS)
    add_library(MediaServer STATIC ${MediaServer_SRC_LIST})
else()
    add_executable(MediaServer ${MediaServer_SRC_LIST})
endif()

message(STATUS "target_compile_definitions:${COMPILE_DEFINITIONS}  ${COMPILE_OPTIONS_DEFAULT}")
target_compile_definitions(MediaServer
        PRIVATE ${COMPILE_DEFINITIONS})
target_compile_options(MediaServer
        PRIVATE ${COMPILE_OPTIONS_DEFAULT})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(MediaServer -Wl,--start-group ${MK_LINK_LIBRARIES} -Wl,--end-group)
else()
    #target_link_libraries(MediaServer ${MK_LINK_LIBRARIES})
endif()

install(TARGETS MediaServer DESTINATION ${CMAKE_SOURCE_DIR}/bin)
