#!/bin/bash

g++ -fpic -shared game/*.cpp -I ./game -lSDL3 -o game.so
