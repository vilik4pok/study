#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "classes.h"
using namespace std;
#define FULLSCREEN 0
#define DEFAULTWIDTH 500
#define DEFAULTHEIGHT 500

int main(int argc, char *argv[])
{

    setlocale(LC_ALL, "rus");
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
    {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        return 1;
    }
/*если запускается в оконном режиме, то получаем координаты, чтобы окно было по центру*/
    int windowPosX = displayMode.w/2-DEFAULTWIDTH/2,windowPosY = displayMode.h/2-DEFAULTHEIGHT/2;
/*создаем окно*/
    window = SDL_CreateWindow("Game",   windowPosX*!FULLSCREEN,
                                        windowPosY*!FULLSCREEN,
                                        DEFAULTWIDTH*!FULLSCREEN,
                                        DEFAULTWIDTH*!FULLSCREEN,
                                        SDL_WINDOW_FULLSCREEN_DESKTOP*FULLSCREEN);
/*проверка инициализации*/
    if (window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (TTF_Init() != 0)
    {
        std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
        return 1;
    }
    IMG_Init(IMG_INIT_PNG);
/*получаем размер полотна окна*/
    SDL_GL_GetDrawableSize(window, &windowWidth, &windowHeight);
    Game game;
    game.run();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}
