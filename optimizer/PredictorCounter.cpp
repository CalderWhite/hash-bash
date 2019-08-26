#include <stdint.h>

#include <boost/multiprecision/cpp_int.hpp>

#include "PredictorCounter.h"

namespace mp = boost::multiprecision;

PredictorCounter::PredictorCounter(const Predictor& p, int gl, int inc)
    : m_predictor(p), m_guess_length(gl), m_increment(inc), m_count(0) {

    m_powers.reserve(m_guess_length);
    for (int i=0; i<m_guess_length; i++) {
        m_powers[i] = mp::pow(mp::int128_t(m_predictor.getCharSetSize()), i+1);
    }
}

void PredictorCounter::getNext(char* out) {
    int64_t parts[m_guess_length] = {0};

    for (int i=0; i<m_guess_length; i++) {
        parts[i] = static_cast<int64_t>(m_count / m_powers[m_guess_length-i-1]);
    }

    int block_size = m_predictor.getBlockSize();

    if (m_guess_length > block_size) {
        m_predictor.getChars(parts, block_size, out);

        for (int i=block_size; i<m_guess_length; i++) {
            char c = m_predictor.getNextChar(&out[i-block_size+1], parts[i]);
            out[i] = c;
        }
    } else {
        m_predictor.getChars(parts, m_guess_length, out);
    }

    m_count += m_increment;
}
