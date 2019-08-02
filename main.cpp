#include <chrono>
#include <cstring>
#include <iostream>
#include <math.h>

const char* POSSIBLE_CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const int POSSIBLE_CHAR_COUNT = strlen(POSSIBLE_CHARS);
int HASH_LENGTH;

std::chrono::high_resolution_clock::time_point getTime() {
    return std::chrono::high_resolution_clock::now();
}

long long getTimeDiff(
    std::chrono::high_resolution_clock::time_point t1,
    std::chrono::high_resolution_clock::time_point t2) {
    return std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
}

void findAllPermutations(const char* hash, int current_char, const char current[]) {
    if (current_char == HASH_LENGTH) {
        if (strncmp(hash, current, HASH_LENGTH) == 0) {
        }
    } else {
        char new_str[current_char + 1];
        for (int i=0; i<POSSIBLE_CHAR_COUNT; i++) {
            // Better preformance was found with a loop instead of:
            // strncpy(new_str, current, current_char);
            for (int j=0; j<current_char; j++) {
                new_str[j] = current[j];
            }

            new_str[current_char] = POSSIBLE_CHARS[i];

            findAllPermutations(hash, current_char + 1, new_str); 
        }
    }
}

int main(int argc, char** args) {

    if (argc < 2) {
        std::cerr << "Error! No hash provided.\n";
        return 1;
    }

    /*
    HASH_LENGTH = strlen(args[1]);
    const char* hash = args[1];
    const char blank[HASH_LENGTH] = {};

    auto start_time = getTime();
    findAllPermutations(hash, 0, blank);

    auto stop_time = getTime();
    long long duration = getTimeDiff(start_time, stop_time);

    std::cout << std::fixed;
    std::cout << duration << "\u03BCs elapsed.\n";

    float seconds = duration / 1000000.0;
    long long permutations = std::pow(POSSIBLE_CHAR_COUNT, HASH_LENGTH);
    std::cout << permutations / seconds << " attempts per second.\n";
    */

    HASH_LENGTH = strlen(args[1]);
    const char* hash = args[1];
    const char blank[HASH_LENGTH] = {};

    long long sum = 0;
    int sample_size = 10;

    for (int i=0; i<sample_size; i++) {
        auto start_time = getTime();
        findAllPermutations(hash, 0, blank);

        auto stop_time = getTime();
        long long duration = getTimeDiff(start_time, stop_time);
        std::cout << duration << "\n";
        sum += duration;
    }

    sum /= sample_size;

    float seconds = sum / 1000000.0;
    long long permutations = std::pow(POSSIBLE_CHAR_COUNT, HASH_LENGTH);

    std::cout << "Averaged permutations per second: " << permutations / seconds << "\n";
}
