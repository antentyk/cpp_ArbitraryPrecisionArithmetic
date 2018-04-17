cmake_minimum_required(VERSION 3.5)
project(ArbitraryPrecisionArithmetic)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_executable(
    MBigInt
    MBigInt/Exceptions.h
    MBigInt/main.cpp
    MBigInt/MBigInt.cpp
    MBigInt/MBigInt.h
)
add_executable(
    MRationalNumber
    MRationalNumber/Exceptions.h
    MRationalNumber/main.cpp
    MRationalNumber/MRationalNumber.h
    MRationalNumber/MRationalNumber.cpp
    MBigInt/MBigInt.h
    MBigInt/MBigInt.cpp
    MBigInt/Exceptions.h
)