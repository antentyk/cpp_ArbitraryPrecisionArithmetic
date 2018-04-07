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

    class EmptyString : public std::exception{
    public:
        const char * what() const throw(){
            return "Representation string is empty";
        }
    };
}

#endif