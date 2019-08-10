#include <iostream>
#include <exception>

#include "PTree.h"
#include "PTreeException.h"

const long BLOCK_SIZE = 4;
const long CHAR_SET_SIZE = 95;

void testme() {
    const long block_size = 4;
    const long char_set_size = 95;
    PTree p(char_set_size, block_size, ' ');

    std::cout << p.getSubCount("no") << "\n";

    // testing the count addition of no
    p.addStr("node");
    p.addStr("nope");

    // In ascii, ~ is the last readable character.
    // This is important, since the following test makes sure our arrays are the correct size
    // If the size is incorrect, PTree will throw a segmentation fault.
    p.addStr("~~~~");

    /*
    EXPECT_EQ(2, p.getSubCount("n"));
    EXPECT_EQ(2, p.getSubCount("no"));

    EXPECT_EQ(1, p.getSubCount("nod"));
    EXPECT_EQ(1, p.getSubCount("nop"));

    EXPECT_EQ(1, p.getSubCount("node"));
    EXPECT_EQ(1, p.getSubCount("nope"));

    EXPECT_EQ(1, p.getSubCount("~~~~"));
    */

    std::cout << p.getSubCount("no") << "\n";
}

int main() {
    testme();
    testme();
}
