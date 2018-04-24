#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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
using std::istream;
using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;

const string MBigIntSamplePath = "../test/MBigIntSample/";

bool testStream(istream& strm)
{
    char current;
    strm >> current;

    if(!strm)
        return false;
    
    strm.putback(current);

    return true;
}

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
    file.open(MBigIntSamplePath + "Random.txt");
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
    file.open(MBigIntSamplePath + "Random.txt");
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
    file.open(MBigIntSamplePath + "Random.txt");
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
    MBigInt tmp(2);
    ASSERT_TRUE(tmp == 2);
    ASSERT_FALSE(tmp != 2);
    ASSERT_FALSE(tmp == -1);
    ASSERT_TRUE(tmp != -1);

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

TEST(MBigInt, Assignment)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Random.txt");

    ASSERT_TRUE(file.is_open());

    string representation;
    while(file >> representation)
    {
        MBigInt a(representation);

        MBigInt b(1);

        if(a == b)
            continue;
        
        ASSERT_NE(b, a);

        b = a;

        ASSERT_EQ(b, MBigInt(representation));
        ASSERT_EQ(a, MBigInt(representation));
    }

    file.close();
}

TEST(MBigInt, IstreamOperator)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Random.txt");

    ASSERT_TRUE(file.is_open());

    string representation;
    while(file >> representation)
    {
        stringstream in_strm(representation);

        MBigInt a(representation);

        MBigInt b;
        in_strm >> b;

        ASSERT_EQ(a, b);
    }

    file.close();
}

TEST(MBigInt, OstreamOperator)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Random.txt");

    ASSERT_TRUE(file.is_open());

    string representation;
    while(file >> representation)
    {
        stringstream out_strm;

        MBigInt a(representation);

        out_strm << a;

        ASSERT_EQ(a, MBigInt(out_strm.str()));
    }

    file.close();
}

TEST(MBigInt, ComparisonOperators)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Gt.txt");
    ASSERT_TRUE(file.is_open());

    string res;
    MBigInt a, b;
    while(testStream(file))
    {
        file >> a >> b >> res;

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

TEST(MBigInt, UnaryOperators)
{
    ifstream file;
    file.open(MBigIntSamplePath + "UnaryMinus.txt");

    ASSERT_TRUE(file.is_open());

    MBigInt a, b;
    while(testStream(file))
    {
        file >> a >> b;

        ASSERT_EQ(-a, b);
        ASSERT_EQ(+a, a);
    }

    file.close();

    MBigInt tmp;
    ASSERT_EQ(-tmp, tmp);
    ASSERT_EQ(+tmp, tmp);
}

TEST(MBigInt, Abs)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Random.txt");

    ASSERT_TRUE(file.is_open());

    MBigInt a;
    while(testStream(file))
    {
        file >> a;

        MBigInt b = abs(a);

        if(a >= 0)
            ASSERT_EQ(a, b);
        else
            ASSERT_EQ(-a, b);
    }

    file.close();
}

TEST(MBigInt, Addition)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Addition.txt");

    ASSERT_TRUE(file.is_open());

    while(testStream(file))
    {
        MBigInt a, b, c;
        MBigInt ainitial, binitial, cinitial;

        file >> ainitial >> binitial >> cinitial;
        a = ainitial;
        b = binitial;
        c = cinitial;

        ASSERT_EQ(a + b, c);
        ASSERT_EQ(a, ainitial);
        ASSERT_EQ(b, binitial);
        ASSERT_EQ(c, cinitial);

        a += b;
        ASSERT_EQ(b, binitial);
        ASSERT_EQ(a, c);
    }

    file.close();
}

TEST(MBigInt, Subtraction)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Subtraction.txt");

    ASSERT_TRUE(file.is_open());

    while(testStream(file))
    {
        MBigInt a, b, c;
        MBigInt ainitial, binitial, cinitial;

        file >> ainitial >> binitial >> cinitial;
        a = ainitial;
        b = binitial;
        c = cinitial;

        ASSERT_EQ(a - b, c);
        ASSERT_EQ(a, ainitial);
        ASSERT_EQ(b, binitial);
        ASSERT_EQ(c, cinitial);

        a -= b;
        ASSERT_EQ(b, binitial);
        ASSERT_EQ(a, c);
    }

    file.close();
}

TEST(MBigInt, Multiplication)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Multiplication.txt");

    ASSERT_TRUE(file.is_open());

    while(testStream(file))
    {
        MBigInt a, b, c;
        MBigInt ainitial, binitial, cinitial;

        file >> ainitial >> binitial >> cinitial;
        a = ainitial;
        b = binitial;
        c = cinitial;

        ASSERT_EQ(a * b, c);
        ASSERT_EQ(a, ainitial);
        ASSERT_EQ(b, binitial);
        ASSERT_EQ(c, cinitial);

        a *= b;
        ASSERT_EQ(b, binitial);
        ASSERT_EQ(a, c);
    }

    file.close();
}

TEST(MBigInt, Division)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Division.txt");

    ASSERT_TRUE(file.is_open());

    while(testStream(file))
    {
        MBigInt a, b, c;
        MBigInt ainitial, binitial, cinitial;

        file >> ainitial >> binitial >> cinitial;
        a = ainitial;
        b = binitial;
        c = cinitial;

        ASSERT_EQ(a / b, c);
        ASSERT_EQ(a, ainitial);
        ASSERT_EQ(b, binitial);
        ASSERT_EQ(c, cinitial);

        a /= b;
        ASSERT_EQ(b, binitial);
        ASSERT_EQ(a, c);
    }

    file.close();
}

TEST(MBigInt, Modulo)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Modulo.txt");

    ASSERT_TRUE(file.is_open());

    while(testStream(file))
    {
        MBigInt a, b, c;
        MBigInt ainitial, binitial, cinitial;

        file >> ainitial >> binitial >> cinitial;
        a = ainitial;
        b = binitial;
        c = cinitial;

        ASSERT_EQ(a % b, c);
        ASSERT_EQ(a, ainitial);
        ASSERT_EQ(b, binitial);
        ASSERT_EQ(c, cinitial);

        a %= b;
        ASSERT_EQ(b, binitial);
        ASSERT_EQ(a, c);
    }

    file.close();
}

TEST(MBigInt, Power)
{
    ifstream file;
    file.open(MBigIntSamplePath + "Power.txt");

    ASSERT_TRUE(file.is_open());

    while(testStream(file))
    {
        MBigInt a, b, c, ainitial, binitial, cinitial;
        file >> ainitial >> binitial >> cinitial;

        a = ainitial;
        b = binitial;
        c = cinitial;

        ASSERT_EQ(c, pow(a, b));
        ASSERT_EQ(a, ainitial);
        ASSERT_EQ(b, binitial);
        ASSERT_EQ(c, cinitial);
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