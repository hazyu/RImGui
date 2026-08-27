#!/bin/bash

g++ $(find src -type f -iname *.cpp -print) -I src -lSDL3 -lSDL3_image -o game
