#ifndef M_BIG_INT_H_
#define M_BIG_INT_H_

#include <string>
#include <vector>
#include <ostream>
#include <sstream>
#include <algorithm>

#include "Exceptions.h"

typedef long long digit;
typedef std::vector<digit> digitContainer;

namespace ArbitraryPrecisionArithmetic{
    class MBigInt{
    public:
        static const digit kBaseDegree = 8;
        static const digit kBase = 1e8;
        static const digit kRepresentationBase = 10;

        explicit MBigInt(std::string representation);
        MBigInt(int number);
        MBigInt(const MBigInt &other);

        MBigInt& operator=(const MBigInt &rhs);

        inline MBigInt operator-() const{
            return MBigInt(sign_ ^ 1, reversedDigits_);
        }
        inline MBigInt operator+() const{
            return MBigInt(*this);
        }

        bool operator==(const MBigInt &rhs) const;
        inline bool operator!=(const MBigInt &rhs) const{
            return !(operator==(rhs));
        }

        bool operator>(const MBigInt &rhs) const;
        inline bool operator>=(const MBigInt &rhs) const{
            return operator==(rhs) || operator>(rhs);
        }
        inline bool operator<(const MBigInt &rhs) const{
            return !operator==(rhs) && !operator>(rhs);
        }
        inline bool operator<=(const MBigInt &rhs) const{
            return !operator>(rhs);
        }

        MBigInt& operator+=(const MBigInt &rhs);
        MBigInt& operator-=(const MBigInt &rhs);
        inline MBigInt& operator*=(const MBigInt &rhs){
            return operator=(operator*(rhs));
        }
        inline MBigInt& operator/=(const MBigInt &rhs){
            return operator=(operator/(rhs));
        }
        inline MBigInt& operator%=(const MBigInt &rhs){
            return operator=(operator%(rhs));
        }

        operator std::string() const;

        inline MBigInt operator+(const MBigInt &rhs) const{
            MBigInt result(*this);
            result += rhs;
            return result;
        }
        inline MBigInt operator-(const MBigInt &rhs) const{
            MBigInt result(*this);
            result -= rhs;
            return result;
        }
        MBigInt operator*(const MBigInt &rhs) const;
        MBigInt operator/(const MBigInt &rhs) const;
        inline MBigInt operator%(const MBigInt &rhs) const{
            // very inefficient
            return operator-(operator/(rhs) * rhs);
        }

        MBigInt& operator++();
        MBigInt& operator--();

        MBigInt operator++(int);
        MBigInt operator--(int);

        inline const digitContainer& getReversedDigits() const{
            return reversedDigits_;
        }

    private:
        MBigInt(bool sign, digitContainer reversedDigits);
        MBigInt(digit number);

        inline bool isZero() const{
            return reversedDigits_.size() == 1 && reversedDigits_.at(0) == 0;
        }
        inline bool isPositive() const{
            return !sign_;
        }
        inline bool isNegative() const{
            return sign_;
        }

        bool sign_; // false - positive, true - negative
        digitContainer reversedDigits_;
    };

    inline std::ostream& operator<<(std::ostream &strm, const MBigInt &instance){
        return strm << static_cast<std::string>(instance);
    }

    // only for non-negative powers
    MBigInt pow(const MBigInt &number, const MBigInt &power);

    inline MBigInt abs(const MBigInt &number){
        return (number < 0? -number : number);
    }
}

#endif