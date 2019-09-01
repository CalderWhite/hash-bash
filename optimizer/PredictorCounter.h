#pragma once

#include <stdint.h>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

#include "Predictor.h"

namespace mp = boost::multiprecision;

/**
 * Contains helpful methods for operating on the Predictor.
 * Can also be used to keep info on the current combination being tried in the scenario of one attempting to 
 * guess a certain combination of characters using a Predictor.
 */
class PredictorCounter {
public:
    PredictorCounter(const Predictor& predictor, int guess_length, int increment);

    /**
     * Returns the next most-probable combination of m_guess_length.
     * These are not back-to-back, as they are m_increment apart.
     */
    void getNext(char* out);

    /**
     * s must have a length of m_guess_length.
     * Returns how many other generations will be created before s is found.
     */
    mp::int128_t getOffset(const char* s);

    /**
     * Return the naive offset of s if it was brute forced in the order of ascii,
     * starting at the predictor's m_ascii_start.
     */
    mp::int128_t getBadOffset(const char* s);

private:
    const Predictor& m_predictor;
    int m_guess_length;

    // the gaps between guesses for getNext.
    int m_increment;

    // the current index from 0 (most probable) to m_predictor.m_char_set_size^m_guess_length (least probable).
    mp::int128_t m_count;

    // avoid calculating the powers millions of times over.
    std::vector<mp::int128_t> m_powers;

    /**
     * Return the offset of s in its sub-array in the Predictor.
     * This method is meant for strings of length predictor.m_block_size or less.
     */
    int getSubOffset(const char* s, int l);
};
