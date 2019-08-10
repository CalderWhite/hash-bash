#include <math.h>

#include "gtest/gtest.h"

#include "PTree.h"

TEST(PTree, CountTableSmall) {
    long block_size = 4;
    long char_set_size = 95;
    PTree p(char_set_size, block_size, ' ');

    // testing the count addition of no
    p.addStr("node");
    p.addStr("nope");

    // In ascii, ~ is the last readable character.
    // This is important, since the following test makes sure our arrays are the correct size
    // If the size is incorrect, PTree will throw a segmentation fault.
    p.addStr("~~~~");

    EXPECT_EQ(2, p.getSubCount("n"));
    EXPECT_EQ(2, p.getSubCount("no"));

    EXPECT_EQ(1, p.getSubCount("nod"));
    EXPECT_EQ(1, p.getSubCount("nop"));

    EXPECT_EQ(1, p.getSubCount("node"));
    EXPECT_EQ(1, p.getSubCount("nope"));

    EXPECT_EQ(1, p.getSubCount("~~~~"));
}

TEST(PTree, CountTableLarge) {
    long block_size = 3;
    long char_set_size = 95;
    PTree p(char_set_size, block_size, ' ');


    char s[block_size] = {0};
    for (int i=0; i<95; i++) {
        s[0] = ' ' + i;
        for (int j=0; j<95; j++) {
            s[1] = ' ' + j;
            for (int k=0; k<95; k++) {
                s[2] = ' ' + k;
                p.addStr(s, block_size);
            }
        }
    }

    for (int i=0; i<char_set_size; i++) {
        s[0] = ' ' + i;
        for (int j=0; j<char_set_size; j++) {
            s[1] = ' ' + j;
            EXPECT_EQ(95, p.getCountAt(s, 1));
            for (int k=0; k<char_set_size; k++) {
                s[2] = ' ' + k;

                ASSERT_EQ(1, p.getCountAt(s, 2));
            }
        }
    }
}

TEST(PTree, MergeTreeSmall) {
    long block_size = 3;
    long char_set_size = 95;
    PTree p(char_set_size, block_size, ' ');
    PTree q(char_set_size, block_size, ' ');

    p.addStr("thi");
    q.addStr("tha");

    p.mergeTree(q);

    EXPECT_EQ(2, p.getCountAt("t", 0));
    EXPECT_EQ(2, p.getCountAt("th", 1));
    EXPECT_EQ(1, p.getCountAt("thi", 2));
    EXPECT_EQ(1, p.getCountAt("tha", 2));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
