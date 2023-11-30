# SquareSnake

This program written in C++ is a Snake-type game by using SDL2 library.

## Prerequisites

The game is intended to be run on Linux systems.
Moreover C/C++ library SDL2 and C++ compiler g++ have to be installed on the system.

## Launching

Once the project pulled, open the terminal at the root.
Execute compile_main.sh file (command line is ./compile_main.sh) to build the project.
The executable binary file is created in the /out directory as the name game.
In order to execute the game, just run this file (command line is ./out/game).

## How to play

Once launched, the progam opens a 800*600 pixels window and a game starts.
Snake's head is represented by a blue square, food is represented by a red and green square ans Snake's body is represented by black square.
The snake begins to move as of the player presses any arrow key and stops to move when it collides with an window edge or it's own body which makes the game over.
When snake's head collides food, its body size raises by 1 square.
When the game is over, background turns to gray and to start a new game, the player has to press any key other than the arrow keys.