#include <math.h>
#include <stdint.h>

#include "gtest/gtest.h"

#include "PTree.h"
#include "Predictor.h"

TEST(Predictor, GetCharsTest) {
    int64_t block_size = 4;
    int64_t char_set_size = 95;
    PTree p(char_set_size, block_size, ' ');

    p.addStr("node");
    p.addStr("nope");
    p.addStr("nail");

    Predictor pred(char_set_size, block_size);
    pred.genFromPTree(p);

    // add 1 to make it a c string terminated by \0
    char o[block_size + 1] = {0};

    // I liked the appearance of the initializer lists, so I put them in seperate scopes
    {
        int64_t c[block_size] = {0};
        pred.getChars(c, block_size, o);
        EXPECT_STREQ(o, "node");
    }

    {
        int64_t c[block_size] = {0, 0, 1, 0};
        pred.getChars(c, block_size, o);
        EXPECT_STREQ(o, "nope");
    }

    {
        int64_t c[block_size] = {0, 1, 0, 0};
        pred.getChars(c, block_size, o);
        EXPECT_STREQ(o, "nail");
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
