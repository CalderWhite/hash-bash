#include <iostream>
#include <algorithm>
#include <cstring>
#include <exception>
#include <math.h>

#include "PTree.h"

PTree::PTree(long ss, long bs, char st)
    : m_char_set_size(ss), m_block_size(bs), m_ascii_start(st) {

    m_count_table_block_sizes = new long[m_block_size];
    for (int i=0; i<m_block_size; i++) {
        m_count_table_block_sizes[i] = ipow(m_char_set_size, i);
    }

    allocateArrays();
}

PTree::~PTree() {
    for (int i=0; i<m_block_size; i++) {
        delete[] m_count_table[i];
    }

    delete[] m_count_table;
    delete[] m_count_table_block_sizes;

    std::cout << "Deleted!\n";
}

PTree::PTree(const PTree& p) {
    m_char_set_size = p.m_char_set_size;
    m_block_size = p.m_block_size;
    m_ascii_start = p.m_ascii_start;

    allocateArrays();

    // TODO test this feature
    for (int i=0; i<m_block_size; i++) {
        std::copy(p.m_count_table[i], p.m_count_table[i] + ipow(m_char_set_size, i+1),
                  m_count_table[i]);
    }
}

PTree& PTree::operator= (const PTree& ptree) {
    static PTree p(ptree);
    return p;
}

/**
 * Traverses the tree from the first char to the last, via the count table (m_count_table).
 * At each level of the tree, it increments the count of the character it is at before traversing
 * one further down the tree.
 */
void PTree::addStr(char s[]) {

    if (strlen(s) != m_block_size) {
        std::cout << "Error: Input string did not match block size!\n";
        throw "Input string did not match block size!\n";
    }

    for (int i=0; i<m_block_size; i++) {
        long index = 0;
        for (int j=0; j<=i; j++) {
            index += (s[j] - m_ascii_start) * m_count_table_block_sizes[i-j];
        }

        //m_count_table[i][index] = s[i] - m_ascii_start;
        ++m_count_table[i][index];
    }
}

void PTree::allocateArrays() {
    m_count_table = new int*[m_block_size];
    for (int i=0; i<m_block_size; i++) {
        m_count_table[i] = new int[ipow(m_char_set_size, i+1)];
    }
}

long PTree::ipow(long base, long exponent) {
    long c = 1;
    for (long i=0; i<exponent; i++) {
        c *= base;
    }

    return c;
}

void PTree::test() {
    for (int i=0; i<m_block_size; i++) {
        std::cout << "Step: " << m_count_table_block_sizes[i] << "\n";
        for (int j=0; j<ipow(m_char_set_size, i+1); j++) {
            //if(m_count_table[i][j] != 1)
            //    std::cout << "Bad!\n";
            std::cout << m_count_table[i][j] << "\n";
        }
        std::cout << "------------\n";
    }
}
