#!/bin/sh
rm -r ./build ; cmake -S . -B ./build/ ; cmake --build ./build/ -- -j8 ;