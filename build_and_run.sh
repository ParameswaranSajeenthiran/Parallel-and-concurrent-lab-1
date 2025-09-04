#!/bin/bash

# Usage: ./build_and_run.sh [num_cores]
# If num_cores is provided, will run the program pinned to that many cores on Ubuntu.

# Default: use all cores
NUM_CORES="$1"

# Create build directory
mkdir -p build
cd build || exit

# Generate build system
cmake ..

# Build the project
cmake --build .

# Determine OS and run the executable
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    if [[ -n "$NUM_CORES" ]]; then
        # Create a comma-separated list of cores: 0,1,2,...
        CORE_LIST=$(seq -s, 0 $((NUM_CORES-1)))
        echo "Running ./Lab with cores: $CORE_LIST"
        taskset -c $CORE_LIST ./Lab
    else
        ./Lab
    fi
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]]; then
    ./Lab.exe
else
    ./Lab
fi
