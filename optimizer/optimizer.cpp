#include <iostream>
#include <fstream>
#include <chrono>

#include <boost/multiprecision/cpp_int.hpp>

#include "Predictor.h"
#include "PredictorCounter.h"

const long BLOCK_SIZE = 4;
const long CHAR_SET_SIZE = 95;

std::chrono::high_resolution_clock::time_point getTime() {
    return std::chrono::high_resolution_clock::now();
}

int64_t getTimeDiff(
    std::chrono::high_resolution_clock::time_point t1,
    std::chrono::high_resolution_clock::time_point t2) {
    return std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
}

struct my_numpunct : std::numpunct<char> {
  std::string do_grouping() const {return "\03";}
};

int main(int argc, char** argv) {
    Predictor pred(CHAR_SET_SIZE, BLOCK_SIZE);
    pred.deserializeFromFile("/home/cwhite/test/hash-bash/optimizer/trained.dat.gz");

    std::ifstream in("/home/cwhite/test/hash-bash/data/crackstation-human-only.txt");

    // init 20 counters to be used for the various lengths of the passwords
    std::vector<PredictorCounter> counters;
    for (int i=0; i<21; i++) {
        counters.emplace_back(pred, i, 1);
    }

    // pretty printing large numbers
    /*
    std::locale loc (std::cout.getloc(),new my_numpunct);
    std::cout.imbue(loc);
    */

    const int agg_groups = 20;
    const int static_length = 8;
    const mp::int128_t max_offset = mp::pow(mp::int128_t(CHAR_SET_SIZE), static_length);
    const mp::int128_t odiv = max_offset / agg_groups;
    int agg[agg_groups] = {0};

    if (in.is_open()) {
        std::string line;

        int pwd_count = 0;
        int loop_count = 0;
        while (getline(in, line)) {
            ++loop_count;
            //if (line.length() < 4 || line.length() > 20) continue;
            if (line.length() != static_length) continue;

            bool skip = false;
            for (int i=0; i<line.length(); i++) {
                if (line[i] < 32) {
                    skip = true;
                }
            }

            if (skip) continue;

            mp::int128_t offset = counters[line.length()].getOffset(line.c_str());

            ++agg[static_cast<int>(offset / odiv)];

            ++pwd_count;

            if (loop_count % 100000 == 0) {
                std::cout << "Passwords: " << std::setw(9) << pwd_count
                    << " Total Pwds: " << std::setw(9) << loop_count << "\n";
            }
        }

        std::cout << "Report:\n--------------------\n";
        for (int i=0; i<agg_groups; i++) {
            //std::cout << std::setw(20) << odiv*i << " - " << std::setw(20) <<
            //    odiv*(i+1) << " " << std::setw(12) << agg[i] << "\n";
            std::cout << odiv*i << ", " << odiv*(i+1) << ", " << agg[i] << "\n";
        }
    } else {
        std::cerr << "Error opening data file.\n";
        return 1;
    }
}
