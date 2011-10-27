#!/bin/sh
cd ..
make clean
make tests TARGET=STATION TEST=1
./bin/problem_data_tests
./bin/algorithm_tests
./bin/main_tests