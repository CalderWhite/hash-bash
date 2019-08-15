#include <iostream>
#include <stdint.h>

#include "utils.h"

int64_t utils::ipow(int64_t base, int64_t exponent) {
    int64_t c = 1;
    for (int64_t i=0; i<exponent; i++) {
        c *= base;
    }

    return c;
}

int utils::binarySearch(int a[], int item, int low, int high) {
    if (high <= low) {
        return (item > a[low]) ?  (low + 1) : low;
    }

    int mid = (low + high)/2;

    if(item == a[mid]) {
        return mid+1;
    }

    if(item > a[mid]) {
        return binarySearch(a, item, mid+1, high);
    }

    return binarySearch(a, item, low, mid-1);
}

void utils::insertionSort(int a[], int n, int cit[]) {
    int i, loc, j, selected;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = a[i];
        char tempC = cit[i];

        loc = binarySearch(a, selected, 0, j);

        while (j >= loc) {
            a[j+1] = a[j];
            cit[j+1] = cit[j];
            j--;
        }
        a[j+1] = selected;
        cit[j+1] = tempC;
    }
}
