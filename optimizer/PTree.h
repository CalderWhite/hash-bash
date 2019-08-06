#pragma once

class PTree {
public:
    PTree(long char_set_size, long block_size, char ascii_start=' ');

    // Rule of 3
    ~PTree();
    PTree(const PTree& ptree);
    PTree& operator= (const PTree& ptree);

    void addStr(char s[]);
    void test();
private:
    long m_char_set_size;
    long m_block_size;
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
    int** m_count_table;

    /**
     * Stores the sizes of each count table to reduce the number of powers that are calculated.
     * 0 -> 1
     * 1 -> m_char_set_size
     * 2 -> m_char_set_size^2
     * ...
     * m_block_size-1 -> m_char_set_size^(m_block_size-1)
     */
    long* m_count_table_block_sizes;

    void allocateArrays();
    long ipow(long base, long exponent);
};
