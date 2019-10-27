cmake_minimum_required(VERSION 3.7)
project(UserSystem)

set(CMAKE_CXX_STANDARD 11)

add_executable(UserSystem main.cpp)

add_subdirectory(server)
add_subdirectory(client-native)