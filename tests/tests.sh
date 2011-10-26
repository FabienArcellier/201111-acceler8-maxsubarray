#!/bin/sh
cd ..
make clean
make tests TARGET=STATION
./bin/problem_data_tests
./bin/algorithm_tests
./bin/main_tests