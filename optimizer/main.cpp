#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <chrono>

#include "BigTree.h"
#include "BigTreeException.h"
#include "PTree.h"
#include "Predictor.h"
#include "PredictorCounter.h"

const long BLOCK_SIZE = 4;
const long CHAR_SET_SIZE = 95;

int main() {
    Predictor pred(CHAR_SET_SIZE, BLOCK_SIZE);
    pred.deserializeFromFile("/home/cwhite/test/hash-bash/optimizer/trained.dat.gz");
    /*
    PTree p(CHAR_SET_SIZE, BLOCK_SIZE, ' ');

    p.addStr("node");
    p.addStr("nope");
    p.addStr("nail");

    Predictor pred(CHAR_SET_SIZE, BLOCK_SIZE);
    pred.genFromPTree(p);
    */
    PredictorCounter pc(pred, 4, 1);
    pc.genAll();
}
