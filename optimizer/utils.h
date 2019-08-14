#pragma once

namespace utils {
    /**
     * Util function. Returns the base^exponent for integers only.
     */
    long ipow(long base, long exponent);


    /**
     * Binary search implementation.
     */
    int binarySearch(int a[], int item, int low, int high);

    /**
     * In-place binary insertion sort for array a of length n.
     * Moves the values in index_tracker according to the values in a.
     * This way if you have certain items in a that correspond to other values initially, they can be
     * found at the end of the sorting when all the indicies have been changed.
     */
    void insertionSort(int a[], int n, int index_tracker[]);

} // namespace utils
