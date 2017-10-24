cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(main)

set(CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")

message(STATUS ${CMAKE_C_FLAGS})

set(sources 
    ifconfig.c
)

add_executable(${CMAKE_PROJECT_NAME} ${sources})
