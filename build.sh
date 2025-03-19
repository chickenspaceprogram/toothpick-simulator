#!/bin/sh

mkdir -p out
c++ -O3 -std=c++14 simulator.cpp main.cpp -o out/main

