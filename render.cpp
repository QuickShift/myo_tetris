#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "common.h"
#include "text.h"

struct game_state
{
    b32 IsInit;

    TTF_Font* Font;
};

GAME_UPDATE_AND_RENDER(GameUpdateAndRender)
{
    Assert(GameMemory.IsInit);
    // INIT
    game_state* GameState = (game_state*)GameMemory.Memory;
    if(!GameState->IsInit)
    {
        GameState->IsInit = true;

        GameState->Font = LoadFont("UbuntuMono.ttf", 50);
    }

    // UPDATE

    // RENDER
    u32 R = Input.TranslateLeft.Down ? 255 : 0;
    u32 G = Input.TranslateDown.Down ? 255 : 0;
    u32 B = Input.TranslateRight.Down ? 255 : 0;

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
    TextTexture = CreateTextTexture(&TextRectangle, Renderer, GameState->Font, "Test");
    //SDL_SetTextureBlendMode(TextTexture, SDL_BLENDMODE_BLEND);
    TextRectangle.x = 100;
    TextRectangle.y = 100;

    SDL_RenderCopy(Renderer, TextTexture, NULL, &TextRectangle);

    SDL_DestroyTexture(TextTexture);
}
