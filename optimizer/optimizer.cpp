#include <iostream>

#include "Predictor.h"
#include "PredictorCounter.h"

const long BLOCK_SIZE = 4;
const long CHAR_SET_SIZE = 95;

int main() {
    Predictor pred(CHAR_SET_SIZE, BLOCK_SIZE);
    pred.deserializeFromFile("trained.dat.gz");

    PredictorCounter pc(pred, 8, 1);

    std::cout << pc.getOffset("iiiiiiii") << "\n";
}
