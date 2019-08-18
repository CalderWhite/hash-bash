#pragma once

#include <string>
#include <stdint.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "PTree.h"
#include "BigTree.h"

class Predictor : public BigTree<char> {
public:
    Predictor(int64_t ss, int64_t bs);

    void genFromPTree(PTree p);

    /**
     * Serialization helper function. For more extensibility,
     * the user can do the boost serialization of the class themselves.
     */
    void serializeToFile(std::string filename);

    void deserializeFromFile(std::string filename);

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
