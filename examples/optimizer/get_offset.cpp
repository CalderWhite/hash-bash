#include <iostream>
#include <fstream>
#include <chrono>

#include <boost/multiprecision/cpp_int.hpp>

#include "Predictor.h"
#include "PredictorCounter.h"

/**
 * Apologies, this code isn't well documented.
 * This was used to generate the data for researching the effectiveness of the
 * optimizer or various plaintext password datasets using one of my trained models.
 *
 * This has to be built with bazel then run in the root directory of the repo.
 * This is because bazel, by design, does not allow workspace modification.
 * So, if you bazel run the cc_binary you will not find your output in your current directory.
 */

// these should be the same as the trained model you supply
const long BLOCK_SIZE = 4;
const long CHAR_SET_SIZE = 95;

// set to true to see what it would be like if a naive brute force was used.
const bool USE_BAD = false;

struct my_numpunct : std::numpunct<char> {
  std::string do_grouping() const {return "\03";}
};

int main(int argc, char** argv) {
    Predictor pred(CHAR_SET_SIZE, BLOCK_SIZE);
    pred.deserializeFromFile("trained.dat.gz");

    std::ifstream in("data/crackstation-human-only.txt");
    //std::ifstream in("data/rockyou.txt");
    std::ofstream outfile("crackstation_bad_control_1000.csv");

    // pretty printing large numbers
    std::locale loc (std::cout.getloc(),new my_numpunct);
    std::cout.imbue(loc);

    const int agg_groups = 999;
    const int max_length = 20;
    int agg[agg_groups] = {0};

    // init 20 counters to be used for the various lengths of the passwords
    std::vector<PredictorCounter> counters;
    for (int i=0; i<max_length; i++) {
        counters.emplace_back(pred, i, 1);
    }

    mp::int128_t max_o[max_length] = {0};
    for (int i=0; i<max_length; i++) {
        max_o[i] = mp::pow(mp::int128_t(CHAR_SET_SIZE), i);
    }

    if (in.is_open()) {
        std::string line;

        int pwd_count = 0;
        int loop_count = 0;
        while (getline(in, line)) {
            ++loop_count;
            if (line.length() < 4 || line.length() >= max_length) continue;

            bool skip = false;
            for (int i=0; i<line.length(); i++) {
                if (line[i] < 32) {
                    skip = true;
                }
            }

            if (skip) continue;

            mp::int128_t offset;
            if (USE_BAD) {
                offset = counters[line.length()].getBadOffset(line.c_str());
            } else {
                offset = counters[line.length()].getOffset(line.c_str());
            }

            mp::int128_t odiv = max_o[line.length()] / agg_groups;
            int index = static_cast<int>(offset / odiv);

            ++agg[index];
            ++pwd_count;

            if (loop_count % 100000 == 0) {
                std::cout << "Passwords: " << std::setw(9) << pwd_count
                    << " Total Pwds: " << std::setw(9) << loop_count << "\n";
            }
        }

        outfile << std::setprecision(9);

        double sum = 0;
        for (int i=0; i<agg_groups; i++) {
            sum += agg[i];
            outfile << (i+1)*1.0/agg_groups << ", " << sum/pwd_count << "\n";
        }

        outfile.close();
    } else {
        std::cerr << "Error opening data file.\n";
        return 1;
    }
}
