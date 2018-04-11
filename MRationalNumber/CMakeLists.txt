cmake_minimum_required(VERSION 3.5)
project(MRationalNumber)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include_directories(. ../MBigInt)

file(GLOB SOURCES "*.cpp" ../MBigInt/MBigInt.cpp)

add_executable(MRationalNumber ${SOURCES})