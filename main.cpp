#include <iostream>
#include <string>

#include "MBigInt.h"

using namespace ArbitraryPrecisionArithmetic;
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(){
    string s1, s2, s3;

    while(cin >> s1 >> s2 >> s3){
        MBigInt
            a(s1),
            b(s2),
            c(s3);
        
        if(a / b != c){
            cout << "Error" << endl;
            cout << a << endl;
            cout << b << endl;

            cout << "Should be " << c <<endl;
            cout << "You got   " << (a / b) << endl;
            return 0;
        }
    }

    cout << "Everyting went ok" << endl;

    return 0;
}