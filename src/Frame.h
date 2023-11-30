#ifndef FRAME
#define FRAME

#include "SDL_Manager.h"

class Frame
{
    private:

    SDL_Window *_window = NULL;
    SDL_Renderer *_renderer = NULL;

    public:

    Frame(const char title[]);
    ~Frame();
    void refreshRender();
    void setColor(int r,int g,int b,int a);
    void drawPoint(int x,int y);
    void drawLine(int x1,int y1,int x2,int y2);
    void drawRect(int x,int y,int w,int h);
    void fillRect(int x,int y,int w,int h);
};

#endif
