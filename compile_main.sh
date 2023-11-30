#!/bin/bash

proj_path=$(dirname $(readlink -f "$0"))/
if [ ! -d "$proj_path"/out ]; then
    mkdir "$proj_path"/out
fi
g++ "$proj_path"src/*.cpp -o "$proj_path"out/game $(sdl2-config --cflags --libs)
