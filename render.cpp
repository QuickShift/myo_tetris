#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "common.h"
#include "text.h"

#define STRING_LENGTH 50

struct v4
{
    float R;
    float G;
    float B;
    float A;
};

enum scene
{
    SCENE_Menu,
    SCENE_Info,
    SCENE_Game,

    SCENE_Count,
};

struct menu_scene
{
    v4 BackgroundColor;

    v4 GameColor;
    v4 InfoColor;

    SDL_Rect GameRectangle;
    SDL_Rect InfoRectangle;
};

struct game_state
{
    b32 IsInit;

    TTF_Font* Font;

    u32 TileSize;
    u32 TileCountX;
    u32 TileCountY;

    scene CurrentScene;

    menu_scene Menu;
};

void
DrawBackground(v4 Color, SDL_Renderer* Renderer)
{
    SDL_SetRenderDrawColor(Renderer, Color.R, Color.G, Color.B, Color.A);
    SDL_RenderClear(Renderer);
}

void
DrawTextQuad(char* Text, TTF_Font* Font, v4 Color, SDL_Rect Rectangle, SDL_Renderer* Renderer)
{
    SDL_SetRenderDrawColor(Renderer, Color.R, Color.G, Color.B, Color.A);
    SDL_RenderFillRect(Renderer, &Rectangle);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(Renderer, &Rectangle);

    SDL_Rect TextRectangle = {};
    SDL_Texture* TextTexture = CreateTextTexture(&TextRectangle, Renderer, Font, Text);

    TextRectangle.x = Rectangle.x + (Rectangle.w - TextRectangle.w) / 2.0f;
    TextRectangle.y = Rectangle.y + (Rectangle.h - TextRectangle.h) / 2.0f;

    SDL_RenderCopy(Renderer, TextTexture, NULL, &TextRectangle);

    SDL_DestroyTexture(TextTexture);
}

GAME_UPDATE_AND_RENDER(GameUpdateAndRender)
{
    Assert(GameMemory.IsInit);
    // INIT
    game_state* GameState = (game_state*)GameMemory.Memory;
    if(!GameState->IsInit)
    {
        GameState->IsInit = true;

        GameState->Font = LoadFont("UbuntuMono.ttf", 50);

        GameState->TileSize = 20;
        GameState->TileCountX = WINDOW_WIDTH / GameState->TileSize;
        GameState->TileCountY = WINDOW_HEIGHT / GameState->TileSize;

        GameState->CurrentScene = SCENE_Menu;

        // MENU
        {
            GameState->Menu.BackgroundColor = v4{ 100.0f, 100.0f, 100.0f, 255.0f };
            GameState->Menu.GameColor = v4{ 150.0f, 0.0f, 0.0f, 255.0f };
            GameState->Menu.InfoColor = v4{ 0.0f, 100.0f, 100.0f, 255.0f };

            SDL_Rect GameRectangle = {};
            GameRectangle.x = 400;
            GameRectangle.y = 300;
            GameRectangle.w = 200;
            GameRectangle.h = 100;
            GameState->Menu.GameRectangle = GameRectangle;

            SDL_Rect InfoRectangle = {};
            InfoRectangle.x = 400;
            InfoRectangle.y = 600;
            InfoRectangle.w = 200;
            InfoRectangle.h = 100;
            GameState->Menu.InfoRectangle = InfoRectangle;
        }
    }

    // UPDATE

    // RENDER
    switch(GameState->CurrentScene)
    {
        case SCENE_Menu:
        {
            menu_scene* Menu = &GameState->Menu;
            DrawBackground(Menu->BackgroundColor, Renderer);

            DrawTextQuad("Game", GameState->Font, Menu->GameColor, Menu->GameRectangle, Renderer);
            DrawTextQuad("Info", GameState->Font, Menu->InfoColor, Menu->InfoRectangle, Renderer);
        } break;
        case SCENE_Info:
        {
        } break;
        case SCENE_Game:
        {
            u32 R = Input.TranslateLeft.Down ? 255 : 0;
            u32 G = Input.TranslateDown.Down ? 255 : 0;
            u32 B = Input.TranslateRight.Down ? 255 : 0;

            for(u32 i = 0; i < GameState->TileCountX; ++i)
            {
                for(u32 j = 0; j < GameState->TileCountY; ++j)
                {
                    SDL_Rect Rectangle = {};
                    Rectangle.x = i * GameState->TileSize;
                    Rectangle.y = j * GameState->TileSize;
                    Rectangle.w = GameState->TileSize;
                    Rectangle.h = GameState->TileSize;
                    SDL_SetRenderDrawColor(Renderer, R * i / GameState->TileCountX, G * i / GameState->TileCountX, B * i / GameState->TileCountX, 255);
                    SDL_RenderFillRect(Renderer, &Rectangle);
                    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
                    SDL_RenderDrawRect(Renderer, &Rectangle);
                }
            }
        } break;
    }
}
