#ifndef M_BIG_INT_H_
#define M_BIG_INT_H_

#include <string>
#include <vector>
#include <ostream>
#include <sstream>

#include "Exceptions.h"

namespace ArbitraryPrecisionArithmetic{
    class MBigInt{
    public:
        MBigInt();
        MBigInt(std::string representation);
        MBigInt(const MBigInt &other);

        MBigInt& operator=(const MBigInt &other);

        std::string getRepresentation() const;
    private:
        static const unsigned long long kBaseDegree = 8;
        static const unsigned int kRepresentationBase = 1e8;

        static const unsigned int kSourceBase = 10;

        std::vector<unsigned long long> reversedDigits;
        bool isPositive;

        std::string representation;
        void fillRepresentation();
    };

    std::ostream& operator<<(std::ostream &strm, const MBigInt &instance);
}

#endif