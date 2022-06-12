cmake_minimum_required(VERSION 3.10)

project(hiddentest)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--version-script=${CMAKE_SOURCE_DIR}/sym.map")
set(CMAKE_CXX_FLAGS "-fvisibility=hidden")


add_library(objsym OBJECT symbol.cpp)
add_library(sym SHARED $<TARGET_OBJECTS:objsym>)
add_library(symstatic STATIC $<TARGET_OBJECTS:objsym>)

# add_library(sym SHARED symbol.cpp)
# add_library(symstatic STATIC symbol.cpp)

add_executable(hisym main.cpp)
target_link_libraries(hisym sym)
