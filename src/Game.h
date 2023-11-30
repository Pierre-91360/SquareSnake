#ifndef GAME
#define GAME

#include <cstdlib>
#include <vector>
#include "Frame.h"

enum Direction
{
    NONE, UP, RIGHT, DOWN, LEFT
};

enum Prog_State
{
    GAME_OVER, GAME_PLAY
};

class Game
{
    private:

    Frame *_frame = NULL;
    bool _isPlaying = false;
    unsigned int _headX = 0;
    unsigned int _headY = 0;
    std::vector<unsigned int> *_bodyX = NULL;
    std::vector<unsigned int> *_bodyY = NULL;
    Direction _direction = NONE;
    Prog_State _pState;
    unsigned int _foodX = 0;
    unsigned int _foodY = 0;
    Uint64 _lastGameUpdate = 0;

    public:

    Game(); // Constructor
    ~Game(); // Destructeur
    void run();

    private:

    void initGame();
    void fillBackground();
    void fillBackgroundGO();
    void drawBoard();
    void drawSnake();
    void drawFood();
    void getRandomSquare(unsigned int *x,unsigned int *y);
    bool isOccupiedBySnake(int x,int y);
    void moveSnake();
    void movingTo(unsigned int x,unsigned int y);
    void moveFood();
    void gameOver();
    void eventGameOver(SDL_Event *event);
    void eventGamePlay(SDL_Event *event);
    void runGameOver();
    void runGamePlay();
};

#endif
