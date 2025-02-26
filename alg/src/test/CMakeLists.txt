
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/../graph
        ${CMAKE_CURRENT_SOURCE_DIR}/../queue
)

file(GLOB src-files
        ${CMAKE_CURRENT_SOURCE_DIR}/../*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../graph/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../queue/*.cpp
)

aux_source_directory(. TEST_SRC_LIST)
foreach(TEST_SRC ${TEST_SRC_LIST})
    STRING(REGEX REPLACE "^\\./|\\.c[a-zA-Z0-9_]*$" "" TEST_EXE_NAME ${TEST_SRC})
    message(STATUS "添加测试程序:${TEST_EXE_NAME}")
    add_executable(${TEST_EXE_NAME} ${TEST_SRC})
endforeach(TEST_SRC ${TEST_SRC_LIST})
