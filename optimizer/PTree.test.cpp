#include <math.h>

#include "gtest/gtest.h"

#include "PTree.h"

/**
 * Compares the output of the custom ipow private method to 1L left shifted
 * increasing amounts up to the limit of a long.
 */
TEST(PTree, IpowPowersOfTwo) {
    PTree p(0, 0);

    for (int i=0; i<64; i++) {
        ASSERT_EQ(1L << i, p.ipow(2, i));
    }
}

/**
 * Compares the output of the custom ipow private method to the output
 * of the standard library's pow() function.
 */
TEST(PTree, IpowStdPow) {
    const int test_count = 6;
    PTree p(0, 0);

    long bases[test_count] = {
        1,
        2,
        6,
        123553,
    };

    for (int i=0; i<test_count; i++) {
        for (int j=0; j<3; j++) {
            ASSERT_EQ(static_cast<long>(pow(bases[i], j)), p.ipow(bases[i], j));
        }
    }
}

TEST(PTree, CountTableSmall) {
    const long block_size = 4;
    const long char_set_size = 95;
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
    const long block_size = 4;
    const long char_set_size = 95;
    PTree p(char_set_size, block_size, ' ');


    char s[block_size] = {0};
    for (int i=0; i<95; i++) {
        s[0] = ' ' + i;
        for (int j=0; j<95; j++) {
            s[1] = ' ' + j;
            for (int k=0; k<95; k++) {
                s[2] = ' ' + k;
                for (int l=0; l<95; l++) {
                    s[3] = ' ' + l;

                    p.addStr(s);
                }
            }
        }
    }

    for (int i=0; i<char_set_size; i++) {
        s[0] = ' ' + i;
        for (int j=0; j<char_set_size; j++) {
            s[1] = ' ' + j;
            for (int k=0; k<char_set_size; k++) {
                s[2] = ' ' + k;

                ASSERT_EQ(95, p.getCountAt(s, 2));
                for (int l=0; l<char_set_size; l++) {
                    s[3] = ' ' + l;

                    ASSERT_EQ(1, p.getSubCount(s));
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
