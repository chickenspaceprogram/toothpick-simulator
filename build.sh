#!/bin/sh

OPT_LVL=-O3

mkdir -p out
c++ $OPT_LVL -std=c++14 simulator.cpp main.cpp -o out/main
