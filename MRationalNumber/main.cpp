#include <iostream>

#include "MRationalNumber.h"

using namespace ArbitraryPrecisionArithmetic;
using std::cin;
using std::cout;
using std::endl;

int main(){
    // usage example

    // construtors

    MRationalNumber a;
    MRationalNumber b(2);
    MRationalNumber c(4, 5);
    MRationalNumber d(MBigInt("-12340987209485702938475"), MBigInt(8));

    cout << "a = " << endl;
    cout << a << endl;
    cout << "b = " << endl;
    cout << b << endl;
    cout << "c = " << endl;
    cout << c << endl;
    cout << "d = " << endl;
    cout << d << endl;
    cout << endl;

    // assignment operator

    b = a;
    cout << "After b = a; b = " << endl;
    cout << b << endl;

    b = -1;
    cout << "After b = -1; b = " << endl;
    cout << b << endl;
    cout << endl;

    // unary operators

    cout << "-d = " << endl;
    cout << -d << endl;
    cout << "+d = " << endl;
    cout << +d << endl;
    cout << endl;

    // comparison operators
    // equality operators
    // ==, !=, >, <, >=, <=

    cout << "b == -1 is " << (b == -1? "true": "false") << endl;
    cout << "c == 4/5 is " << (c == MRationalNumber(4, 5)? "true": "false") << endl;
    cout << "c > d is " << (c > d ? "true": "false") << endl;
    cout << endl;

    // postfix and prefix ++ and -- operators

    cout << "d++ is " << endl;
    cout << d++ << endl;
    cout << "d is " << endl;
    cout << d << endl;
    cout << endl;

    // operators + - * /

    cout << "b + 2/3 is " << endl;
    cout << b + MRationalNumber(2, 3) << endl;
    cout << "c * 5/4 is " << endl;
    cout << c * MRationalNumber(5, 4) << endl;
    cout << endl;

    // pow function

    cout << "(1/2 ^ 100) is" << endl;
    cout << pow(MRationalNumber(1, 2), 100) << endl;
    cout << endl;

    // abs function

    cout << "abs(-4/5) is " << endl;
    cout << abs(MRationalNumber(-4, 5)) << endl;
    cout << endl;

    

    return 0;
}