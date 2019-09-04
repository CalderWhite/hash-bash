#pragma once

#include <string>
#include <stdint.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "CountTree.h"
#include "BigTree.h"

/**
 * Stores sorted arrays of chars in order of most probable to least.
 * The sub-arrays of each are still indexed via the char's integer value (minus the ascii start).
 * char() - m_ascii_start. However, each sub array is then sorted.
 */
class Predictor : public BigTree<char> {
public:
    Predictor(int64_t ss, int64_t bs, char as = ' ');

    /**
     * Builds a predictor from a CountTree. The CountTree parameter is deliberately copied 
     * as the sorting algorithm is in place and changes the values of the CountTree.
     */
    void genFromCountTree(CountTree p);

    /**
     * Serialization helper function. For more extensibility,
     * the user can do the boost serialization of the class themselves.
     */
    void serializeToFile(std::string filename) const;

    void deserializeFromFile(std::string filename);

    /**
     * Returns the sequence of chars after the increasing string of indicies, p.
     *
     * Example:
     * The Predictor has node + nope + nail in its count table.
     * The indicies for each letter go as follows
     * n: 0 --> o: 0 --> d: 0 --> e: 0
     * |        |
     * |        +--> p: 1 --> e: 0
     * |
     * +--> a: 1 --> i: 0 --> l: 0
     *
     * Notice that 'o' comes before 'a', due to the higher number of occurances of 'o' after 'n' is the first letter.
     *
     * The most probable char is always at the lowest index. The indicies are also dependant
     * on the characters that come before them, similar to a Trie.
     *
     * @param p The list of indicies to get. 0: Most probable. m_char_set_size-1: Least probable.
     * @param n How many characters you wish to get. Max of m_block_size.
     * @param out The array to put the retrieved characters in.
     */
    void getChars(int64_t* p, int n, char* out) const;

    /**
     * Finds the position of the final array via the chain in a.
     * Then returns last_index of that array.
     */
    char getNextChar(char* a, int last_index) const;

private:
    friend class boost::serialization::access;

    /**
     * Since this is a template function, this had to go in the header.
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_char_set_size;
        ar & m_block_size;
        ar & m_ascii_start;

        for (int i=0; i<m_block_size; i++) {
            ar & boost::serialization::make_array(m_count_table[i], getCountLength(i));
        }

        ar & boost::serialization::make_array(m_powers, m_block_size+1);
    }
};
