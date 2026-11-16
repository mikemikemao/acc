PROJECT(thirdparty C CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

set(COMPILE_OPTIONS_DEFAULT
		"-fPIC"
		"-Wall;-Wextra"
		"-Wno-unused-function;-Wno-unused-parameter;-Wno-unused-variable;-Wno-deprecated-declarations"
		"-Wno-error=extra;-Wno-error=missing-field-initializers;-Wno-error=type-limits;-Wno-comment")
 message(STATUS "CMAKE_SOURCE_DIR : ${CMAKE_SOURCE_DIR}")
add_library(
		libhicore
		SHARED
		IMPORTED
		)
	
set_target_properties(
		libhicore
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/libhicore.so)
		
set(native-libs
        android
        log
        m
        z
        )


add_executable(test test.cpp)

target_link_libraries( # Specifies the target library.
        test
		PRIVATE
		libhicore
		${native-libs}
        # Links the target library to the log library
        # included in the NDK.
        )