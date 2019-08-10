#include "utils.h"

long utils::ipow(long base, long exponent) {
    long c = 1;
    for (long i=0; i<exponent; i++) {
        c *= base;
    }

    return c;
}
