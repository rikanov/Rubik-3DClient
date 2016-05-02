cmake_minimum_required(VERSION 2.6)
project(rubik_client)

add_executable(rubik_client main.cpp)

install(TARGETS rubik_client RUNTIME DESTINATION bin)
