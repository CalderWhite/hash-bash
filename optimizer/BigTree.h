#pragma once

#include <exception>
#include <stdint.h>

#include "utils.h"
#include "BigTreeException.h"

/**
 * Although templating is discouraged, the overlap between the Predictor and CountTree was too great.
 * Thus, a base "BigTree" template class was created. This contains most of the code for general operations
 * on the tree to provide a layer of abstraction above the 2d array representing the tree, indexed by a character string
 */
template <typename T>
class BigTree {
public:
    BigTree(int64_t ss, int64_t bs, char st = ' ')
        : m_char_set_size(ss), m_block_size(bs), m_ascii_start(st) {

        initPowerArray();
        allocateCountTableArrays();
    }

    ~BigTree() {
        deallocateCountTableArrays();
    }

    BigTree(const BigTree& p) : BigTree(p.m_char_set_size, p.m_block_size, p.m_ascii_start) {
        for (int i=0; i<m_block_size; i++) {
            std::copy(p.m_count_table[i], p.m_count_table[i] + p.getCountLength(i),
                      m_count_table[i]);
        }
    }

    BigTree& operator= (const BigTree& p) {
        return *this;
    }

    /**
     * Returns the offset of the s[l-1] in m_count_table[l-1]
     * (l-1 since the table starts at 0, but the str len starts at 1)
     */
    int64_t getCharIndex(const char s[], int cindex) const {
        // TODO any faster with formula? (Probably not, since closed form uses powers)
        int64_t index = 0;
        for (int i=0; i<=cindex; i++) {
            index += (s[i] - m_ascii_start) * getCountBlockSize(cindex-i);
        }

        return index;
    }

    /**
     * Returns the value at [depth][index] to avoid direct access of the tree.
     */
    T at(int depth, int64_t index) const {
        return m_count_table[depth][index];
    }

    /**
     * Returns a reference to [depth][index].
     * This is useful for operating on the sub-arrays of m_count_table[depth].
     * (This is because each branch is stored next to one another. Each are of length m_char_set_size.)
     */
    T* atRef(int depth, int64_t index) const {
        return &m_count_table[depth][index];
    }

    /**
     * This method is used to avoid the calculation of powers.
     *
     * @return The length of the m_count_table[i]
     */
    inline int64_t getCountLength(int i) const {
        return m_powers[i+1];
    }

    /**
     * Returns the length of the sub-arrays of m_count_table[i] using m_powers.
     * 0 -> 1
     * 1 -> m_char_set_size
     * 2 -> m_char_set_size^2
     * ...
     * m_block_size-1 -> m_char_set_size^(m_block_size-1)
     */
    inline int64_t getCountBlockSize(int i) const {
        return m_powers[i];
    }

    /**
     * Getters
     */

    inline int getBlockSize() const {
        return m_block_size;
    }

    inline int getCharSetSize() const {
        return m_char_set_size;
    }

    inline char getAsciiStart() const {
        return m_ascii_start;
    }

protected:
    int64_t m_char_set_size;
    int64_t m_block_size;
    char m_ascii_start;

    /**
     * Contains pointers to the counter arrays at each level of the tree.
     * The structure & size is outlined as follows:
     *     0 -> the first character, length of m_char_set_size
     *     1-> the second character, length of m_char_set_size^2
     *     ...
     *     m_block_size-1 -> the last character in the block, 
     *                       length of m_char_set_size^m_block_size
     */
    T** m_count_table;

    /**
     * Stores the powers m_char_set_size of from 0 to m_block_size 
     */
    int64_t* m_powers;

    void initPowerArray() {
        m_powers = new int64_t[m_block_size+1]();
        for (int i=0; i<m_block_size+1; i++) {
            m_powers[i] = utils::ipow(m_char_set_size, i);
        }

    }

    /**
     * Creates each counting array in m_count_table based on getCountLength()
     */
    void allocateCountTableArrays() {
        m_count_table = new T*[m_block_size]();
        try {
            for (int i=0; i<m_block_size; i++) {
                m_count_table[i] = new T[getCountLength(i)]();
            }
        } catch (std::bad_alloc) {
            deallocateCountTableArrays();
            throw BigTreeException("Failed to allocate memory for count table!");
        }
    }

    /**
     * Deletes the arrays created by allocateCountTableArrays().
     */
    void deallocateCountTableArrays() {
        for (int i=0; i<m_block_size; i++) {
            delete[] m_count_table[i];
        }

        delete[] m_count_table;
        delete[] m_powers;
    }
};
