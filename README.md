# cpp_ArbitraryPrecisionArithmetic
ArbitraryPrecisionArithmetic assignment during C++ course at UCU

It has 2 classes available:
- <b>MBigInt</b> - arbitrary precision integer
- <b>MRationalNumber</b> - arbitrary precision rational number

<b>[MBigInt](MBigInt)</b>

What is implemented
- constructor from string and integer, default constructor(initializes 0 value), copy constructor
- assignment operator =
- unary - and + operators
- equality operators == and !=
- comparison operators > < >= <=
- casting to std::string
- operators + - * / %
- operators += -= *= /= %=
- prefix and postfix ++ and --
- function pow(for non-negative powers) and abs
- GCD and LCM functions
- ostream << operator

see usage example [here](MBigInt/main.cpp)

<b>[MRationalNumber](MRationalNumber)

What is implemented
- various constructors (from 2 MBigInts, 2 integers, 1 MBigInt(numerator), 1 integer, default constructor(initializes as 0)), copy constructo
- assignment operator =
- unary - and + operators
- equality operators == and !=
- comparison operators > < >= <=
- casting to std::string
- operators + - * /
- operators += -= *= /=
- prefix and postfix ++ and --
- function pow(for non-negative powers) and abs
- ostream << operator

see usage example [here](MRationalNumber/main.cpp)