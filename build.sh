#!/bin/sh

OPT_LVL=-Ofast

mkdir -p out
c++ $OPT_LVL -std=c++14 simulator.cpp main.cpp -o out/main
