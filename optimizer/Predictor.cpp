#include "PTree.h"
#include "Predictor.h"
#include "utils.h"

Predictor::Predictor(long ss, long bs) : BigTree(ss, bs) {}

void Predictor::genFromPTree(PTree const& p) {
    long** tree_table = p.getTreeTable();

    for (int depth=0; depth<m_block_size; depth++) {
        // 1 item from depth-1 = 1 block at the current depth
        // so, we must sort getCountLength(depth-1) blocks
        // this can be simplified to getCountBlockSize(depth), since
        // getCountLength(depth-1) == getCountBlockSize(depth)
        for (int i=0; i<getCountBlockSize(depth); i++) {

        }
    }

    std::cout << "node\n";
    for (int i=0; i<4; i++) {
        std::cout << p.getCountAt("node", i) << "\n";
    }

    std::cout << "nope\n";
    for (int i=0; i<4; i++) {
        std::cout << p.getCountAt("nope", i) << "\n";
    }
}
