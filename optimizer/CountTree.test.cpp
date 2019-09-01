#include <math.h>
#include <stdint.h>

#include "gtest/gtest.h"

#include "CountTree.h"

TEST(CountTree, CountTableSmall) {
    int64_t block_size = 4;
    int64_t char_set_size = 95;
    CountTree p(char_set_size, block_size, ' ');

    // testing the count addition of no
    p.addStr("node");
    p.addStr("nope");

    // In ascii, ~ is the last readable character.
    // This is important, since the following test makes sure our arrays are the correct size
    // If the size is incorrect, CountTree will throw a segmentation fault.
    p.addStr("~~~~");

    EXPECT_EQ(2, p.getSubCount("n"));
    EXPECT_EQ(2, p.getSubCount("no"));

    EXPECT_EQ(1, p.getSubCount("nod"));
    EXPECT_EQ(1, p.getSubCount("nop"));

    EXPECT_EQ(1, p.getSubCount("node"));
    EXPECT_EQ(1, p.getSubCount("nope"));

    EXPECT_EQ(1, p.getSubCount("~~~~"));
}

TEST(CountTree, CountTableLarge) {
    int64_t block_size = 3;
    int64_t char_set_size = 95;
    CountTree p(char_set_size, block_size, ' ');


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

TEST(CountTree, MergeTreeSmall) {
    int64_t block_size = 3;
    int64_t char_set_size = 95;
    CountTree p(char_set_size, block_size, ' ');
    CountTree q(char_set_size, block_size, ' ');

    p.addStr("thi");
    q.addStr("tha");

    p.mergeTree(q);

    EXPECT_EQ(2, p.getCountAt("t", 0));
    EXPECT_EQ(2, p.getCountAt("th", 1));
    EXPECT_EQ(1, p.getCountAt("thi", 2));
    EXPECT_EQ(1, p.getCountAt("tha", 2));
}

TEST(CountTree, AddLongStr) {
    int64_t block_size = 3;
    int64_t char_set_size = 95;
    CountTree p(char_set_size, block_size, ' ');

    p.addLongStr("abcd", 4);

    EXPECT_EQ(1, p.getCountAt("a", 0));
    EXPECT_EQ(1, p.getCountAt("b", 0));

    EXPECT_EQ(1, p.getCountAt("ab", 1));
    EXPECT_EQ(1, p.getCountAt("bc", 1));
}

TEST(CountTree, IngestDataNoNewline) {
    CountTree p(95, 3);

    const char test[] = "abcd";
    p.ingestData(&test[0], &test[0] + 4);

    EXPECT_EQ(1, p.getCountAt("a", 0));
    EXPECT_EQ(1, p.getCountAt("b", 0));

    EXPECT_EQ(1, p.getCountAt("ab", 1));
    EXPECT_EQ(1, p.getCountAt("bc", 1));

    EXPECT_EQ(1, p.getCountAt("abc", 2));
    EXPECT_EQ(1, p.getCountAt("bcd", 2));
}

TEST(CountTree, IngestDataMultiple) {
    CountTree p(95, 3);

    const char test[] = "this\nthat\n";
    p.ingestData(&test[0], &test[0] + 9);

    EXPECT_EQ(2, p.getCountAt("t", 0));
    EXPECT_EQ(2, p.getCountAt("th", 1));
    EXPECT_EQ(1, p.getCountAt("thi", 2));
    EXPECT_EQ(1, p.getCountAt("tha", 2));
}

TEST(CountTree, IngestFileMultiThreadSplit) {
    CountTree p(95, 3);

    std::istringstream test("this\nthat\n");
    p.ingestFileMultiThread(test, 2);

    EXPECT_EQ(2, p.getCountAt("t", 0));
    EXPECT_EQ(2, p.getCountAt("th", 1));
    EXPECT_EQ(1, p.getCountAt("thi", 2));
    EXPECT_EQ(1, p.getCountAt("tha", 2));
}

TEST(CountTree, IngestFileMultiThreadExtra) {
    CountTree p(95, 3);

    std::istringstream test("this\nthat\n");
    p.ingestFileMultiThread(test, 3);

    EXPECT_EQ(2, p.getCountAt("t", 0));
    EXPECT_EQ(2, p.getCountAt("th", 1));
    EXPECT_EQ(1, p.getCountAt("thi", 2));
    EXPECT_EQ(1, p.getCountAt("tha", 2));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
