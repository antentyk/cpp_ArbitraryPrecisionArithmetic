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
        MBigInt a(s1);
        MBigInt b(s2);
        MBigInt c(s3);

        if(a * b != c){
            cout << "Error" << endl;
            cout << a << " " << b << endl;
            cout << "Should be " << s3 << endl;
            return 0;
        }
    }

    cout << "Everything went ok" << endl;
    return 0;
}