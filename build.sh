#!/bin/bash


# build without installation
set -e

mkdir -p build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release

make -j$(nproc)

