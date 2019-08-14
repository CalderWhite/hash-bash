#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <chrono>

const long ARR_SIZE = 95;
const long NUM_ARRS = 866496;
const long MIN = 0;
//const long MAX = 2147483648;
const long MAX = 1e4;

std::chrono::high_resolution_clock::time_point getTime() {
    return std::chrono::high_resolution_clock::now();
}

long long getTimeDiff(
    std::chrono::high_resolution_clock::time_point t1,
    std::chrono::high_resolution_clock::time_point t2) {
    return std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
}

int binarySearch(int a[], int item, int low, int high) {
    if (high <= low) {
        return (item > a[low])?  (low + 1): low;
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

// Function to sort an array a[] of size 'n'
void insertionSort(int a[], int n) {
    int i, loc, j, selected;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = a[i];

        // find location where selected sould be inseretd
        loc = binarySearch(a, selected, 0, j);

        // Move all elements after location to create space
        while (j >= loc) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = selected;
    }
}

void genRandom(int** start) {
    // lol just moved this code out. Rip good code.
    srand (time(NULL));

    for (int i=0; i<NUM_ARRS; i++) {
        for (int j=0; j<ARR_SIZE; j++) {
            start[i][j] = rand() % MAX;
            //std::cout << arrays[i][j] << "\n";
        }
    }
}

int main() {

    std::cout << "Building array at runtime because Calder is lazy...\n";
    int** arrays = new int*[NUM_ARRS];
    for (int i=0; i<NUM_ARRS; i++) {
        arrays[i] = new int[ARR_SIZE]();
    }

    genRandom(arrays);

    std::cout << "Running sorting bench...\n";

    const long offset = sizeof(long)*ARR_SIZE;
    auto t1 = getTime();
    for (int i=0; i<NUM_ARRS; i++) {
        std::sort(arrays[i], arrays[i] + offset);
    }
    auto t2 = getTime();
    std::cout << getTimeDiff(t1, t2)/1e6 << "\n";

    std::cout << "Regenerating randoms....\n";
    genRandom(arrays);

    std::cout << "Running second sorting bench...\n";

    t1 = getTime();
    for (int i=0; i<NUM_ARRS; i++) {
        insertionSort(arrays[i], ARR_SIZE);
    }
    t2 = getTime();
    std::cout << getTimeDiff(t1, t2)/1e6 << "\n";
}
