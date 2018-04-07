#include "MBigInt.h"

using namespace ArbitraryPrecisionArithmetic;
using std::vector;
using std::string;
using std::stringstream;
using std::ostream;

typedef unsigned long long ull;
typedef unsigned int ui;

MBigInt::MBigInt():
    isPositive(true)
{
    reversedDigits.clear();
    reversedDigits.push_back(0);
    fillRepresentation();
}

MBigInt::MBigInt(const MBigInt &other):
    reversedDigits(other.reversedDigits),
    isPositive(other.isPositive),
    representation(other.representation)
{}

MBigInt& MBigInt::operator=(const MBigInt &other){
    if(&other == this)
        return *this;
    
    reversedDigits = other.reversedDigits;
    isPositive = other.isPositive;
    representation = other.representation;

    return *this;
}

MBigInt::MBigInt(string representation){
    isPositive = true;

    if(representation.size() == 0)
        throw EmptyString();
    
    auto start = representation.rbegin();
    auto end = representation.rend();

    if
    (
        representation.at(0) == '-' || 
        representation.at(0) == '+'
    )
        --end;
    
    if(representation.at(0) == '-')
        isPositive=false;
    
    ull currently_taken = 0;
    ull current_number = 0;
    ull current_power = 1;

    for(; start != end; ++start){
        if(!isdigit(*start))
            throw InvalidCharacter();
        
        ui digit = *start - '0';

        current_number += current_power * digit;

        current_power *= kRepresentationBase;
        ++currently_taken;

        if(currently_taken == kBaseDegree){
            reversedDigits.push_back(current_number);
            current_power = 1;
            currently_taken = 0;
            current_number = 0;
        }
    }

    if(current_number != 0)
        reversedDigits.push_back(current_number);

    fillRepresentation();
}

void MBigInt::fillRepresentation(){
    stringstream strm; 

    if(!isPositive)
        strm << '-';
    
    for(auto itr = reversedDigits.rbegin(); itr != reversedDigits.rend(); ++itr)
        strm << *itr;
    
    representation = strm.str();
}

string MBigInt::getRepresentation() const{
    return representation;
}

ostream& ArbitraryPrecisionArithmetic::operator<<(
    ostream &strm,
    const MBigInt &instance
)
{
    strm << instance.getRepresentation();
    return strm;
}