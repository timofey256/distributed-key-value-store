#!/bin/bash

if ! command -v cmake &> /dev/null; then
    echo "DEPENDENCY ERROR:"
    echo "cmake not found. Please install cmake first:"
    echo "You can use our tools under 'src/tools/dependencies'"
    echo ""
    echo "Or, alternatively, install it yourself:"
    echo "Ubuntu/Debian: sudo apt-get install cmake"
    echo "Fedora: sudo dnf install cmake"
    echo "Mac: brew install cmake"
    exit 1
fi

if ! command -v g++ &> /dev/null; then
    echo "DEPENDENCY ERROR:"
    echo "g++ not found. Please install C++ compiler first:"
    echo "You can use our tools under 'src/tools/dependencies'"
    echo ""
    echo "Or, alternatively, install it yourself:"
    echo "Ubuntu/Debian: sudo apt-get install build-essential"
    echo "Fedora: sudo dnf install gcc-c++"
    echo "Mac: xcode-select --install"
    exit 1
fi

cd ../src/
mkdir build
cd build
cmake ..
make