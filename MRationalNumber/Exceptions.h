#ifndef M_RATIONAL_NUMBER_EXCEPTIONS_H_
#define M_RATIONAL_NUMBER_EXCEPTIONS_H_

#include <exception>

namespace ArbitraryPrecisionArithmetic{
    class ZeroDenominator : public std::exception{
    public:
        const char* what() const throw(){
            return "Denominator cannot be zero";
        } 
    };
}

#endif