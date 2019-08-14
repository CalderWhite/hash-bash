#pragma once

#include "PTree.h"
#include "BigTree.h"

class Predictor : BigTree<char> {
public:
    Predictor(long ss, long bs);

    void genFromPTree(PTree p);
};
