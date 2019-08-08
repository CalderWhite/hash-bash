#include <iostream>
#include <exception>

#include "PTree.h"
#include "PTreeException.h"

const long BLOCK_SIZE = 4;
const long CHAR_SET_SIZE = 95;

int main() {
    const long block_size = 4;
    const long char_set_size = 95;
    PTree p(char_set_size, block_size, ' ');

    char s[block_size] = {0};
    for (int i=0; i<95; i++) {
        for (int j=0; j<95; j++) {
            for (int k=0; k<95; k++) {
                for (int l=0; l<95; l++) {
                    s[0] = ' ' + i;
                    s[1] = ' ' + j;
                    s[2] = ' ' + k;
                    s[3] = ' ' + l;

                    p.addStr(s);
                }
            }
        }
    }

    for (int i=0; i<char_set_size; i++) {
        for (int j=0; j<char_set_size; j++) {
            for (int k=0; k<char_set_size; k++) {
                for (int l=0; l<char_set_size; l++) {
                    s[0] = ' ' + i;
                    s[1] = ' ' + j;
                    s[2] = ' ' + k;
                    s[3] = ' ' + l;

                    //std::cout << char_set_size << " " << i << " " << j << " " << k << " " << l << "\n";
                    if(0 == p.getSubCount(s)) {
                        std::cout << "ERROR! [";
                        for (int _=0; _<4; _++) {
                            std::cout << (int)s[_] << " ";
                        }

                        std::cout << "]\n";
                    }
                }
            }
        }
    }
}
