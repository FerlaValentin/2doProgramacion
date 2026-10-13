#!/bin/sh

# Example script to build a program with the ESAT graphic library for 
# macOS 64bit systems.
#
# This script compiles all .cc files found at the ../src/ directory and links 
# them with the libESAT library and all its dependencies (e.g: Cocoa, IOKit,
# Corevideo, OpenGL, etc...).
#
# Standard ESAT C++ project structure with standard directory names is 
# assumed (src, include, deps . . .)

rm -f test_d test *.o

# Debug configuration

clang++ -g -m64 -std=c++11 -I../include -I../deps/ESAT/include/ -c ../src/main.cc 
clang++ -g -m64 -std=c++11 -L../deps/ESAT/bin/macos64 -lESAT -framework OpenGL -framework Cocoa -framework Corevideo -framework IOKit -framework AudioToolbox main.o -o test_d

# Release configuration

clang++ -O2 -m64 -std=c++11 -I../include -I../deps/ESAT/include/ -c ../src/main.cc 
clang++ -O2 -m64 -std=c++11 -L../deps/ESAT/bin/macos64 -l ESAT -framework OpenGL -framework Cocoa -framework Corevideo -framework IOKit -framework AudioToolbox main.o -o test

