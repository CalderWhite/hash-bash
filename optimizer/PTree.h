#pragma once

/**
 * A PTree contains the counts of each character after a certain amount of characters that come before it.
 * This is found by ingesting large amounts of strings into the class using addStr().
 *
 * Further Explanation:
 * This class is used to count the occurances of certain strings of characters.
 * This is done by creating a tree where one character leads to another, and each
 * node in the tree has a specific count associated with it.
 * For example, if you were to call addStr() on both park and pays, the tree would be as follows:
 *
 * p(2) --> a(2) --> r(1) --> k(1)
 *          |
 *          +-- y(1) --> s(1)
 *
 * This structure is similar to a trie.
 *
 * Parallelization:
 * The class is not designed to be operated on in parallel, however this can be accomplished with
 * processing sub-trees and then merging the gathered data with mergeTree().
 * i.e. : You have 1000 strings. In one thread you create a PTree and process 500. 
 *        In another you process the other 500. Then, you merge one into the other (or a main PTree).
 */
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
