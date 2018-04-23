#include <iostream>
#include <string>
#include <fstream>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <gtest/gtest.h>

#include "../MBigInt/MBigInt.h"
#include "../MRationalNumber/MRationalNumber.h"

using namespace ArbitraryPrecisionArithmetic;
using std::string;
using std::ifstream;
using std::cerr;
using std::endl;

const string MBigIntSamplePath = "../test/MBigIntSample/";

TEST(MBigInt, initialization)
{
    ASSERT_ANY_THROW(MBigInt("-"));
    ASSERT_ANY_THROW(MBigInt(""));
    ASSERT_ANY_THROW(MBigInt("--"));
    ASSERT_ANY_THROW(MBigInt("+"));
    ASSERT_ANY_THROW(MBigInt("alsdkfj"));
    ASSERT_ANY_THROW(MBigInt("0aksjfdh"));
    ASSERT_ANY_THROW(MBigInt("-+0"));
    ASSERT_ANY_THROW(MBigInt("-2-1"));

    ASSERT_NO_THROW(MBigInt("+0"));
    ASSERT_NO_THROW(MBigInt("+1"));

    ifstream file;
    file.open(MBigIntSamplePath + "StringCasting.txt");
    ASSERT_TRUE(file.is_open());

    string representation;
    while(file >> representation)
        ASSERT_NO_THROW(MBigInt(representation));
    
    file.close();

    ASSERT_NO_THROW(MBigInt(-1));
    ASSERT_NO_THROW(MBigInt(1));
    ASSERT_NO_THROW(MBigInt(0));
    ASSERT_NO_THROW(MBigInt(INT_MAX));
    ASSERT_NO_THROW(MBigInt(INT_MIN));
}

int main(int argc, char ** argv)
{
    struct stat buffer;
    if(stat(MBigIntSamplePath.c_str(), &buffer) != 0)
    {
        cerr << "To begin testing, run test/MBigIntTestGenerator.py for generating samples" << endl;
        return EXIT_FAILURE;
    }

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}