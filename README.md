# cpp_ArbitraryPrecisionArithmetic
ArbitraryPrecisionArithmetic assignment during C++ course at UCU

It has 2 classes available:
- <b>MBigInt</b> - arbitrary precision integer
- <b>MRationalNumber</b> - arbitrary precision rational number

<b>[MBigInt](MBigInt)</b>

What is implemented
- constructor from <b>string</b> and <b>integer</b>, <b>default</b> constructor(initializes 0 value), <b>copy</b> constructor
- assignment operator <b>=</b>
- unary <b>-</b> and <b>+</b> operators
- equality operators <b>==</b> and <b>!=</b>
- comparison operators <b>> < >= <=</b>
- casting to <b>std::string</b>
- operators <b>+ - * / %</b>
- operators <b>+= -= *= /= %=</b>
- prefix and postfix <b>++</b> and <b>--</b>
- function <b>pow</b>(for non-negative powers) and <b>abs</b>
- <b>GCD</b> and <b>LCM</b> functions
- ostream <b><<</b> operator

see usage example [here](MBigInt/main.cpp)

<b>[MRationalNumber](MRationalNumber)</b>

What is implemented
- various constructors (from <b>2 MBigInts</b>, <b>2 integers</b>, <b>1 MBigInt</b>(numerator), <b>1 integer</b>, <b>default</b> constructor(initializes as 0)), <b>copy</b> constructor
- assignment operator <b>=</b>
- unary <b>-</b> and <b>+</b> operators
- equality operators <b>==</b> and <b>!=</b>
- comparison operators <b>> < >= <=</b>
- casting to <b>std::string</b>
- operators <b>+ - * /</b>
- operators <b>+= -= *= /=</b>
- prefix and postfix <b>++</b> and <b>--</b>
- function <b>pow</b>(for non-negative powers) and <b>abs</b>
- ostream <b><<</b> operator

see usage example [here](MRationalNumber/main.cpp)