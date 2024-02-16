#ifndef INVALIDRATEEXCEPTION_H
#define INVALIDRATEEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;
class InvalidRateException : public std::runtime_error {
public:
    InvalidRateException(int invalidRate)
        : std::runtime_error("RATE " + std::to_string(invalidRate) + " is not a valid number for a review") {}

    virtual ~InvalidRateException() noexcept {}
};

#endif // INVALIDRATEEXCEPTION_H
