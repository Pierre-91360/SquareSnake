#include <iostream>
#include "Game.h"

int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));
    SDL_Initialisation();
    Game *game = new Game();
    game->run();
    delete game;
    SDL_End();
	return 0;
}
