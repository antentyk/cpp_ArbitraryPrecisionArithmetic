#include <sstream>
#include <algorithm>

#include "MBigInt.h"

using namespace ArbitraryPrecisionArithmetic;
using std::string;
using std::to_string;
using std::ostream;
using std::istream;
using std::stringstream;
using std::reverse;

namespace
{
    int raw_cmp(const digitContainer &lhs, const digitContainer &rhs){
        // compares unsigned MBigInt digits representations
        // -1 lhs < rhs
        // 0 lhs == rhs
        // 1 lhs > rhs

        if(lhs.size() > rhs.size())
            return 1;
        if(lhs.size() < rhs.size())
            return -1;

        auto lhs_itr = lhs.rbegin(), rhs_itr = rhs.rbegin();

        for
        (
            ;
            lhs_itr != lhs.rend() && rhs_itr != rhs.rend() && *lhs_itr == *rhs_itr;
            ++lhs_itr, ++rhs_itr
        );

        if(lhs_itr == lhs.rend() && rhs_itr == rhs.rend())
            return 0;
        if(*lhs_itr < *rhs_itr)
            return -1;
        if(*lhs_itr > *rhs_itr)
            return 1;
        
        throw ComparisonError();
    }

    int digitsnum(digit number){
        // returns amount of digits in number (needed to put leading zeros)
        // in string representation of MBigInt
        if(number == 0)
            return 1;
        
        int result = 0;
        while(number > 0){
            ++result;
            number /= 10;
        }

        return result;
    }

    void raw_add
    (
        const digitContainer &lhs,
        const digitContainer &rhs,
        digitContainer &target
    )
    {
        // performs addition of unsigned MBigInt representations
        // target can be one of lhs or rhs
        // (in that case it will be replaced by new digits)
        digit memory = 0;

        size_t
            index = 0,
            lhs_index = 0,
            rhs_index = 0;
        
        while
        (
            index < target.size() &&
            lhs_index < lhs.size() &&
            rhs_index < rhs.size()
        )
        {
            digit current = lhs.at(lhs_index++) + rhs.at(rhs_index++) + memory;
            target.at(index++) = current % MBigInt::kBase;
            memory = current / MBigInt::kBase;
        }

        while(index < target.size() && lhs_index < lhs.size()){
            digit current = lhs.at(lhs_index++) + memory;
            target.at(index++) = current % MBigInt::kBase;
            memory = current / MBigInt::kBase;
        }

        while(index < target.size() && rhs_index < rhs.size()){
            digit current = rhs.at(rhs_index++) + memory;
            target.at(index++) = current % MBigInt::kBase;
            memory = current / MBigInt::kBase;
        }

        while
        (
            lhs_index < lhs.size() &&
            rhs_index < rhs.size()
        )
        {
            digit current = lhs.at(lhs_index++) + rhs.at(rhs_index++) + memory;
            target.push_back(current % MBigInt::kBase);
            memory = current / MBigInt::kBase;
        }

        while(lhs_index < lhs.size()){
            digit current = lhs.at(lhs_index++) + memory;
            target.push_back(current % MBigInt::kBase);
            memory = current / MBigInt::kBase;
        }

        while(rhs_index < rhs.size()){
            digit current = rhs.at(rhs_index++) + memory;
            target.push_back(current % MBigInt::kBase);
            memory = current / MBigInt::kBase;
        }

        if(memory != 0)
            target.push_back(memory);
    }

    void raw_subtract
    (
        const digitContainer &lhs,
        const digitContainer &rhs,
        digitContainer &target
    )
    {
        // performs subtraction of unsigned MBigInt representations
        // target can be one of lhs or rhs
        // (in that case it will be replaced by new digits)

        // digit represented by lhs should be greater than
        // in rhs
        // otherwise the behaviour is underfined

        bool carriage = false;

        size_t
            index = 0,
            lhs_index = 0,
            rhs_index = 0;
        
        while
        (
            index < target.size() &&
            lhs_index < lhs.size() &&
            rhs_index < rhs.size()
        )
        {
            digit current = lhs.at(lhs_index++) - carriage - rhs.at(rhs_index++);
            carriage = current < 0;
            if(current < 0)
                current += MBigInt::kBase;
            
            target.at(index++) = current;
        }

        while
        (
            index < target.size() &&
            lhs_index < lhs.size()
        )
        {
            digit current = lhs.at(lhs_index++) - carriage;
            carriage = current < 0;
            if(current < 0)
                current += MBigInt::kBase;
            
            target.at(index++) = current;
        }

        while(lhs_index < lhs.size() && rhs_index < rhs.size()){
            digit current = lhs.at(lhs_index++) - carriage - rhs.at(rhs_index++);
            carriage = current < 0;
            if(current < 0)
                current += MBigInt::kBase;
            
            target.push_back(current);
        }

        while(lhs_index < lhs.size()){
            digit current = lhs.at(lhs_index++) - carriage;
            carriage = current < 0;
            if(current < 0)
                current += MBigInt::kBase;
            
            target.push_back(current);
        }

        while(target.size() > 1 && target.back() == 0)
            target.pop_back();
    }
}

MBigInt::MBigInt(string representation){
    // throws FormatError
    //      if representation is empty
    //      if there are no digits characters
    //      if there are leading zeros
    // throws InvalidCharacter
    //      if there is non-digit character
    //          (apart from + or - in the beginning)
    sign_ = false;

    if(representation.size() == 0)
        throw FormatError();

    if(representation.at(0) == '-')
        sign_ = true;

    if
    (
        representation.at(0) == '-' || 
        representation.at(0) == '+'
    )
        representation = representation.substr(1);
    
    auto start = representation.rbegin();
    auto end = representation.rend();

    if(representation.size() == 0)
        throw FormatError();
    
    if(representation == "0"){
        reversedDigits_.push_back(0);
        return;
    }

    if
    (
        representation.size() > 1 &&
        representation.substr(0, 2) == "00"
    )
        throw FormatError();

    digit
        currently_taken = 0,
        current_number = 0,
        current_power = 1;

    for(; start != end; ++start){
        if(!isdigit(*start))
            throw InvalidCharacter();
        
        digit current_digit = *start - '0';

        current_number += current_power * current_digit;

        current_power *= kRepresentationBase;
        ++currently_taken;

        if(currently_taken == kBaseDegree){
            reversedDigits_.push_back(current_number);
            currently_taken = 0;
            current_number = 0;
            current_power = 1;
        }
    }

    if(current_number != 0)
        reversedDigits_.push_back(current_number);
}

MBigInt::MBigInt(int number):
MBigInt(to_string(number))
{}

MBigInt::MBigInt(digit number):
MBigInt(to_string(number))
{}

MBigInt::MBigInt(const MBigInt &other):
    sign_(other.sign_),
    reversedDigits_(other.reversedDigits_)
{}

MBigInt::MBigInt():
MBigInt(0)
{}

MBigInt& MBigInt::operator=(const MBigInt &rhs){
    if(this == &rhs)
        return *this;

    sign_ = rhs.sign_;
    reversedDigits_ = rhs.reversedDigits_;

    return *this;
}

bool MBigInt::operator==(const MBigInt &rhs) const{
    if(isZero() && rhs.isZero())
        return true;
    if(isZero() || rhs.isZero())
        return false;
    
    return
        sign_ == rhs.sign_ &&
        reversedDigits_ == rhs.reversedDigits_;
}

bool MBigInt::operator>(const MBigInt &rhs) const{
    if(operator==(rhs))
        return false;
    
    if(isZero())
        return rhs.isNegative();
    if(rhs.isZero())
        return isPositive();
    
    if(isPositive() && rhs.isNegative())
        return true;
    if(isNegative() && rhs.isPositive())
        return false;
    
    int result = raw_cmp(reversedDigits_, rhs.reversedDigits_);

    if(isPositive())
        return result == 1;
    if(isNegative())
        return result == -1;
    
    throw ComparisonError();
}

MBigInt& MBigInt::operator+=(const MBigInt &rhs){
    if(sign_ == rhs.sign_){
        raw_add(reversedDigits_, rhs.reversedDigits_, reversedDigits_);
        return *this;
    }

    if(operator>=(0) && rhs <= 0){
        if(raw_cmp(reversedDigits_, rhs.reversedDigits_) >= 0)
            raw_subtract(reversedDigits_, rhs.reversedDigits_, reversedDigits_);
        else{
            sign_ ^= 1;
            raw_subtract(rhs.reversedDigits_, reversedDigits_, reversedDigits_);
        }

        return *this;
    }
    
    if(operator<=(0) && rhs >= 0){
        sign_ ^= 1;
        operator-=(rhs);
        sign_ ^= 1;
        return *this;
    }

    throw OperatorError();
}

MBigInt& MBigInt::operator-=(const MBigInt &rhs){
    if(sign_ == rhs.sign_){
        if(raw_cmp(reversedDigits_, rhs.reversedDigits_) >= 0)
            raw_subtract(reversedDigits_, rhs.reversedDigits_, reversedDigits_);
        else{
            raw_subtract(rhs.reversedDigits_, reversedDigits_, reversedDigits_);
            sign_ ^= 1;
        }
        
        return *this;
    }

    if(operator<=(0) && rhs >= 0){
        raw_add(reversedDigits_, rhs.reversedDigits_, reversedDigits_);
        return *this;
    }

    if(operator>=(0) && rhs <= 0){
        raw_add(reversedDigits_, rhs.reversedDigits_, reversedDigits_);
        return *this;
    }

    throw OperatorError();
}

MBigInt::operator string() const{
    stringstream strm;

    if(operator<(0))
        strm << "-";
    
    auto itr = reversedDigits_.rbegin();
    strm << *(itr++);

    for(;itr != reversedDigits_.rend(); ++itr){
        for(int i = 0; i < MBigInt::kBaseDegree - digitsnum(*itr); ++i)
            strm << "0";
        
        strm << *itr;
    }

    return strm.str();
}

MBigInt::MBigInt(bool sign, digitContainer reversedDigits):
    sign_(sign)
{
    if(reversedDigits.size() == 0)
        throw FormatError();

    while(reversedDigits.size() > 1 && reversedDigits.back() == 0)
        reversedDigits.pop_back();

    reversedDigits_ = reversedDigits;
}

MBigInt MBigInt::operator*(const MBigInt &rhs) const{
    MBigInt result = 0;

    size_t shift = 0;

    for(auto lhs_digit: reversedDigits_){
        ++shift;

        if(lhs_digit == 0)
            continue;

        digitContainer tmpContainer;

        tmpContainer.resize(shift - 1, 0);
        
        digit memory = 0;
        digit current = 0;

        for(auto rhs_digit: rhs.getReversedDigits()){
            current = memory + rhs_digit * lhs_digit;
            tmpContainer.push_back(current % kBase);
            memory = current / kBase;
        }

        if(memory > 0)
            tmpContainer.push_back(memory);
        
        result += MBigInt(false, tmpContainer);
    }

    result.sign_ = sign_ ^ rhs.sign_;
    return result;
}

MBigInt MBigInt::operator/(const MBigInt &rhs) const{
    const MBigInt &l = operator<(0) ? operator-() : *this;
    const MBigInt &r = (rhs < 0) ? -rhs : rhs;

    if(r == 0)
        throw DivisionByZero();
    
    if(l == 0)
        return 0;
    
    digitContainer fractionDigits;

    MBigInt remainder = 0;

    for
    (
        auto itr = l.reversedDigits_.rbegin();
        itr != l.reversedDigits_.rend();
        ++itr
    )
    {
        digit current_digit = *itr;

        remainder = remainder * kBase + current_digit;

        if(remainder < r){
            fractionDigits.push_back(0);
            continue;
        }

        digit lower = 0, upper = kBase - 1;

        while(upper - lower > 1){
            digit middle = (lower + upper) / 2;
            if(r * middle > remainder)
                upper = middle;
            else
                lower = middle;
        }

        if(r * upper <= remainder){
            fractionDigits.push_back(upper);
            remainder -= r * upper;
            continue;
        }
        fractionDigits.push_back(lower);
        remainder -= r * lower;
    }

    reverse(fractionDigits.begin(), fractionDigits.end());
    MBigInt result(sign_ ^ rhs.sign_, fractionDigits);

    if(sign_ ^ rhs.sign_ && remainder > 0)
        result -= 1;

    return result;
}

MBigInt& MBigInt::operator++(){
    operator+=(1);
    return *this;
}

MBigInt& MBigInt::operator--(){
    operator-=(1);
    return *this;
}

MBigInt MBigInt::operator++(int){
    MBigInt result(*this);
    ++(*this);
    return result;
}

MBigInt MBigInt::operator--(int){
    MBigInt result(*this);
    --(*this);
    return result;
}

MBigInt ArbitraryPrecisionArithmetic::pow
(
    const MBigInt &number,
    const MBigInt &power
)
{
    if(power < 0)
        throw PowerError();
    
    MBigInt a(number);
    MBigInt n(power);

    MBigInt result = 1;

    while(n > 0){
        if(n.getReversedDigits().front() % 2 == 1){
            result *= a;
            --n;
        }
        else{
            a *= a;
            n /= 2;
        }
    }

    return result;
}

MBigInt ArbitraryPrecisionArithmetic::GCD
(
    const MBigInt &lhs,
    const MBigInt &rhs
)
{
    if(lhs < 0 || rhs < 0)
        throw GCDError();
    
    if(rhs == 0)
        return lhs;
    
    return GCD(rhs, lhs % rhs);
}

MBigInt ArbitraryPrecisionArithmetic::LCM
(
    const MBigInt &lhs,
    const MBigInt &rhs
)
{
    if(lhs < 0 || rhs < 0)
        throw LCMError();
    if(lhs == 0 && rhs == 0)
        throw LCMError();
        
    return (lhs / GCD(lhs, rhs)) * rhs;
}

istream& ArbitraryPrecisionArithmetic::operator>>(
    istream& strm,
    MBigInt& instance
)
{
    string representation;
    strm >> representation;

    instance = MBigInt(representation);

    return strm;
}