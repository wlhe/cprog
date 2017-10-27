cmake_minimum_required (VERSION 2.6)

project (main)

set(tcp_dir "../../")

include_directories(${tcp_dir})

set (headers
	tcpclient.h
)

set (sources
	main.cpp
	${tcp_dir}/tcpclient.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -std=gnu++11") 

add_executable(${CMAKE_PROJECT_NAME} ${sources})
