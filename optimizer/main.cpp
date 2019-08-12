#include <iostream>
#include <exception>

#include "BigTree.h"
#include "BigTreeException.h"
#include "PTree.h"
#include "Predictor.h"

const long BLOCK_SIZE = 4;
const long CHAR_SET_SIZE = 95;

int main() {
    const long block_size = 4;
    const long char_set_size = 95;
    PTree p(char_set_size, block_size, ' ');

    p.addStr("node");
    p.addStr("nope");

    Predictor pred(char_set_size, block_size);
    pred.genFromPTree(p);
}
