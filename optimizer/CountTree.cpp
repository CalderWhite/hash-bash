#include <iostream>
#include <algorithm>
#include <cstring>
#include <exception>
#include <string>
#include <istream>
#include <sstream>
#include <thread>
#include <vector>
#include <math.h>
#include <stdint.h>

#include "utils.h"
#include "CountTree.h"
#include "CountTreeException.h"

CountTree::CountTree(int64_t ss, int64_t bs, char st)
    : BigTree(ss, bs, st) {
}

/**
 * Traverses the tree from the first char to the last, via the count table (m_count_table).
 * At each level of the tree, it increments the count of the character it is at before traversing
 * one further down the tree.
 */
void CountTree::addStr(const char s[], int len) {
    if (len == 0) {
        if (strlen(s) != static_cast<unsigned int>(m_block_size)) {
            throw CountTreeException("Input string did not match block size!");
        }
    } else if (len != m_block_size) {
        throw CountTreeException("Input string did not match block size!");
    }

    for (int i=0; i<m_block_size; i++) {
        if (s[i] >= m_ascii_start && s[i] < m_ascii_start + m_char_set_size) {
            ++m_count_table[i][getCharIndex(s, i)];
        } else {
            return; // TODO return int that signals whether or not it was added?
        }
    }
}

void CountTree::addLongStr(const char s[], int len) {
    for (int i=0; i<(len-m_block_size)+1; i++) {
        addStr(&s[0] + i, m_block_size);
    }
}

void CountTree::mergeTree(CountTree const& p) {
    if (p.m_block_size != m_block_size) {
        throw CountTreeException("Mismatched block sizes in attempted tree merge!");
    }

    for (int depth=0; depth<m_block_size; depth++) {
        for (int i=0; i<getCountLength(depth); i++) {
            m_count_table[depth][i] += p.m_count_table[depth][i];
        }
    }
}

int CountTree::getSubCount(const char* s) const {
    const int last_char_index = strlen(s) - 1;
    const int64_t index = getCharIndex(s, last_char_index);
    return m_count_table[last_char_index][index];
}

int CountTree::getCountAt(const char* s, int i) const {
    const int64_t index = getCharIndex(s, i);
    return m_count_table[i][index];
}

int64_t CountTree::getCharIndex(const char s[], int cindex) const {
    // TODO any faster with formula? (Probably not, since closed form uses powers)
    int64_t index = 0;
    for (int i=0; i<=cindex; i++) {
        index += (s[i] - m_ascii_start) * getCountBlockSize(cindex-i);
    }

    return index;
}
void CountTree::createIngestThread(const char* start, const char* stop, CountTree* ptree) {
    ptree->ingestData(start, stop);
}

void CountTree::ingestData(const char* start, const char* stop) {
    while (start < stop) {
        const char* next = start;
        while (*(++next) != '\n' && next < stop) {
        }

        addLongStr(start, next-start);

        start = next;
    }
}

void CountTree::ingestFileMultiThread(std::istream& infile, int thread_count) {
    const std::string data(static_cast<std::stringstream const&>(std::stringstream() << infile.rdbuf()).str());

    //const char* data_ptr = data.c_str();
    const int chunk_size = data.length() / thread_count;
    const char* chunk_delim[thread_count+1] = {0};

    chunk_delim[0] = &data[0];

    // build chunks that end on newlines
    int point = 0;
    int i = 1;
    while ((point += chunk_size) < data.length()) {
        while (data[point] != '\n' && point < data.length()) {
            ++point;
        }

        chunk_delim[i] = &data[0] + point;
        ++i;
    }

    chunk_delim[i] = &data[0] + data.length();

    std::vector<CountTree> trees;
    trees.reserve(thread_count);

    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    for (int i=0; i<thread_count; i++) {
        trees.emplace_back(m_char_set_size, m_block_size, m_ascii_start);
        threads.emplace_back(createIngestThread, chunk_delim[i], chunk_delim[i+1], &trees[i]);
    }

    for (int i=0; i<thread_count; i++) {
        threads[i].join();
        mergeTree(trees[i]);
    }
}
