#include <iostream>
#include <string>

#include "MBigInt.h"

using namespace ArbitraryPrecisionArithmetic;
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(){
    // usage example

    // constructors
    // from string or int
    // copy constructor

    MBigInt a("-123412341");
    MBigInt b(1);
    MBigInt c(b);
    MBigInt d();

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << c << endl;
    cout << endl;

    // assignment operator

    b = a;
    cout << "After b = a; b is " << b << endl;
    b = -1;
    cout << "After b = -1; b is " << b << endl;
    cout << endl;

    // unary operators

    cout << "-b = " << -b << endl;
    cout << "+b = " << +b << endl;
    cout << endl;

    // comparions operators
    // equality operators
    // ==, !=, >, <, >=, <=

    cout << "b == -1 is " << (b == -1? "true": "false") << endl;
    cout << "b > a is " << (b > a? "true": "false") << endl;
    cout << endl;

    // postfix and prefix ++ and -- operators

    cout << "++b is " << ++b << endl;
    cout << "b is " << b << endl;

    cout << "a-- is " << a-- << endl;
    cout << "a is " << a << endl;
    cout << endl;

    // operators +, -, *, / and %

    a = 100;
    b = 3;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << endl;

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;
    cout << "a % b = " << a % b << endl;

    cout << "a + 5 = " << a + 5 << endl;

    cout << "You can also test +=, -=, *=, /= and %= operators" << endl; 
    cout << endl;

    // pow function

    cout << "Only for non-negative b" << endl;
    cout << "pow(a, b) = " << pow(a, b) << endl;
    cout << endl;

    a = MBigInt("-234529348576198237469187346981723469817236491823746918237469182374691283746918237");
    b = MBigInt("12837102398710293871098371092378102983710938712093710238710298091283109837");

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << endl;

    // abs function

    cout << "abs(a) = " << abs(a) << endl;
    cout << "abs(b) = " << abs(b) << endl;
    cout << endl;

    // gcd and lcm functions

    a = 15;
    b = 10;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    cout << "Only for non-negative a and b" << endl;
    cout << "GCD(a, b) = " << GCD(a, b) << endl;
    cout << "Only for non-negative a and b" << endl;
    cout << "LCM(a, b) = " << LCM(a, b) << endl;

    return 0;
}