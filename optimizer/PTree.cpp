#include <iostream>
#include <algorithm>
#include <cstring>
#include <exception>
#include <math.h>

#include "PTree.h"
#include "PTreeException.h"

PTree::PTree(long ss, long bs, char st)
    : m_char_set_size(ss), m_block_size(bs), m_ascii_start(st) {

    initPowerArray();
    allocateCountTableArrays();
}

PTree::~PTree() {
    deallocateCountTableArrays();
}

PTree::PTree(const PTree& p) : PTree(p.m_char_set_size, p.m_block_size, p.m_ascii_start) {
    // TODO test this feature
    for (int i=0; i<m_block_size; i++) {
        std::copy(p.m_count_table[i], p.m_count_table[i] + p.getCountLength(i),
                  m_count_table[i]);
    }
}

PTree& PTree::operator= (const PTree& p) {
    return *this;
}

/**
 * Traverses the tree from the first char to the last, via the count table (m_count_table).
 * At each level of the tree, it increments the count of the character it is at before traversing
 * one further down the tree.
 */
void PTree::addStr(const char s[]) {
    if (strlen(s) != m_block_size) {
        throw PTreeException("Input string did not match block size!");
    }

    for (int i=0; i<m_block_size; i++) {
        ++m_count_table[i][getLastOffset(s, i+1)];
    }
}

void PTree::mergeTree(PTree const& p) {
    if (p.m_block_size != m_block_size) {
        throw PTreeException("Mismatched block sizes in attempted tree merge!");
    }

    for (int depth=0; depth<m_block_size; depth++) {
        for (int i=0; i<getCountLength(depth); i++) {
            m_count_table[depth][i] += p.m_count_table[depth][i];
        }
    }
}

int PTree::getSubCount(const char* s) const {
    const long index = getLastOffset(s, strlen(s));
    return m_count_table[strlen(s)-1][index];
}

long PTree::getLastOffset(const char s[], int l) const {
    // TODO any faster with formula? (Probably not, since closed form uses powers)
    long index = 0;
    for (int i=0; i<l; i++) {
        index += (s[i] - m_ascii_start) * getCountBlockSize(l-i-1);
    }

    return index;
}

void PTree::initPowerArray() {
    m_powers = new long[m_block_size+1];
    for (int i=0; i<m_block_size+1; i++) {
        m_powers[i] = ipow(m_char_set_size, i);
    }

}

void PTree::allocateCountTableArrays() {
    m_count_table = new int*[m_block_size];
    try {
        for (int i=0; i<m_block_size; i++) {
            m_count_table[i] = new int[getCountLength(i)];
        }
    } catch (std::bad_alloc) {
        deallocateCountTableArrays();
        throw PTreeException("Failed to allocate memory for count table!");
    }
}

void PTree::deallocateCountTableArrays() {
    for (int i=0; i<m_block_size; i++) {
        delete[] m_count_table[i];
    }

    delete[] m_count_table;
    delete[] m_powers;
}

long PTree::ipow(long base, long exponent) const {
    long c = 1;
    for (long i=0; i<exponent; i++) {
        c *= base;
    }

    return c;
}

inline long PTree::getCountLength(int i) const {
    return m_powers[i+1];
}

inline long PTree::getCountBlockSize(int i) const {
    return m_powers[i];
}
