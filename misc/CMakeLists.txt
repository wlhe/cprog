cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_FLAGS "-std=gnu++11")

project(main)

set(sources
    # shared_ptr.cpp
    # listsort.cpp
    fileread.cpp
)

add_executable(${PROJECT_NAME} ${sources})

