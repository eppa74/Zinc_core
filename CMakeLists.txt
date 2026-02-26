cmake_minimum_required(VERSION 3.10)
project(pixel CXX)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)
file(GLOB SRC main.cpp)
add_executable(pixel ${SRC}
src/main.cpp
src/include/zinc.h)
