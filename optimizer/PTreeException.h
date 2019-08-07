#pragma once

#include <iostream>
#include <exception>

class PTreeException: public std::runtime_error {
public:
    PTreeException(const char* msg) : std::runtime_error(msg){}
};
