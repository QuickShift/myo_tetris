#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "common.h"
#include "text.h"

#define STRING_LENGTH 50

#define TILE_COUNT_X 10
#define TILE_COUNT_Y 20

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

    v4 PlayColor;
    v4 InfoColor;

    SDL_Rect PlayQuad;
    SDL_Rect InfoQuad;
};

struct tile
{
    b32 IsDrawn;
    u32 X;
    u32 Y;
    v4 Color;
};

struct game_scene
{
    u32 TileSize;

    v4 GameQuadColor;
    v4 GameQuadBorderColor;

    SDL_Rect GameQuad;

    tile Tiles[TILE_COUNT_Y][TILE_COUNT_X];
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
    game_scene Game;
};

void
DrawBackground(v4 Color, SDL_Renderer* Renderer)
{
    SDL_SetRenderDrawColor(Renderer, Color.R, Color.G, Color.B, Color.A);
    SDL_RenderClear(Renderer);
}

void
DrawQuad(v4 Color, v4 BorderColor, SDL_Rect Rectangle, SDL_Renderer* Renderer)
{
    SDL_SetRenderDrawColor(Renderer, Color.R, Color.G, Color.B, Color.A);
    SDL_RenderFillRect(Renderer, &Rectangle);
    SDL_SetRenderDrawColor(Renderer, BorderColor.R, BorderColor.G, BorderColor.B, BorderColor.A);
    SDL_RenderDrawRect(Renderer, &Rectangle);
}

void
DrawTextQuad(char* Text, TTF_Font* Font, v4 Color, SDL_Rect Rectangle, SDL_Renderer* Renderer)
{
    DrawQuad(Color, v4{ 0.0f, 0.0f, 0.0f, 255.0f }, Rectangle, Renderer);

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

    menu_scene* Menu = &GameState->Menu;
    game_scene* Game = &GameState->Game;

    if(!GameState->IsInit)
    {
        GameState->IsInit = true;

        GameState->Font = LoadFont("UbuntuMono.ttf", 50);

        GameState->TileSize = 40;
        GameState->TileCountX = WINDOW_WIDTH / GameState->TileSize;
        GameState->TileCountY = WINDOW_HEIGHT / GameState->TileSize;

        GameState->CurrentScene = SCENE_Menu;

        // MENU
        {
            Menu->BackgroundColor = v4{ 100.0f, 100.0f, 100.0f, 255.0f };
            Menu->PlayColor = v4{ 150.0f, 0.0f, 0.0f, 255.0f };
            Menu->InfoColor = v4{ 0.0f, 100.0f, 100.0f, 255.0f };

            SDL_Rect PlayQuad = {};
            PlayQuad.x = 300;
            PlayQuad.y = 300;
            PlayQuad.w = 400;
            PlayQuad.h = 100;
            Menu->PlayQuad = PlayQuad;

            SDL_Rect InfoQuad = {};
            InfoQuad.x = 300;
            InfoQuad.y = 600;
            InfoQuad.w = 400;
            InfoQuad.h = 100;
            Menu->InfoQuad = InfoQuad;
        }

        // GAME
        {
            Game->TileSize = 40;

            Game->GameQuadColor = v4{ 50.0f, 0.0f, 100.0f, 255.0f };
            Game->GameQuadBorderColor = v4{ 225.0f, 0.0f, 00.0f, 255.0f };

            SDL_Rect GameQuad = {};
            GameQuad.x = 399;
            GameQuad.y = 99;
            GameQuad.w = Game->TileSize * TILE_COUNT_X + 2;
            GameQuad.h = Game->TileSize * TILE_COUNT_Y + 2;
            Game->GameQuad = GameQuad;

            for(u32 i = 0; i < TILE_COUNT_Y; ++i)
            {
                for(u32 j = 0; j < TILE_COUNT_X; ++j)
                {
                    Game->Tiles[i][j] = {};
                }
            }

            Game->Tiles[0][0].IsDrawn = true;
            Game->Tiles[0][0].Color = v4{ 255.0f, 255.0f, 255.0f, 255.0f };

            Game->Tiles[1][1].IsDrawn = true;
            Game->Tiles[1][1].Color = v4{ 255.0f, 255.0f, 255.0f, 255.0f };

            Game->Tiles[1][0].IsDrawn = true;
            Game->Tiles[1][0].Color = v4{ 255.0f, 255.0f, 255.0f, 255.0f };
        }
    }

    switch(GameState->CurrentScene)
    {
        case SCENE_Menu:
        {
            // UPDATE MENU
            {
                if(Input.RotateRight.Down && Input.RotateRight.Changed)
                {
                    GameState->CurrentScene = SCENE_Game;
                }

                if(Input.RotateLeft.Down && Input.RotateLeft.Changed)
                {
                    GameState->CurrentScene = SCENE_Info;
                }
            }

            // RENDER MENU
            {
                DrawBackground(Menu->BackgroundColor, Renderer);

                DrawTextQuad("Play (Space)", GameState->Font, Menu->PlayColor, Menu->PlayQuad, Renderer);
                DrawTextQuad("Info (Shift)", GameState->Font, Menu->InfoColor, Menu->InfoQuad, Renderer);
            }
        } break;
        case SCENE_Info:
        {
        } break;
        case SCENE_Game:
        {
            {
                if(Input.Back.Down && Input.Back.Changed)
                {
                    GameState->CurrentScene = SCENE_Menu;
                }
            }

            // Random stuff; delete later.
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
            }

            {
                DrawQuad(Game->GameQuadColor, Game->GameQuadBorderColor, Game->GameQuad, Renderer);

                SDL_Rect TileRectangle = {};
                TileRectangle.w = Game->TileSize;
                TileRectangle.h = Game->TileSize;

                for(u32 i = 0; i < TILE_COUNT_Y; ++i)
                {
                    TileRectangle.y = Game->GameQuad.y - 1 + Game->GameQuad.h - (i + 1) * Game->TileSize;
                    for(u32 j = 0; j < TILE_COUNT_X; ++j)
                    {
                        if(Game->Tiles[i][j].IsDrawn)
                        {
                            TileRectangle.x = Game->GameQuad.x + 1 + j * Game->TileSize;
                            DrawQuad(Game->Tiles[i][j].Color, v4{ 255.0f, 0.0f, 0.0f, 255.0f }, TileRectangle, Renderer);
                        }
                    }
                }
            }
        } break;
    }
}
