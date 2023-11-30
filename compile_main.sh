#!/bin/bash

proj_path=$(dirname $(readlink -f "$0"))/
g++ "$proj_path"src/*.cpp -o "$proj_path"out/game $(sdl2-config --cflags --libs)
