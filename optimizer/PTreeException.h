#pragma once

#include <iostream>
#include <exception>

/**
 * Custom exceptions to improve error catching/info.
 */
class PTreeException: public std::runtime_error {
public:
    PTreeException(const char* msg) : std::runtime_error(msg){}
};
