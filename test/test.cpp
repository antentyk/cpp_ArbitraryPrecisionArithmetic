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

TEST(MBigInt, Initialization)
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

    ASSERT_NO_THROW(MBigInt());
}

TEST(MBigInt, StringRepresentation)
{
    ifstream file;
    file.open(MBigIntSamplePath + "StringCasting.txt");
    ASSERT_TRUE(file.is_open());

    string representation;
    while(file >> representation)
    {
        MBigInt tmp(representation);

        ASSERT_EQ(representation, string(tmp));
    }

    file.close();

    representation = "100000000000000000000000000000000000000000000000000000000000";
    MBigInt tmp(representation);
    ASSERT_EQ(representation, string(tmp));

    representation = "+1029";
    tmp = MBigInt(representation);
    ASSERT_EQ("1029", string(tmp));

    tmp = MBigInt();
    ASSERT_EQ("0", string(tmp));

    tmp = MBigInt("-0");
    ASSERT_EQ("0", string(tmp));
}

TEST(MBigInt, CopyConstructor)
{
    ifstream file;
    file.open(MBigIntSamplePath + "StringCasting.txt");
    ASSERT_TRUE(file.is_open());

    string representation;
    while(file >> representation)
    {
        MBigInt a(representation);
        MBigInt b(a);

        ASSERT_EQ(representation, string(b));
    }

    file.close();
}

TEST(MBigInt, EqualityOperators)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Equal.txt");
    ASSERT_TRUE(file.is_open());

    string repr1, repr2, res;
    while(file >> repr1 >> repr2 >> res)
    {
        MBigInt a(repr1);
        MBigInt b(repr2);

        if(res == "True")
        {
            ASSERT_TRUE(a == b);
            ASSERT_FALSE(a != b);
        }
        else
        {
            ASSERT_TRUE(a != b);
            ASSERT_FALSE(a == b);
        }
    }

    file.close();
}

TEST(MBigInt, ComparisonOperators)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Gt.txt");
    ASSERT_TRUE(file.is_open());

    string repr1, repr2, res;
    while(file >> repr1 >> repr2 >> res)
    {
        MBigInt a(repr1);
        MBigInt b(repr2);

        if(res == "True")
        {
            ASSERT_TRUE(a > b);
            ASSERT_TRUE(a >= b);
            ASSERT_FALSE(a <= b);
            ASSERT_FALSE(a < b);
        }
        else
        {
            if(a == b)
            {
                ASSERT_FALSE(a > b);
                ASSERT_FALSE(a < b);
                ASSERT_TRUE(a >= b);
                ASSERT_TRUE(a <= b);
            }
            else
            {
                ASSERT_TRUE(a < b);
                ASSERT_TRUE(a <= b);
                ASSERT_FALSE(a >= b);
                ASSERT_FALSE(a > b);
            }
        }
    }

    file.close();
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