cmake_minimum_required(VERSION 3.10)

project(tank C CXX)

set(CXX_FLAGS
    -g
    -Wall
    -std=c++14
    -D_PTHREADS
    -Wno-unused-parameter
    -levent
)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

ADD_DEFINITIONS(-D_DEBUG)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

include_directories(${PROJECT_SOURCE_DIR})


add_subdirectory(src/base)
add_subdirectory(src/base/example)