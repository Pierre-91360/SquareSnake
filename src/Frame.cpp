#include "Frame.h"

Frame::Frame(const char title[])
{
    if (SDL_CreateWindowAndRenderer(WIN_WIDTH,WIN_HEIGHT,0,&(this->_window),&(this->_renderer))!=0)
    {
        SDL_ExitWithSDLError("Fail creating window & renderer");
    }
    SDL_SetWindowTitle(this->_window,title);
} 

Frame::~Frame()
{
    SDL_DestroyRenderer(this->_renderer);
    SDL_DestroyWindow(this->_window);
}

void Frame::refreshRender()
{
    SDL_RenderPresent(this->_renderer);
}

void Frame::setColor(int r,int g,int b,int a)
{
    if (SDL_SetRenderDrawColor(this->_renderer,r,g,b,a)!=0)
        SDL_ExitWithSDLError("Fail setting color");
}

void Frame::drawPoint(int x,int y)
{
    if (SDL_RenderDrawPoint(this->_renderer,x,y)!=0)
        SDL_ExitWithSDLError("Fail drawing point");
}

void Frame::drawLine(int x1,int y1,int x2,int y2)
{
    if (SDL_RenderDrawLine(this->_renderer,x1,y1,x2,y2)!=0)
        SDL_ExitWithSDLError("Fail drawing line");
}

void Frame::drawRect(int x,int y,int w,int h)
{
    SDL_Rect r;
    r.x = x; r.y = y; r.w = w; r.h = h;
    if(SDL_RenderDrawRect(this->_renderer,&r)!=0)
        SDL_ExitWithSDLError("Fail drawing rectangle");
}

void Frame::fillRect(int x,int y,int w,int h)
{
    SDL_Rect r;
    r.x = x; r.y = y; r.w = w; r.h = h;
    if(SDL_RenderFillRect(this->_renderer,&r)!=0)
        SDL_ExitWithSDLError("Fail filling rectangle");
}