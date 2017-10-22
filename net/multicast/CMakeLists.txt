cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
message(STATUS ${CMAKE_C_FLAGS})

add_executable(client client.c)
add_executable(server server.c)
