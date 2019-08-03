#include <chrono>
#include <cstring>
#include <iostream>
#include <math.h>

#include "sha2.h"

const char* POSSIBLE_CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const int POSSIBLE_CHAR_COUNT = strlen(POSSIBLE_CHARS);
const int SAMPLE_SIZE = 3;
int PLAINTEXT_LENGTH;

std::chrono::high_resolution_clock::time_point getTime() {
    return std::chrono::high_resolution_clock::now();
}

long long getTimeDiff(
    std::chrono::high_resolution_clock::time_point t1,
    std::chrono::high_resolution_clock::time_point t2) {
    return std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
}

void findAllPermutations(const unsigned char* hash, int current_char, unsigned char current[], unsigned char digest[]) {
    if (current_char == PLAINTEXT_LENGTH) {
	sha256(current, PLAINTEXT_LENGTH, digest);

	if (memcmp(hash, digest, 32) == 0) {
	    std::cout << "Match!\n";
	}
    } else {
        for (int i=0; i<POSSIBLE_CHAR_COUNT; i++) {
            current[current_char] = POSSIBLE_CHARS[i];

            findAllPermutations(hash, current_char + 1, current, digest); 
        }
    }
}

int main(int argc, char** args) {

    if (argc < 2) {
        std::cerr << "Error! No hash provided.\n";
        return 1;
    }


    PLAINTEXT_LENGTH = strlen(args[1]);

    // calculate the hash of the input string
    const unsigned char* plaintext = reinterpret_cast<const unsigned char *>(args[1]);
    unsigned char hash[32] = {0};
    sha256(plaintext, PLAINTEXT_LENGTH, hash);

    // avoid re allocating memory by defining these here
    unsigned char blank[PLAINTEXT_LENGTH] = {0};
    unsigned char blank_digest[32] = {0};

    long long sum = 0;
    for (int i=0; i<SAMPLE_SIZE; i++) {
        auto start_time = getTime();
        findAllPermutations(hash, 0, blank, blank_digest);

        auto stop_time = getTime();
        long long duration = getTimeDiff(start_time, stop_time);
        std::cout << duration << "\n";
        sum += duration;
    }

    sum /= SAMPLE_SIZE;

    float seconds = sum / 1000000.0;
    long long permutations = std::pow(POSSIBLE_CHAR_COUNT, PLAINTEXT_LENGTH);

    std::cout << "Averaged hashed permutations per second: " << permutations / seconds << "\n";
}
