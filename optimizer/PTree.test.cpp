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

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
