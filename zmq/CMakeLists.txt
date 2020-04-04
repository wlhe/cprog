cmake_minimum_required(VERSION 2.8)

project(zmq)

set(CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")

#find cppzmq wrapper, installed by make of cppzmq
find_package(cppzmq)

include(helloworld/hw.cmake)
