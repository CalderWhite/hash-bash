#include <iostream>
#include <thread>
#include <fstream>

#include <boost/program_options.hpp>

#include "OptimizerOptions.h"
#include "CountTree.h"
#include "Predictor.h"

namespace po = boost::program_options;

int trainCommand(cli_options::Training opts) {
    std::ifstream infile(opts.filename);
    CountTree p(opts.char_set_size, opts.block_size, opts.start_char); 

    if (infile.is_open()) {
        std::cout << "Processing data...\n";
        p.ingestFileMultiThread(infile, opts.threads);

        infile.close();
    } else {
        std::cerr << "ERROR: Unable to open file [" << opts.filename << "].\n";
        return 1;
    }

    std::cout << "Generating Predictor...\n";

    Predictor pred(opts.char_set_size, opts.block_size);
    pred.genFromCountTree(p);

    std::cout << "Writing out compressed stream...\n";
    pred.serializeToFile(opts.outfile);

    return 0;
}

void printMissing(std::string arg, std::string sub_cmd) {
    std::cout << "ERROR! Required argument [ --" << arg << " ] is missing!\n"
        "For usage, run: optimizer " << sub_cmd << " --help\n";
}

void printHelp(po::options_description desc) {
    std::cout << desc << "\n";
}

int main(int argc, char* argv[]) {
    po::options_description desc("Optimizer Cli");

    desc.add_options()
        ("help", "Print all options")
        ("command", po::value<std::string>(), "command to execute"),
        ("subargs", po::value<std::vector<std::string>>(), "Arguments for command");

    po::positional_options_description pos;
    pos.add("command", 1).
        add("subargs", -1);

    po::variables_map vm;

    po::parsed_options parsed = po::command_line_parser(argc, argv).
        options(desc).
        positional(pos).
        allow_unregistered().
        run();

    po::store(parsed, vm);

    if (argc < 2) {
        printHelp(desc);
        return 1;
    }

    std::string cmd = vm["command"].as<std::string>();

    if (cmd == "train") {
        // ls command has the following options:
        po::options_description train_desc("Training Options");
        cli_options::Training opts_out;

        train_desc.add_options()
            ("help", "")
            ("filename", po::value<std::string>(&(opts_out.filename)), "The text file to process")
            ("outfile", po::value<std::string>(&(opts_out.outfile))->default_value("trained.dat"), "The filename to write the Predictor to.")
            ("threads", po::value<int>(&(opts_out.threads))->default_value(std::thread::hardware_concurrency()), "The number of threads to use.")
            ("block_size", po::value<int>(&(opts_out.block_size))->default_value(4), "The character depth of the Predictor.")
            ("char_set_size", po::value<int>(&(opts_out.char_set_size))->default_value(95),
            "How many characters in your set. char_set_size + start_char should not exceed 127 due to ascii limits.")
            ("start_char", po::value<char>(&(opts_out.start_char))->default_value(' '), "The first character in your charset. This must be an ascii character.");

        // Collect all the unrecognized options from the first pass. This will include the
        // (positional) command name, so we need to erase that.
        std::vector<std::string> opts = po::collect_unrecognized(parsed.options, po::include_positional);
        opts.erase(opts.begin());

        // Parse again...
        po::store(po::command_line_parser(opts).options(train_desc).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            printHelp(train_desc);
            return 1;
        }

        if (vm.count("filename") == 0) {
            printMissing("filename", "train");
            return 1;
        }

        return trainCommand(opts_out);
    } else {
        printHelp(desc);
    }
}
