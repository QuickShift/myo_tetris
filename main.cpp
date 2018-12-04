#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#include "common.h"
#include "renderer.h"

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
ProcessInput(game_input* NewInput, game_input* OldInput)
{
    *NewInput = *OldInput;
    SDL_Event Event;

    while(SDL_PollEvent(&Event))
    {
        switch(Event.type)
        {
            case SDL_QUIT:
            {
                return false;
            } break;
            case SDL_KEYDOWN:
            {
                if(Event.key.keysym.sym == SDLK_a)
                {
                    NewInput->TranslateLeft.Down = true;
                }
                if(Event.key.keysym.sym == SDLK_s)
                {
                    NewInput->TranslateDown.Down = true;
                }
                if(Event.key.keysym.sym == SDLK_d)
                {
                    NewInput->TranslateRight.Down = true;
                }
                if(Event.key.keysym.sym == SDLK_LSHIFT)
                {
                    NewInput->RotateLeft.Down = true;
                }
                if(Event.key.keysym.sym == SDLK_SPACE)
                {
                    NewInput->RotateRight.Down = true;
                }
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    NewInput->Back.Down = true;
                }
            } break;
            case SDL_KEYUP:
            {
                if(Event.key.keysym.sym == SDLK_a)
                {
                    NewInput->TranslateLeft.Down = false;
                }
                if(Event.key.keysym.sym == SDLK_s)
                {
                    NewInput->TranslateDown.Down = false;
                }
                if(Event.key.keysym.sym == SDLK_d)
                {
                    NewInput->TranslateRight.Down = false;
                }
                if(Event.key.keysym.sym == SDLK_LSHIFT)
                {
                    NewInput->RotateLeft.Down = false;
                }
                if(Event.key.keysym.sym == SDLK_SPACE)
                {
                    NewInput->RotateRight.Down = false;
                }
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    NewInput->Back.Down = false;
                }
            } break;
        }
    }

    for(u32 i = 0; i < ArrayCount(NewInput->Keys); ++i)
    {
        NewInput->Keys[i].Changed = NewInput->Keys[i].Down == OldInput->Keys[i].Down ? false : true;
    }

    *OldInput = *NewInput;

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

    if(TTF_Init() == -1)
    {
        printf("ERROR: Failed to initialize TTF.\n%s\n", SDL_GetError());
    }

    TTF_Font* Font;
    Font = LoadFont("UbuntuMono.ttf", 50);

    game_input OldInput = {};
    game_input NewInput = {};
    for(;;)
    {
        if(!ProcessInput(&NewInput, &OldInput))
        {
            break;
        }

        if(NewInput.Back.Down)
        {
            break;
        }

        u8 R = NewInput.TranslateLeft.Down ? 255 : 0;
        u8 G = NewInput.TranslateDown.Down ? 255 : 0;
        u8 B = NewInput.TranslateRight.Down ? 255 : 0;
        SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
        SDL_RenderClear(Renderer);

        //GameUpdateAndRender(NewInput);
        u32 TileSize = 20;
        u32 TileCountX = WINDOW_WIDTH / TileSize;
        u32 TileCountY = WINDOW_HEIGHT / TileSize;
        for(u32 i = 0; i < TileCountX; ++i)
        {
            for(u32 j = 0; j < TileCountY; ++j)
            {
                SDL_Rect Rectangle = {};
                Rectangle.x = i * TileSize;
                Rectangle.y = j * TileSize;
                Rectangle.w = TileSize;
                Rectangle.h = TileSize;
                SDL_SetRenderDrawColor(Renderer, R * i / TileCountX, G * i / TileCountX, B * i / TileCountX, 255);
                SDL_RenderFillRect(Renderer, &Rectangle);
                SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(Renderer, &Rectangle);
            }
        }

        SDL_Rect TextRectangle = {};
        SDL_Texture* TextTexture;
        TextTexture = CreateTextTexture(&TextRectangle, Renderer, Font, "Test");
        //SDL_SetTextureBlendMode(TextTexture, SDL_BLENDMODE_BLEND);
        TextRectangle.x = 100;
        TextRectangle.y = 100;

        SDL_RenderCopy(Renderer, TextTexture, NULL, &TextRectangle);

        SDL_DestroyTexture(TextTexture);

        SDL_RenderPresent(Renderer);
        SDL_Delay(FRAME_TIME_MS);
    }

    TTF_Quit();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);

    SDL_Quit();

    return 0;
}
