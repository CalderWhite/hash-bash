#pragma once

#include <iostream>
#include <exception>

class BigTreeException: public std::runtime_error {
public:
    BigTreeException(const char* msg) : std::runtime_error(msg){}
};
