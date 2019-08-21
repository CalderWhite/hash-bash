#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <chrono>

#include "BigTree.h"
#include "BigTreeException.h"
#include "PTree.h"
#include "Predictor.h"

const long BLOCK_SIZE = 4;
const long CHAR_SET_SIZE = 95;

std::chrono::high_resolution_clock::time_point getTime() {
    return std::chrono::high_resolution_clock::now();
}

long long getTimeDiff(
    std::chrono::high_resolution_clock::time_point t1,
    std::chrono::high_resolution_clock::time_point t2) {
    return std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
}

int main() {
    std::ifstream infile("data/crackstation-human-only.txt");
    const long block_size = 4;
    const long char_set_size = 95;
    PTree p(char_set_size, block_size, ' ');

    if (infile.is_open()) {
        //std::cout << "Reading data file...\n";

        auto t1 = getTime();
        p.ingestFileMultiThread(infile, 4);
        std::cout << getTimeDiff(t1, getTime()) << "\n";

        infile.close();
    } else {
        std::cout << "Unable to open file.\n";
    }

    std::cout << "Generating Predictor...\n";

    Predictor pred(char_set_size, block_size);
    pred.genFromPTree(p);

    std::cout << "Writing out compressed stream...\n";
    pred.serializeToFile("trained.dat.gz");
}
