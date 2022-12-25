#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#define XMIN -3*M_PI /*�������� �������*/
#define XMAX 2*M_PI/2
/*��������� ������� �� ������*/
void draw_by_pixels(SDL_Renderer *render, double xmin, double xmax);
/*�������*/
double f(double x)
{
    return tan(x-M_PI/3);
}
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *win = SDL_CreateWindow("y = tan(x-PI/3)", 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (win == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
    if (ren == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    /*�������� �����*/
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    /*������� �������*/
    SDL_RenderClear(ren);
    /*��������� �������*/
    draw_by_pixels(ren, XMIN, XMAX);
    SDL_RenderPresent(ren);
    SDL_Event windowEvent;
    while (true)
    {
        /*��������� �������*/
        if (SDL_PollEvent(&windowEvent))
        {
            /*������� ������*/
            if (windowEvent.key.keysym.sym==SDLK_ESCAPE)
                break;
        }
    }
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
    return 0;
}
void draw_by_pixels(SDL_Renderer *render, double xmin, double xmax)
{
    Sint32 width, height;
    /*������� ������ ������� ��� ���������*/
    SDL_GetRendererOutputSize(render, &width, &height);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    /*������� ����� �� Y*/
    double ymin, ymax;
    /*mx, my- ������� ��������� �� X � Y*/
    double mx=width/fabs(xmin-xmax), my, dx=0.001, x, y;
    Sint16 x0scr, y0scr, xscr, yscr;
    x0scr=floor(-1*xmin*mx);
    y0scr=height/2;
    ymin = ymax = f(xmin);
    for(x=xmin;x<=xmax;x+=dx)
    {
        /*��������� ��������� �� �������*/
        if(cos(x-M_PI/3))
        {
            /*������� ������� ����� �� Y*/
            if(ymin>f(x)&& fabs(f(x))<mx/10)
                ymin = f(x);
            if(ymax<f(x)&& fabs(f(x))<mx/10)
                ymax = f(x);
        };
    };
    /*��������� ������� �� Y*/
    my=height/fabs(ymin-ymax);
    /*����������� ������*/
    for(x=xmin;x<=xmax;x+=dx)
    {
            if(cos(x-M_PI/3))
            {
                y=f(x);
                xscr=x0scr+floor(x*mx);
                yscr=y0scr-floor(y*my);
                SDL_RenderDrawPoint(render, xscr, yscr);
            }
    }
}
