#find cppzmq wrapper, installed by make of cppzmq
find_package(cppzmq)

add_executable(hwclient ./helloworld/hwclient.cpp)
target_link_libraries(hwclient cppzmq)

add_executable(hwserver ./helloworld/hwserver.cpp)
target_link_libraries(hwserver cppzmq)
