#include <iostream>
#include "Game.h"

int main(int argc, char *argv[])
{
    SDL_version version;
    SDL_VERSION(&version);
    srand((unsigned int)time(NULL));
    SDL_Initialisation();
    Game *game = new Game();
    game->run();
    delete game;
    SDL_End();
	return 0;
}
