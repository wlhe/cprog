cmake_minimum_required(VERSION 3.10)

project(main)

set(CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")

message(STATUS ${CMAKE_C_FLAGS})

set(sources 
    main.c
)

add_library(dep SHARED libdep.c)
add_library(test SHARED libtest.c)
add_executable(${CMAKE_PROJECT_NAME} ${sources})
target_link_libraries(${CMAKE_PROJECT_NAME} dep)
