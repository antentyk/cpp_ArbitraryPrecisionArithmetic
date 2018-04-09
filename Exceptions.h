#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>

namespace ArbitraryPrecisionArithmetic{
    class InvalidCharacter : public std::exception{
    public:
        const char* what() const throw(){
            return "Invalid character detected";
        }
    };

    class ComparisonError : public std::exception{
    public:
        const char * what() const throw(){
            return "Error in comparison";
        }
    };

    class FormatError : public std::exception{
    public:
    const char * what() const throw(){
        return "Wrong number format";
    }
    };
}

#endif