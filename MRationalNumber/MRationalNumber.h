#ifndef M_RATIONAL_NUMBER_H_
#define M_RATIONAL_NUMBER_H_

#include <string>
#include <ostream>
#include <algorithm>
#include <vector>

#include "Exceptions.h"
#include "../MBigInt/MBigInt.h"

namespace ArbitraryPrecisionArithmetic{
    class MRationalNumber{
    public:
        MRationalNumber(const MBigInt &numerator, const MBigInt &denominator);
        MRationalNumber(int numerator, int denominator);
        MRationalNumber(const MBigInt &numerator);
        MRationalNumber(int numerator);
        MRationalNumber();
        MRationalNumber(const MRationalNumber &other);

        operator std::string() const;

        MRationalNumber& operator=(const MRationalNumber &rhs);

        bool operator==(const MRationalNumber &rhs) const;
        inline bool operator!=(const MRationalNumber &rhs) const{
            return !operator==(rhs);
        }

        MRationalNumber operator*(const MRationalNumber &rhs) const;
        MRationalNumber operator/(const MRationalNumber &rhs) const;
        MRationalNumber operator+(const MRationalNumber &rhs) const;
        MRationalNumber operator-(const MRationalNumber &rhs) const;

        inline MRationalNumber operator+() const{
            return MRationalNumber(*this);
        }
        MRationalNumber operator-() const;

        inline MRationalNumber& operator*=(const MRationalNumber &rhs){
            return operator=(operator*=(rhs));
        };
        inline MRationalNumber& operator/=(const MRationalNumber &rhs){
            return operator=(operator/(rhs));
        }
        inline MRationalNumber& operator+=(const MRationalNumber &rhs){
            return operator=(operator+(rhs));
        }
        inline MRationalNumber& operator-=(const MRationalNumber &rhs){
            return operator=(operator-(rhs));
        }

        MRationalNumber& operator++();
        MRationalNumber& operator--();

        MRationalNumber operator++(int);
        MRationalNumber operator--(int);

        bool operator>(const MRationalNumber &rhs) const;
        inline bool operator>=(const MRationalNumber &rhs) const{
            return operator>(rhs) || operator==(rhs);
        }
        inline bool operator<(const MRationalNumber &rhs) const{
            return !operator>=(rhs);
        }
        inline bool operator<=(const MRationalNumber &rhs) const{
            return operator>(rhs) || operator==(rhs);
        }

        inline const MBigInt& getNumerator() const{
            return numerator;
        }
        inline const MBigInt& getDenominetor() const{
            return denominator;
        }

    private:
        static const char
            kDelimiter = '-',
            kWhiteSpace = ' ';

        static void leastCommonDenominator(
            const MRationalNumber &lhs,
            const MRationalNumber &rhs,
            MBigInt * newLhsDenominator,
            MBigInt * newRhsDenominator,
            MBigInt * newLhsNumerator,
            MBigInt * newRhsNumerator
        );

        MRationalNumber& reduce();

        MBigInt
            numerator,
            denominator;
    };

    inline std::ostream& operator<<
    (
        std::ostream &strm,
        const MRationalNumber &instance
    )
    {
        return strm << static_cast<std::string>(instance);
    }

    // only for non-negative power
    inline MRationalNumber pow(const MRationalNumber &number, const MBigInt &power){
        return MRationalNumber(
            pow(number.getNumerator(), power),
            pow(number.getDenominetor(), power)
        );
    }

    inline MRationalNumber abs(const MRationalNumber &rhs){
        return rhs < 0 ? -rhs : rhs;
    }
};

#endif