cmake_minimum_required(VERSION 3.5)
project(SpyHunterDrv64)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ALLOW_LOSSE_LOOP_CONSTRUCTS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /WX")

#
# Determine 32 or 64 bit
#
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PROGRAM_64BIT TRUE)
else ()
    set(PROGRAM_64BIT FALSE)
endif ()

message("generator is set to ${CMAKE_GENERATOR}")
message("build config file will be generated under folder ${PROJECT_BINARY_DIR}")
message("Library build file output path is ${LIBRARY_OUTPUT_PATH}")
message("Executable build file output path is ${EXECUTABLE_OUTPUT_PATH}")

add_subdirectory(SpyHunterDrv64)
