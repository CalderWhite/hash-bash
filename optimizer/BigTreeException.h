#pragma once

#include <iostream>
#include <exception>

/**
 * Custom exceptions to improve error catching/info.
 */
class BigTreeException: public std::runtime_error {
public:
    BigTreeException(const char* msg) : std::runtime_error(msg){}
};
