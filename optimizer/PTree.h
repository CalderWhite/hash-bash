#pragma once

#include "utils.h"
#include "BigTree.h"

/**
 * A PTree contains the counts of each character after a certain string of characters that come before it.
 * This is found by ingesting large amounts of strings into the class using addStr().
 *
 * Further Explanation:
 * This class is used to count the occurances of certain strings of characters.
 * This is done by creating a tree where one character leads to another, and each
 * node in the tree has a specific count associated with it.
 * For example, if you were to call addStr() on both "park" and "pays", the tree would be as follows:
 *
 * p(2) --> a(2) --> r(1) --> k(1)
 *          |
 *          +-- y(1) --> s(1)
 *
 * This structure is similar to a trie. However, in a PTree, all of the different possibilities are stored.
 *
 * Parallelization:
 * The class is not designed to be operated on in parallel. However, this can be accomplished with
 * processing sub-trees and then merging the gathered data with mergeTree().
 * i.e. : You have 1000 strings. In one thread you create a PTree and process 500. 
 *        In another you process the other 500. Then, you merge one into the other (or a main PTree).
 *        This final tree has the same result as processing the 1000 strings serially in 1 thread.
 */
class PTree : BigTree<long> {
public:
    PTree(long char_set_size, long block_size, char ascii_start=' ');

    // Rule of 3
    /*
    ~PTree();
    PTree(const PTree& ptree);
    PTree& operator= (const PTree& ptree);
    */

    /*
     * Increments the count of each character based on the tree's trie-like structure.
     */
    void addStr(const char s[], int len=0);

    /**
     * Merges the current count tree with the inputted PTree's count tree.
     */
    void mergeTree(PTree const& p);

    /*
     * Finds the count of the final node in the string's tree
     * I.e. If you were to run getSubCount("abc"):
     *
     * Where x reps a's count
     * Where y reps b's count
     * Where z reps c's count
     *
     * a(x) --> b(y) --> c(z)
     *                   ^
     *                   | this value
     *
     * The return value would be z.
     */
    int getSubCount(const char* s) const;

    /**
     * Similar to getSubCount(), except you can chose at what level you get the count.
     */
    int getCountAt(const char* s, int i) const;

    /**
     * Returns the offset of the s[l-1] in m_count_table[l-1]
     * (l-1 since the table starts at 0, but the str len starts at 1)
     */
    long getCharIndex(const char s[], int cindex) const;
};
