#include <stdint.h>
#include <fstream>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include "PTree.h"
#include "Predictor.h"
#include "utils.h"

Predictor::Predictor(int64_t ss, int64_t bs) : BigTree(ss, bs) {}

void Predictor::genFromPTree(PTree p) {
    int index_tracker[m_char_set_size] = {0};

    // set starting values. keeps track of which characters are at what index
    for (int i=0; i<m_char_set_size; i++) {
        index_tracker[i] = i;
    }

    for (int depth=0; depth<m_block_size; depth++) {
        // sorting input: p.m_count_table
        // sorting output: m_count_table
        for (int start=0; start<getCountLength(depth); start+=m_char_set_size) {
            // custom sort since we want to avoid lots of memory alloc
            // using insertion sort for now. make it better later

            // set starting values as well as check if there is data in the current array
            bool has_data = false;
            for (int i=0; i<m_char_set_size; i++) {
                index_tracker[i] = i;
                if (p.at(depth, start+i) != 0) {
                    has_data = true;
                }
            }

            // VV this is all within the context of the sub arrays of size m_char_set_size
            // the insertionSort implementation is weird. Still messes around with the index_tracker
            // even if the items are all zeros. Also, a lot of time is saved if
            // empty arrays are not processed (although, if you are training with enough data
            // and good data, hopefully all the arrays will have data)
            if (has_data) {
                utils::insertionSort(p.atRef(depth, start), m_char_set_size, index_tracker);
            }

            // copy values into their char values, reversed into our count_table
            // this allows the user to have the most probable characters at the lowest
            // indicies and not have to have any awareness of m_ascii_start
            for (int i=0; i<m_char_set_size; i++) {
                m_count_table[depth][start+i] = m_ascii_start + index_tracker[m_char_set_size-i-1];
            }
        }
    }
}

void Predictor::serializeToFile(std::string filename) const {
    std::ofstream out_stream(filename, std::ios::binary | std::ios::out);

    boost::iostreams::filtering_ostream out;
    out.push(boost::iostreams::gzip_compressor());
    out.push(out_stream);

    boost::archive::binary_oarchive out_archive(out);

    out_archive << *this;
}

void Predictor::deserializeFromFile(std::string filename) {
    std::ifstream in_stream(filename, std::ios::binary | std::ios::in);

    boost::iostreams::filtering_istream filter;
    filter.push(boost::iostreams::gzip_decompressor());
    filter.push(in_stream);

    boost::archive::binary_iarchive ia(filter);
    Predictor temp(m_char_set_size, m_block_size);
    ia >> *this;
}

void Predictor::getChars(int64_t* p, int n, char* out) const {
    char last_char = m_ascii_start;
    int64_t start = 0;
    for (int i=0; i<n; i++) {
        // start is a sum of the character's indicies where the first should be 
        // multiplied by m_char_set_size^(i-1). This sum can be factored by 95 
        // each time it is used, so multiplying it each time acts as "adding"
        // that factor in. Naturally the indicies that have been around the longest
        // end up with the largest power.
        start += (last_char-m_ascii_start);
        start *= m_char_set_size;
        last_char = m_count_table[i][start + p[i]];

        out[i] = last_char;
    }
}

char Predictor::getNextChar(char* a, int last_index) const {
    int64_t index = 0;
    for (int i=0; i<m_block_size-1; i++) {
        index += getCountBlockSize(m_block_size-i-1) * (a[i] - m_ascii_start);
    }

    return m_count_table[m_block_size - 1][index + last_index];
}
