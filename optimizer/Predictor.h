#pragma once

#include <stdint.h>

#include "PTree.h"
#include "BigTree.h"

class Predictor : BigTree<char> {
public:
    Predictor(int64_t ss, int64_t bs);

    void genFromPTree(PTree p);
};
