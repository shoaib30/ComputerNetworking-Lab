cmake_minimum_required(VERSION 3.5)
project(CRC_16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(CRC_16 ${SOURCE_FILES})