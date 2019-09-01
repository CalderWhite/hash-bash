#pragma once

#include <iostream>
#include <exception>

/**
 * Custom exceptions to improve error catching/info.
 */
class CountTreeException: public std::runtime_error {
public:
    CountTreeException(const char* msg) : std::runtime_error(msg){}
};
