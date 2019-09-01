#include <math.h>
#include <stdint.h>

#include "gtest/gtest.h"

#include "CountTree.h"
#include "Predictor.h"
#include "PredictorCounter.h"

TEST(PredictorCounter, GetOffsetSameGuessLength) {
    int char_set_size = 95;
    int block_size = 4;
    CountTree p(char_set_size, block_size, ' ');

    p.addStr("node");
    p.addStr("nope");
    p.addStr("nail");

    Predictor pred(char_set_size, block_size);
    pred.genFromCountTree(p);

    // do not be confused: we are using block_size for the guess_length
    PredictorCounter pc(pred, block_size, 1);

    EXPECT_EQ(0, pc.getOffset("node"));
    EXPECT_EQ(char_set_size, pc.getOffset("nope"));
}

TEST(PredictorCounter, GetOffset) {
    int char_set_size = 95;
    int block_size = 4;
    CountTree p(char_set_size, block_size, ' ');

    p.addStr("bbbb");

    Predictor pred(char_set_size, block_size);
    pred.genFromCountTree(p);
    PredictorCounter pc(pred, 7, 1);

    EXPECT_EQ(0, pc.getOffset("bbbbbbb"));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
