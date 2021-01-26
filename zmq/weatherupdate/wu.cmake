#find cppzmq wrapper, installed by make of cppzmq
find_package(cppzmq)

add_executable(wuclient ./weatherupdate/wuclient.cpp)
target_link_libraries(wuclient cppzmq)

add_executable(wuserver ./weatherupdate/wuserver.cpp)
target_link_libraries(wuserver cppzmq)
