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

        inline const digitContainer& getReversedDigits() const{
            return reversedDigits_;
        }

        operator std::string() const;

    private:
        inline bool isZero() const{
            return reversedDigits_.size() == 1 && reversedDigits_.at(0) == 0;
        }
        inline bool isPositive() const{
            return !sign_;
        }
        inline bool isNegative() const{
            return sign_;
        }

        bool sign_; // 0 - positive, 1 - negative
        digitContainer reversedDigits_;
    };

    inline std::ostream& operator<<(std::ostream &strm, const MBigInt &instance){
        return strm << static_cast<std::string>(instance);
    }
}

#endif