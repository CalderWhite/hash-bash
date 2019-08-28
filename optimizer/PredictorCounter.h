#pragma once

#include <stdint.h>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

#include "Predictor.h"

namespace mp = boost::multiprecision;

class PredictorCounter {
public:
    PredictorCounter(const Predictor& predictor, int guess_length, int increment);

    void getNext(char* out);
    void genAll();

    /**
     * s must have a length of m_guess_length.
     * Returns how many other generations will be created before s is found.
     */
    mp::int128_t getOffset(const char* s);

private:
    Predictor m_predictor;
    int m_guess_length;
    int m_increment;
    mp::int128_t m_count;
    std::vector<mp::int128_t> m_powers;

    int getSubOffset(const char* s, int l);
};
