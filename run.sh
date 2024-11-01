#!/usr/bin/env bash

set -e

# Test if build dir exists
if [ ! -d "build" ]; then
    cmake -B build
fi

cmake --build build
./build/fp-fault