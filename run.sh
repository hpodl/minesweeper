#!/bin/sh

mkdir -p build
cmake -B build
cd build
rm ./Minesweeper
make
make test
./Minesweeper
