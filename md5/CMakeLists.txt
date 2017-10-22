cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")


set(CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")

message(STATUS ${CMAKE_C_FLAGS})

add_executable(md5cal md5cal.c)
target_link_libraries(md5cal ssl crypto)
