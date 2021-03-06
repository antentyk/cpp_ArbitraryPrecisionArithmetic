#ifndef M_BIG_INT_EXCEPTIONS_H_
#define M_BIG_INT_EXCEPTIONS_H_

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

    class OperatorError : public std::exception{
    public:
        const char * what() const throw(){
            return "Error while applying operand";
        }
    };

    class DivisionByZero : public std::exception{
    public:
        const char * what() const throw(){
            return "Division by zero";
        }
    };

    class PowerError : public std::exception{
    public:
        const char * what() const throw(){
            return "Only non-negative powers are allowed";
        }
    };

    class GCDError : public std::exception{
    public:
        const char* what() const throw(){
            return "Number cannot be negative";
        }
    };

    class LCMError : public std::exception{
    public:
        const char* what() const throw(){
            return "Number cannot be negative";
        }
    };
}

#endif