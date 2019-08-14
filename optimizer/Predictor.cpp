#include "PTree.h"
#include "Predictor.h"
#include "utils.h"

Predictor::Predictor(long ss, long bs) : BigTree(ss, bs) {}

void Predictor::genFromPTree(PTree p) {
    int** tree_table = p.getTreeTable();

    int index_tracker[m_char_set_size] = {0};

    // set starting values. keeps track of which characters are at what index
    for (int i=0; i<m_char_set_size; i++) {
        index_tracker[i] = i;
    }

    for (int depth=0; depth<m_block_size; depth++) {
        // sorting input: tree_table
        // sorting output: m_count_table
        for (int start=0; start<getCountLength(depth); start+=m_char_set_size) {
            // custom sort since we want to avoid lots of memory alloc
            // using insertion sort for now. make it better later

            // set starting values as well as check if there is data in the current array
            bool has_data = false;
            for (int i=0; i<m_char_set_size; i++) {
                index_tracker[i] = i;
                if (tree_table[depth][start+i] != 0) {
                    has_data = true;
                }
            }

            // VV this is all within the context of the sub arrays of size m_char_set_size
            // the insertionSort implementation is weird. Still messes around with the index_tracker
            // even if the items are all zeros. Also, a lot of time is saved if
            // empty arrays are not processed (although, if you are training with enough data
            // and good data, hopefully all the arrays will have data)
            if (has_data) {
                utils::insertionSort(&tree_table[depth][start], m_char_set_size, index_tracker);
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
