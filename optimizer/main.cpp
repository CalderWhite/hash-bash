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

std::chrono::high_resolution_clock::time_point getTime() {
    return std::chrono::high_resolution_clock::now();
}

long long getTimeDiff(
    std::chrono::high_resolution_clock::time_point t1,
    std::chrono::high_resolution_clock::time_point t2) {
    return std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
}

int main() {
    //Predictor pred(CHAR_SET_SIZE, BLOCK_SIZE);
    //pred.deserializeFromFile("/home/calder/repos/hash-bash/optimizer/trained.dat.gz");

    /*
    PredictorCounter pc(pred, 12, 1);

    char s[12] = {0};
    pc.getNext(s);

    std::cout << s << "\n";
    */

    int64_t block_size = 4;
    int64_t char_set_size = 95;
    PTree p(char_set_size, block_size, ' ');

    p.addStr("node");
    p.addStr("nope");
    p.addStr("~~~~");

    Predictor pred(char_set_size, block_size);
    pred.genFromPTree(p);

    // add 1 to make it a c string terminated by \0
    char o[block_size + 1] = {0};
    int64_t c[block_size] = {0};
    pred.getChars(c, block_size, o);
    std::cout << o << "\n";

    /*
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
    */
}
