#include <iostream>

#include "PTree.h"

const long BLOCK_SIZE = 4;
const long CHAR_SET_SIZE = 95;

int main() {
    PTree p(CHAR_SET_SIZE, BLOCK_SIZE);

    char s[BLOCK_SIZE] = {0};
    for (int i=0; i<CHAR_SET_SIZE; i++) {
        for (int j=0; j<CHAR_SET_SIZE; j++) {
            for (int k=0; k<CHAR_SET_SIZE; k++) {
                for (int l=0; l<CHAR_SET_SIZE; l++) {
                    s[0] = ' ' + i;
                    s[1] = ' ' + j;
                    s[2] = ' ' + k;
                    s[3] = ' ' + l;

                    p.addStr(s);
                }
            }
        }
    }

    p.test();
}
