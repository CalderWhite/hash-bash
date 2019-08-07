#pragma once

class PTree {
public:
    PTree(long char_set_size, long block_size, char ascii_start=' ');

    // Rule of 3
    ~PTree();
    PTree(const PTree& ptree);
    PTree& operator= (const PTree& ptree);

    /*
     * Increments the count of each character based on the tree's trie-like structure.
     */
    void addStr(char s[]);

    /**
     * Merges the current count tree with the inputted PTree's count tree.
     */
    void mergeTree(PTree const& p);

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
     * Stores the powers m_char_set_size of from 0 to m_block_size 
     */
    long* m_powers;

    /**
     * Creates each counting array in m_count_table based on getCountLength()
     */
    void allocateCountTableArrays();

    void deallocateCountTableArrays();

    /**
     * Util function. Returns the base^exponent for integers only.
     */
    long ipow(long base, long exponent) const;

    /**
     * This method is used to avoid the calculation of powers.
     *
     * @return The length of the m_count_table[i]
     */
    inline long getCountLength(int i) const;

    /**
     * Returns the length of the sub-arrays of m_count_table[i] using m_powers.
     * 0 -> 1
     * 1 -> m_char_set_size
     * 2 -> m_char_set_size^2
     * ...
     * m_block_size-1 -> m_char_set_size^(m_block_size-1)
     */
    inline long getCountBlockSize(int i) const;
};
