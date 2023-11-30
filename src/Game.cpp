#include "Game.h"

Game::Game()
{
    this->_frame = new Frame(WIN_TITLE);
    this->_pState = GAME_PLAY;
} 

Game::~Game()
{
    delete this->_frame;
    delete this->_bodyX;
    delete this->_bodyY;
}

void Game::run()
{
    SDL_Event evt;
    bool quit = false;
    this->initGame();
    while (!quit)
    {
        while (SDL_PollEvent(&evt))
        {
            if(evt.type == SDL_QUIT) quit = true;
            else 
            {
                switch (this->_pState)
                {
                case GAME_PLAY:
                    this->eventGamePlay(&evt);
                    break;
                
                case GAME_OVER:
                    this->eventGameOver(&evt);
                    break;
                
                default:
                    break;
                }
            }
        }
        switch (this->_pState)
        {
            case GAME_PLAY:
                this->runGamePlay();
                break;

            case GAME_OVER:
                this->runGameOver();
                break;
        
            default:
                break;
        }
    }
}

void Game::initGame()
{
    this->_direction = NONE;
    this->_isPlaying = true;
    this->_pState = GAME_PLAY;
    this->getRandomSquare(&this->_headX,&this->_headY);
    do
    {
        this->getRandomSquare(&this->_foodX,&this->_foodY);
    } while ((this->_foodX == this->_headX) && (this->_foodY == this->_headY));
    delete this->_bodyX; delete this->_bodyY;
    this->_bodyX = new std::vector<unsigned int>();
    this->_bodyY = new std::vector<unsigned int>();
}

void Game::fillBackground()
{
    this->_frame->setColor(COLOR_BACKGROUND);
    this->_frame->fillRect(0,0,WIN_WIDTH,WIN_HEIGHT);
}

void Game::fillBackgroundGO()
{
    this->_frame->setColor(COLOR_BACKGROUND_GO);
    this->_frame->fillRect(0,0,WIN_WIDTH,WIN_HEIGHT);
}

void Game::drawBoard()
{
    this->fillBackground();
    this->drawSnake();
    this->drawFood();
    this->_frame->refreshRender();
}

void Game::drawSnake()
{
    this->_frame->setColor(COLOR_SNAKE_HEAD);
    this->_frame->fillRect(this->_headX*SQUARE_WIDTH,this->_headY*SQUARE_HEIGHT,SQUARE_WIDTH,SQUARE_HEIGHT);
    this->_frame->setColor(COLOR_SNAKE_BODY);
    for (int i = 0; ((i<this->_bodyX->size())&&(i<this->_bodyY->size())); i++)
    {
        this->_frame->fillRect(
            (*this->_bodyX)[i]*SQUARE_WIDTH,
            (*this->_bodyY)[i]*SQUARE_HEIGHT,
            SQUARE_WIDTH,
            SQUARE_HEIGHT
            );
    }
}

void Game::drawFood()
{
    this->_frame->setColor(COLOR_FOOD);
    this->_frame->fillRect(this->_foodX*SQUARE_WIDTH,this->_foodY*SQUARE_HEIGHT,SQUARE_WIDTH,SQUARE_HEIGHT);
    this->_frame->setColor(COLOR_FOOD_2);
    this->_frame->fillRect(
        this->_foodX*SQUARE_WIDTH + (SQUARE_WIDTH/4),
        this->_foodY*SQUARE_HEIGHT + (SQUARE_HEIGHT/4),
        SQUARE_WIDTH/2,
        SQUARE_HEIGHT/2
    );
}

void Game::getRandomSquare(unsigned int *x, unsigned int *y)
{
    int square = rand() % ((WIN_HEIGHT/SQUARE_HEIGHT)*(WIN_WIDTH/SQUARE_WIDTH));
    *x = square % (WIN_WIDTH/SQUARE_WIDTH);
    *y = square / (WIN_WIDTH/SQUARE_WIDTH);
}

bool Game::isOccupiedBySnake(int x, int y)
{
    if ((this->_headX==x)&&(this->_headY==y))
        return true;
    for (int i = 0; ((i<this->_bodyX->size())&&(i<this->_bodyY->size())); i++)
        if (((*this->_bodyX)[i]==x)&&((*this->_bodyY)[i]==y))
            return true;
    return false;
}

void Game::moveSnake()
{
    switch (this->_direction)
    {
    case NONE:
        break;
    
    case UP: // y--
        if (this->_headY == 0)
        {
            this->gameOver();
        }
        else this->movingTo(this->_headX,this->_headY-1);
        break;

    case RIGHT: // x++
        if (this->_headX >= (WIN_WIDTH/SQUARE_WIDTH-1))
        {
            this->gameOver();
        }
        else this->movingTo(this->_headX+1,this->_headY);
        break;

    case DOWN: // y++
        if (this->_headY >= (WIN_HEIGHT/SQUARE_HEIGHT-1))
        {
            this->gameOver();
        }
        else this->movingTo(this->_headX,this->_headY+1);
        break;

    case LEFT: // x--
        if (this->_headX == 0)
        {
            this->gameOver();
        }
        else this->movingTo(this->_headX-1,this->_headY);
        break;

    default:
        break;
    }
}

void Game::movingTo(unsigned int x, unsigned int y)
{
    if(this->isOccupiedBySnake(x,y))
    {
        this->gameOver();
    }
    else if ((x == this->_foodX) && (y == this->_foodY))
    {
        this->_bodyX->push_back(this->_headX);
        this->_bodyY->push_back(this->_headY);
        this->_headX = x;
        this->_headY = y;
        this->moveFood();
    }
    else
    {
        for (int i = 0; ((i<((int)(this->_bodyX->size())-1))&&(i<((int)(this->_bodyY->size())-1))); i++)
        {
            (*this->_bodyX)[i] = (*this->_bodyX)[i+1];
            (*this->_bodyY)[i] = (*this->_bodyY)[i+1];
        }
        if ((this->_bodyX->size()>0)&&(this->_bodyY->size()>0))
        {
            (*this->_bodyX)[this->_bodyX->size()-1] = this->_headX;
            (*this->_bodyY)[this->_bodyY->size()-1] = this->_headY;
        }
        this->_headX = x;
        this->_headY = y;
    }
}

void Game::moveFood()
{
    do
    {
        this->getRandomSquare(&this->_foodX,&this->_foodY);
    } while (this->isOccupiedBySnake(this->_foodX,this->_foodY));
}

void Game::gameOver()
{
    this->_pState = GAME_OVER;
    SDL_Log("GAME OVER, Score : %d",((int)this->_bodyX->size()));
}

void Game::eventGameOver(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
            case SDLK_UP:
            case SDLK_RIGHT:
            case SDLK_DOWN:
            case SDLK_LEFT:
                break;
            default:
                this->initGame();
                break;
        }
        break;
    
    default:
        break;
    }
}

void Game::eventGamePlay(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
            case SDLK_UP:
                this->_direction = UP;
                break;

            case SDLK_RIGHT:
                this->_direction = RIGHT;
                break;

            case SDLK_DOWN:
                this->_direction = DOWN;
                break;

            case SDLK_LEFT:
                this->_direction = LEFT;
                break;

            default:
                break;
        }
        break;
    
    default:
        break;
    }
}

void Game::runGameOver()
{
    this->fillBackgroundGO();
    this->drawSnake();
    this->drawFood();
    this->_frame->setColor(COLOR_SNAKE_GO);
    this->_frame->drawLine(this->_headX*SQUARE_WIDTH,this->_headY*SQUARE_HEIGHT,(this->_headX+1)*SQUARE_WIDTH,(this->_headY+1)*SQUARE_HEIGHT);
    this->_frame->drawLine(this->_headX*SQUARE_WIDTH,(this->_headY+1)*SQUARE_HEIGHT,(this->_headX+1)*SQUARE_WIDTH,this->_headY*SQUARE_HEIGHT);
    this->_frame->setColor(COLOR_SNAKE_GO);
    for (int i = 0; ((i<this->_bodyX->size())&&(i<this->_bodyY->size())); i++)
    {
        this->_frame->drawRect(
            (*this->_bodyX)[i]*SQUARE_WIDTH,
            (*this->_bodyY)[i]*SQUARE_HEIGHT,
            SQUARE_WIDTH,
            SQUARE_HEIGHT
        );
    }
    this->_frame->refreshRender();
}

void Game::runGamePlay()
{
    this->drawBoard();
    if ((this->_lastGameUpdate + UPDATE_PERIOD) <= SDL_GetTicks64())
    {
        this->_lastGameUpdate = SDL_GetTicks64();
        this->moveSnake();
    }
}
