#include <SDL2/SDL.h>
#include <stdio.h>

#include "common.h"

static b32
Init(SDL_Window** Window, SDL_Renderer** Renderer)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL_Init failed!\nERROR: %s\n", SDL_GetError());
        return false;
    }

    *Window = SDL_CreateWindow("Myo Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if(!*Window)
    {
        printf("SDL_CreateWindow failed!\nERROR: %s\n", SDL_GetError());
        return false;
    }

    *Renderer = SDL_CreateRenderer(*Window, -1, SDL_RENDERER_ACCELERATED);

    if(!*Renderer)
    {
        printf("SDL_CreateRenderer failed!\nERROR: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

static b32
ProcessInput()
{
    SDL_Event Event;

    while(SDL_PollEvent(&Event))
    {
        if(Event.type == SDL_QUIT)
        {
            return false;
        }
    }

    return true;
}

int
main(int ArgCount, char** Args)
{
    Platform::SetHighDPIAwareness();

    SDL_Window* Window = 0;
    SDL_Renderer* Renderer = 0;

    if(!Init(&Window, &Renderer))
    {
        return -1;
    }

    for(;;)
    {
        SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
        SDL_RenderClear(Renderer);

        if(!ProcessInput())
        {
            break;
        }

        //GameUpdateAndRender();
        SDL_RenderPresent(Renderer);
        SDL_Delay(FRAME_TIME_MS);
    }

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);

    SDL_Quit();

    return 0;
}
