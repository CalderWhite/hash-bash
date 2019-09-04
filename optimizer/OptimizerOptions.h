#pragma once
#include <string>

namespace cli_options {

struct Training {
    std::string filename;
    std::string outfile;
    int threads;
    int block_size;
    int char_set_size;
    char start_char;
};

} // namespace cli_options
