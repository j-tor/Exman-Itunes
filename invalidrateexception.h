#ifndef INVALIDRATEEXCEPTION_H
#define INVALIDRATEEXCEPTION_H

#include <stdexcept>
#include <string>


class InvalidRateException : public std::runtime_error {
public:
    InvalidRateException(int rate) : std::runtime_error("RATE " + std::to_string(rate) + " no es un numero valido") {}

};

#endif // INVALIDRATEEXCEPTION_H
