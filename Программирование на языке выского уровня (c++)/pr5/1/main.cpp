#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#define XMIN -3*M_PI /*диапозон графика*/
#define XMAX 2*M_PI/2
/*отрисовка графика по точкам*/
void draw_by_pixels(SDL_Renderer *render, double xmin, double xmax);
/*функция*/
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
    /*устанока цвета*/
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    /*очистка рендера*/
    SDL_RenderClear(ren);
    /*отрисовка графика*/
    draw_by_pixels(ren, XMIN, XMAX);
    SDL_RenderPresent(ren);
    SDL_Event windowEvent;
    while (true)
    {
        /*обработка событий*/
        if (SDL_PollEvent(&windowEvent))
        {
            /*событие выхода*/
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
    /*находим размер области для рисования*/
    SDL_GetRendererOutputSize(render, &width, &height);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    /*крайние точки по Y*/
    double ymin, ymax;
    /*mx, my- масштаб отрисовки по X и Y*/
    double mx=width/fabs(xmin-xmax), my, dx=0.001, x, y;
    Sint16 x0scr, y0scr, xscr, yscr;
    x0scr=floor(-1*xmin*mx);
    y0scr=height/2;
    ymin = ymax = f(xmin);
    for(x=xmin;x<=xmax;x+=dx)
    {
        /*проверяем определен ли тангенс*/
        if(cos(x-M_PI/3))
        {
            /*находим крайние точки по Y*/
            if(ymin>f(x)&& fabs(f(x))<mx/10)
                ymin = f(x);
            if(ymax<f(x)&& fabs(f(x))<mx/10)
                ymax = f(x);
        };
    };
    /*вычисляем масштаб по Y*/
    my=height/fabs(ymin-ymax);
    /*отрисовывем график*/
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
