#! /bin/bash

# I haven't bothered to bazel-ify this. Here is the command
# for an optimized binary

g++ main.cpp sha2.c -std=c++11 -O3 -o cpp_fast
