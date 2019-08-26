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

private:
    Predictor m_predictor;

    int m_guess_length;
    int m_increment;
    mp::int128_t m_count;
    std::vector<mp::int128_t> m_powers;
};
