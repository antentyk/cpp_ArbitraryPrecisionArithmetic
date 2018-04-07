cmake_minimum_required(VERSION 3.5)
project(MBigInt)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include_directories(.)

file(GLOB SOURCES "*.cpp")

add_executable(MBigInt ${SOURCES})