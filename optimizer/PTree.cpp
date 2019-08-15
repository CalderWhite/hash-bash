#include <iostream>
#include <algorithm>
#include <cstring>
#include <exception>
#include <math.h>
#include <stdint.h>

#include "utils.h"
#include "PTree.h"
#include "PTreeException.h"

PTree::PTree(int64_t ss, int64_t bs, char st)
    : BigTree(ss, bs, st) {
}

/**
 * Traverses the tree from the first char to the last, via the count table (m_count_table).
 * At each level of the tree, it increments the count of the character it is at before traversing
 * one further down the tree.
 */
void PTree::addStr(const char s[], int len) {
    if (len == 0) {
        if (strlen(s) != m_block_size) {
            throw PTreeException("Input string did not match block size!");
        }
    } else if (len != m_block_size) {
        throw PTreeException("Input string did not match block size!");
    }

    for (int i=0; i<m_block_size; i++) {
        ++m_count_table[i][getCharIndex(s, i)];
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
    const int last_char_index = strlen(s) - 1;
    const int64_t index = getCharIndex(s, last_char_index);
    return m_count_table[last_char_index][index];
}

int PTree::getCountAt(const char* s, int i) const {
    const int64_t index = getCharIndex(s, i);
    return m_count_table[i][index];
}

int64_t PTree::getCharIndex(const char s[], int cindex) const {
    // TODO any faster with formula? (Probably not, since closed form uses powers)
    int64_t index = 0;
    for (int i=0; i<=cindex; i++) {
        index += (s[i] - m_ascii_start) * getCountBlockSize(cindex-i);
    }

    return index;
}
