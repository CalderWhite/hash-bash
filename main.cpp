#include <cstring>
#include <chrono>
#include <iostream>
#include <math.h>

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

std::chrono::high_resolution_clock::time_point get_time() {
    return std::chrono::high_resolution_clock::now();
}

long long get_diff(
    std::chrono::high_resolution_clock::time_point t1,
    std::chrono::high_resolution_clock::time_point t2) {
    return std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
}

const char* POSSIBLE_CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const int POSSIBLE_CHAR_COUNT = strlen(POSSIBLE_CHARS);
int HASH_LENGTH;

void find_all(const char* hash, int current_char, const char current[]) {
    if ((current_char == HASH_LENGTH)) {
        if ((strncmp(hash, current, HASH_LENGTH) == 0)) {
        }
    } else {
        for (int i=0; i<POSSIBLE_CHAR_COUNT; i++) {
            char new_str[HASH_LENGTH];
            strncpy(new_str, current, HASH_LENGTH);

            new_str[current_char] = POSSIBLE_CHARS[i];

            find_all(hash, current_char + 1, new_str); 
        }
    }
}

int main_test(int argc, char** args) {
    if (argc < 2) {
        std::cerr << "Error! No hash provided.\n";
        return 1;
    }

    HASH_LENGTH = strlen(args[1]);
    const char* hash = args[1];
    const char blank[HASH_LENGTH] = {};

    auto start_time = get_time();
    find_all(hash, 0, blank);

    auto stop_time = get_time();
    long long duration = get_diff(start_time, stop_time);

    std::cout << std::fixed;
    std::cout << duration << "\u03BCs elapsed.\n";

    float seconds = duration / 1000000.0;
    long long permutations = std::pow(POSSIBLE_CHAR_COUNT, HASH_LENGTH);
    std::cout << permutations / seconds << " attempts per second.\n";

    return 0;
}

int main(int argc, char** args) {

    HASH_LENGTH = strlen(args[1]);
    const char* hash = args[1];
    const char blank[HASH_LENGTH] = {};

    for (int i=0; i<1000; i++) {
        auto start_time = get_time();
        find_all(hash, 0, blank);

        auto stop_time = get_time();
        long long duration = get_diff(start_time, stop_time);
        std::cout << duration << "\n";
    }
}
