#include <math.h>
#include <stdint.h>

#include "gtest/gtest.h"

#include "utils.h"

/**
 * Compares the output of the custom ipow private method to 1L left shifted
 * increasing amounts up to the limit of a int64_t.
 */
TEST(Utils, IpowPowersOfTwo) {
    for (int i=0; i<64; i++) {
        ASSERT_EQ(1L << i, utils::ipow(2, i));
    }
}

/**
 * Compares the output of the custom ipow private method to the output
 * of the standard library's pow() function.
 */
TEST(Utils, IpowStdPow) {
    const int test_count = 4;

    int64_t bases[test_count] = {
        1,
        2,
        6,
        123553,
    };

    for (int i=0; i<test_count; i++) {
        for (int j=0; j<3; j++) {
            ASSERT_EQ(static_cast<int64_t>(pow(bases[i], j)), utils::ipow(bases[i], j));
        }
    }
}

// TODO: BinarySearch Test
// TODO: InsertionSort Test

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
