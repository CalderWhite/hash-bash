#include <stdint.h>

#include <boost/multiprecision/cpp_int.hpp>

#include "PredictorCounter.h"

namespace mp = boost::multiprecision;

PredictorCounter::PredictorCounter(const Predictor& p, int gl, int inc)
    : m_predictor(p), m_guess_length(gl), m_increment(inc), m_count(0) {
    m_powers.reserve(m_guess_length+1);
    for (int i=0; i<m_guess_length+1; i++) {
        m_powers[i] = mp::pow(mp::int128_t(m_predictor.getCharSetSize()), i);
    }
}

void PredictorCounter::getNext(char* out) {
    int64_t parts[m_guess_length] = {0};

    for (int i=0; i<m_guess_length; i++) {
        mp::int128_t temp = m_count % m_powers[m_guess_length-i];
        temp /= m_powers[m_guess_length-i-1];
        parts[i] = static_cast<int64_t>(temp);
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


void PredictorCounter::genAll() {
    char o[7] = {0};
    while (m_count < m_powers[m_guess_length]) {
        getNext(o);
        std::cout << o << "\n";
    }
}

mp::int128_t PredictorCounter::getOffset(const char* s) {
    mp::int128_t offset = 0;

    int block_size = m_predictor.getBlockSize();

    for (int i=0; i<block_size; i++) {
        offset += getSubOffset(s, i) * m_powers[m_guess_length - i - 1];
    }

    for (int i=block_size; i<m_guess_length; i++) {
        offset += getSubOffset(&s[1+i-block_size], block_size-1) * m_powers[m_guess_length - i - 1];
    }

    return offset;
}

int PredictorCounter::getSubOffset(const char* s, int last_index) {
    // get the offset of the array the last char is in.
    int64_t start = 0;
    for (int i=0; i<last_index; i++) {
        start += (s[i] - m_predictor.getAsciiStart()) * m_predictor.getCountBlockSize(last_index - i);
    }

    for (int i=0; i<m_predictor.getCharSetSize(); i++) {
        if (m_predictor.at(last_index, start + i) == s[last_index]) {
            return i;
        }
    }

    // TODO: Better error handling here.
    return -1;
}
