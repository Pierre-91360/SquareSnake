#include "SDL_Manager.h"

void SDL_Initialisation()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithSDLError("Fail initializing SDL");
    }
    
}

void SDL_End() { SDL_Quit(); }
void SDL_Sleep(unsigned int msTime) { SDL_Delay(msTime); }

void SDL_ExitWithSDLError(const char errorMsg[])
{
    SDL_Log("%s : %s\n",errorMsg,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
