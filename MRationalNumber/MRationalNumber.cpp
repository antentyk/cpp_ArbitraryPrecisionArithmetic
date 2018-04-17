#include <algorithm>

#include "MRationalNumber.h"

using namespace ArbitraryPrecisionArithmetic;
using std::string;
using std::min;
using std::max;

MRationalNumber::MRationalNumber
(
    const MBigInt &numerator,
    const MBigInt &denominator
):
    numerator(numerator),
    denominator(denominator)
{
    if(denominator == 0)
        throw ZeroDenominator();
    
    reduce();
}

MRationalNumber::MRationalNumber(int numerator, int denominator):
MRationalNumber(MBigInt(numerator), MBigInt(denominator)){}

MRationalNumber::MRationalNumber(const MRationalNumber &other):
    numerator(other.numerator),
    denominator(other.denominator)
{}

MRationalNumber::MRationalNumber(const MBigInt &numerator):
MRationalNumber(numerator, 1){}

MRationalNumber::MRationalNumber(int numerator):
MRationalNumber(MBigInt(numerator)){}

MRationalNumber::MRationalNumber():
MRationalNumber(0){}

MRationalNumber& MRationalNumber::reduce(){
    if(denominator < 0){
        numerator *= -1;
        denominator *= -1;
    }

    MBigInt g = GCD(abs(numerator), denominator);
    denominator /= g;
    numerator /= g;

    return *this;
}

void MRationalNumber::leastCommonDenominator
(
    const MRationalNumber &lhs,
    const MRationalNumber &rhs,
    MBigInt * newLhsDenominator,
    MBigInt * newRhsDenominator,
    MBigInt * newLhsNumerator,
    MBigInt * newRhsNumerator
)
{
    MBigInt lcm = LCM(lhs.denominator, rhs.denominator);

    if(newLhsNumerator != nullptr)
        *newLhsNumerator = lhs.numerator * (lcm / lhs.denominator);
    
    if(newRhsNumerator != nullptr)
        *newRhsNumerator = rhs.numerator * (lcm / rhs.denominator);
    
    if(newLhsDenominator != nullptr)
        *newLhsDenominator = lcm;
    
    if(newRhsDenominator != nullptr)
        *newRhsDenominator = lcm;
}

MRationalNumber::operator string() const{
    string numerator_str = static_cast<string>(numerator);
    string denominator_str = static_cast<string>(denominator);

    size_t max_size = max(numerator_str.size(), denominator_str.size());
    
    string result;

    if(numerator_str.size() < max_size)
        for(size_t i = 0; i < max_size - numerator_str.size(); ++i)
            result.push_back(kWhiteSpace);
    result += numerator_str;
    result.push_back('\n');

    for(size_t i = 0; i < max_size; ++i)
        result.push_back(kDelimiter);
    result.push_back('\n');

    if(denominator_str.size() < max_size)
        for(size_t i = 0; i < max_size - denominator_str.size(); ++i)
            result.push_back(kWhiteSpace);
    result += denominator_str;
    
    return result;
}

MRationalNumber& MRationalNumber::operator=(const MRationalNumber &rhs){
    if(this == &rhs)
        return *this;
    
    numerator = rhs.numerator;
    denominator = rhs.denominator;

    return *this;
}

bool MRationalNumber::operator==(const MRationalNumber &rhs) const{
    return
        numerator == rhs.numerator &&
        denominator == rhs.denominator;
}

MRationalNumber MRationalNumber::operator*(const MRationalNumber &rhs) const{
    MRationalNumber result(*this);

    result.numerator *= rhs.numerator;
    result.denominator *= rhs.denominator;

    return result.reduce();
}

MRationalNumber MRationalNumber::operator/(const MRationalNumber &rhs) const{
    if(rhs == 0)
        throw DivisionByZero();
    
    MRationalNumber result(*this);

    result.numerator *= rhs.denominator;
    result.denominator *= rhs.numerator;

    return result.reduce();
}

MRationalNumber MRationalNumber::operator+(const MRationalNumber &rhs) const{
    MRationalNumber result;

    MBigInt rhsNumerator;

    leastCommonDenominator(
        *this,
        rhs,
        &result.denominator,
        nullptr,
        &result.numerator,
        &rhsNumerator
    );

    result.numerator += rhsNumerator;

    return result.reduce();
}

MRationalNumber MRationalNumber::operator-(const MRationalNumber &rhs) const{
    MRationalNumber result;

    MBigInt rhsNumerator;

    leastCommonDenominator(
        *this,
        rhs,
        &result.denominator,
        nullptr,
        &result.numerator,
        &rhsNumerator
    );

    result.numerator -= rhsNumerator;

    return result.reduce();
}

MRationalNumber MRationalNumber::operator-() const{
    MRationalNumber result(*this);

    result.numerator *= -1;

    return result;
}

MRationalNumber& MRationalNumber::operator++(){
    operator+=(1);
    return *this;
}

MRationalNumber& MRationalNumber::operator--(){
    operator-=(1);
    return *this;
}

MRationalNumber MRationalNumber::operator++(int){
    MRationalNumber result(*this);
    ++(*this);
    return result;
}

MRationalNumber MRationalNumber::operator--(int){
    MRationalNumber result(*this);
    --(*this);
    return result;
}

bool MRationalNumber::operator>(const MRationalNumber &rhs) const{
    MBigInt
        lhsNumerator,
        rhsNumerator;
    
    leastCommonDenominator(
        *this,
        rhs,
        nullptr,
        nullptr,
        &lhsNumerator,
        &rhsNumerator
    );

    return lhsNumerator > rhsNumerator;
}