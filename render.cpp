#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "common.h"
#include "text.h"

#define STRING_LENGTH 50

#define TILE_SIZE 40
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
    v4 ExitColor;

    SDL_Rect PlayQuad;
    SDL_Rect InfoQuad;
    SDL_Rect ExitQuad;
};

struct info_scene
{
    v4 BackgroundColor;

    SDL_Rect ControlsQuad;

    SDL_Rect Placeholder1Quad;
    SDL_Rect Placeholder2Quad;
    SDL_Rect Placeholder3Quad;
    SDL_Rect Placeholder4Quad;
};

struct tile
{
    b32 IsDrawn;
    s32 X;
    s32 Y;
    v4 Color;
};

enum piece
{
    PIECE_I,
    PIECE_J,
    PIECE_L,
    PIECE_O,
    PIECE_S,
    PIECE_T,
    PIECE_Z,

    PIECE_Count,
};

struct tetromino
{
    piece Type;
    u32 Center;
    tile Tiles[4];
};

struct game_scene
{
    v4 BackgroundColor;

    u32 LastTime;

    v4 GameQuadColor;
    v4 GameQuadBorderColor;
    v4 NextTetrominoQuadColor;
    v4 NextTetrominoQuadBorderColor;

    SDL_Rect ScoreTextQuad;
    SDL_Rect ScoreCountQuad;
    SDL_Rect LineCountTextQuad;
    SDL_Rect LineCountQuad;
    SDL_Rect NextTetrominoQuad;
    SDL_Rect GameQuad;

    tile Tiles[TILE_COUNT_Y][TILE_COUNT_X];

    b32 TetrominoStop;
    b32 TetrominoIsFalling;
    tetromino Tetromino;
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
    info_scene Info;
    game_scene Game;
};

static void
DrawBackground(v4 Color, SDL_Renderer* Renderer)
{
    SDL_SetRenderDrawColor(Renderer, Color.R, Color.G, Color.B, Color.A);
    SDL_RenderClear(Renderer);
}

static void
DrawQuad(v4 Color, v4 BorderColor, SDL_Rect Rectangle, SDL_Renderer* Renderer)
{
    SDL_SetRenderDrawColor(Renderer, Color.R, Color.G, Color.B, Color.A);
    SDL_RenderFillRect(Renderer, &Rectangle);
    SDL_SetRenderDrawColor(Renderer, BorderColor.R, BorderColor.G, BorderColor.B, BorderColor.A);
    SDL_RenderDrawRect(Renderer, &Rectangle);
}

static void
DrawText(char* Text, TTF_Font* Font, SDL_Rect Rectangle, SDL_Renderer* Renderer)
{
    SDL_Rect TextRectangle = {};
    SDL_Texture* TextTexture = CreateTextTexture(&TextRectangle, Renderer, Font, Text);

    TextRectangle.x = Rectangle.x + (Rectangle.w - TextRectangle.w) / 2.0f;
    TextRectangle.y = Rectangle.y + (Rectangle.h - TextRectangle.h) / 2.0f;

    SDL_RenderCopy(Renderer, TextTexture, NULL, &TextRectangle);

    SDL_DestroyTexture(TextTexture);
}

static void
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

static void
DrawTile(tile Tile, SDL_Rect GameRectangle, SDL_Renderer* Renderer)
{
    SDL_Rect TileRectangle = {};
    TileRectangle.x = GameRectangle.x + 1 + Tile.X * TILE_SIZE;
    TileRectangle.y = GameRectangle.y - 1 + GameRectangle.h - (Tile.Y + 1) * TILE_SIZE;
    TileRectangle.w = TILE_SIZE;
    TileRectangle.h = TILE_SIZE;

    DrawQuad(Tile.Color, v4{ 255.0f, 255.0f, 255.0f, 255.0f }, TileRectangle, Renderer);
}

static void
DrawPreviewTetromino(tetromino Tetromino, SDL_Rect PreviewRectangle, SDL_Renderer* Renderer)
{
    u32 CountX = 0;
    u32 CountY = 0;
    s32 OffsetX = 0;

    switch(Tetromino.Type)
    {
        default:
        {
        } break;
        case PIECE_I:
        {
            CountX = 4;
            CountY = 1;
            OffsetX = 3;
        } break;
        case PIECE_J:
        {
            CountX = 3;
            CountY = 2;
            OffsetX = 3;
        } break;
        case PIECE_L:
        {
            CountX = 3;
            CountY = 2;
            OffsetX = 3;
        } break;
        case PIECE_O:
        {
            CountX = 2;
            CountY = 2;
            OffsetX = 2;
        } break;
        case PIECE_S:
        {
            CountX = 3;
            CountY = 2;
            OffsetX = 3;
        } break;
        case PIECE_T:
        {
            CountX = 3;
            CountY = 2;
            OffsetX = 3;
        } break;
        case PIECE_Z:
        {
            CountX = 3;
            CountY = 2;
            OffsetX = 3;
        } break;
    }

    s32 TetrominoWidth = CountX * TILE_SIZE;
    s32 TetrominoHeight = CountY * TILE_SIZE;

    s32 DrawCornerX = (PreviewRectangle.w - TetrominoWidth) / 2.0f;
    s32 DrawCornerY = (PreviewRectangle.h - TetrominoHeight) / 2.0f;

    for(u32 i = 0; i < 4; ++i)
    {
        s32 RectOffsetY = -Tetromino.Tiles[i].Y + TILE_COUNT_Y - 1;

        SDL_Rect TileRectangle = {};
        TileRectangle.x = PreviewRectangle.x + DrawCornerX + (Tetromino.Tiles[i].X - OffsetX) * TILE_SIZE;
        TileRectangle.y = PreviewRectangle.y + DrawCornerY + RectOffsetY * TILE_SIZE;
        TileRectangle.w = TILE_SIZE;
        TileRectangle.h = TILE_SIZE;

        DrawQuad(Tetromino.Tiles[i].Color, v4{ 255.0f, 255.0f, 255.0f, 255.0f }, TileRectangle, Renderer);
    }
}

static tetromino
CreateTetromino(piece Type)
{
    tetromino Tetromino = {};
    Tetromino.Type = Type;
    switch(Type)
    {
        default:
        {
        } break;
        case PIECE_I:
        {
            v4 Color = v4{ 150.0f, 0.0f, 0.0f, 255.0f };

            Tetromino.Center = 1;

            Tetromino.Tiles[0] = {};
            Tetromino.Tiles[0].IsDrawn = true;
            Tetromino.Tiles[0].X = 3;
            Tetromino.Tiles[0].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[0].Color = Color;

            Tetromino.Tiles[1] = {};
            Tetromino.Tiles[1].IsDrawn = true;
            Tetromino.Tiles[1].X = 4;
            Tetromino.Tiles[1].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[1].Color = Color;

            Tetromino.Tiles[2] = {};
            Tetromino.Tiles[2].IsDrawn = true;
            Tetromino.Tiles[2].X = 5;
            Tetromino.Tiles[2].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[2].Color = Color;

            Tetromino.Tiles[3] = {};
            Tetromino.Tiles[3].IsDrawn = true;
            Tetromino.Tiles[3].X = 6;
            Tetromino.Tiles[3].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[3].Color = Color;
        } break;
        case PIECE_J:
        {
            v4 Color = v4{ 150.0f, 150.0f, 150.0f, 255.0f };

            Tetromino.Center = 1;

            Tetromino.Tiles[0] = {};
            Tetromino.Tiles[0].IsDrawn = true;
            Tetromino.Tiles[0].X = 3;
            Tetromino.Tiles[0].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[0].Color = Color;

            Tetromino.Tiles[1] = {};
            Tetromino.Tiles[1].IsDrawn = true;
            Tetromino.Tiles[1].X = 4;
            Tetromino.Tiles[1].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[1].Color = Color;

            Tetromino.Tiles[2] = {};
            Tetromino.Tiles[2].IsDrawn = true;
            Tetromino.Tiles[2].X = 5;
            Tetromino.Tiles[2].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[2].Color = Color;

            Tetromino.Tiles[3] = {};
            Tetromino.Tiles[3].IsDrawn = true;
            Tetromino.Tiles[3].X = 5;
            Tetromino.Tiles[3].Y = TILE_COUNT_Y - 2;
            Tetromino.Tiles[3].Color = Color;
        } break;
        case PIECE_L:
        {
            v4 Color = v4{ 150.0f, 0.0f, 150.0f, 255.0f };

            Tetromino.Center = 2;

            Tetromino.Tiles[0] = {};
            Tetromino.Tiles[0].IsDrawn = true;
            Tetromino.Tiles[0].X = 3;
            Tetromino.Tiles[0].Y = TILE_COUNT_Y - 2;
            Tetromino.Tiles[0].Color = Color;

            Tetromino.Tiles[1] = {};
            Tetromino.Tiles[1].IsDrawn = true;
            Tetromino.Tiles[1].X = 3;
            Tetromino.Tiles[1].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[1].Color = Color;

            Tetromino.Tiles[2] = {};
            Tetromino.Tiles[2].IsDrawn = true;
            Tetromino.Tiles[2].X = 4;
            Tetromino.Tiles[2].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[2].Color = Color;

            Tetromino.Tiles[3] = {};
            Tetromino.Tiles[3].IsDrawn = true;
            Tetromino.Tiles[3].X = 5;
            Tetromino.Tiles[3].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[3].Color = Color;
        } break;
        case PIECE_O:
        {
            v4 Color = v4{ 0.0f, 0.0f, 150.0f, 255.0f };

            Tetromino.Center = -1;

            Tetromino.Tiles[0] = {};
            Tetromino.Tiles[0].IsDrawn = true;
            Tetromino.Tiles[0].X = 4;
            Tetromino.Tiles[0].Y = TILE_COUNT_Y - 2;
            Tetromino.Tiles[0].Color = Color;

            Tetromino.Tiles[1] = {};
            Tetromino.Tiles[1].IsDrawn = true;
            Tetromino.Tiles[1].X = 4;
            Tetromino.Tiles[1].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[1].Color = Color;

            Tetromino.Tiles[2] = {};
            Tetromino.Tiles[2].IsDrawn = true;
            Tetromino.Tiles[2].X = 5;
            Tetromino.Tiles[2].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[2].Color = Color;

            Tetromino.Tiles[3] = {};
            Tetromino.Tiles[3].IsDrawn = true;
            Tetromino.Tiles[3].X = 5;
            Tetromino.Tiles[3].Y = TILE_COUNT_Y - 2;
            Tetromino.Tiles[3].Color = Color;
        } break;
        case PIECE_S:
        {
            v4 Color = v4{ 0.0f, 150.0f, 0.0f, 255.0f };

            Tetromino.Center = 2;

            Tetromino.Tiles[0] = {};
            Tetromino.Tiles[0].IsDrawn = true;
            Tetromino.Tiles[0].X = 3;
            Tetromino.Tiles[0].Y = TILE_COUNT_Y - 2;
            Tetromino.Tiles[0].Color = Color;

            Tetromino.Tiles[1] = {};
            Tetromino.Tiles[1].IsDrawn = true;
            Tetromino.Tiles[1].X = 4;
            Tetromino.Tiles[1].Y = TILE_COUNT_Y - 2;
            Tetromino.Tiles[1].Color = Color;

            Tetromino.Tiles[2] = {};
            Tetromino.Tiles[2].IsDrawn = true;
            Tetromino.Tiles[2].X = 4;
            Tetromino.Tiles[2].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[2].Color = Color;

            Tetromino.Tiles[3] = {};
            Tetromino.Tiles[3].IsDrawn = true;
            Tetromino.Tiles[3].X = 5;
            Tetromino.Tiles[3].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[3].Color = Color;
        } break;
        case PIECE_T:
        {
            v4 Color = v4{ 150.0f, 75.0f, 75.0f, 255.0f };

            Tetromino.Center = 1;

            Tetromino.Tiles[0] = {};
            Tetromino.Tiles[0].IsDrawn = true;
            Tetromino.Tiles[0].X = 3;
            Tetromino.Tiles[0].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[0].Color = Color;

            Tetromino.Tiles[1] = {};
            Tetromino.Tiles[1].IsDrawn = true;
            Tetromino.Tiles[1].X = 4;
            Tetromino.Tiles[1].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[1].Color = Color;

            Tetromino.Tiles[2] = {};
            Tetromino.Tiles[2].IsDrawn = true;
            Tetromino.Tiles[2].X = 4;
            Tetromino.Tiles[2].Y = TILE_COUNT_Y - 2;
            Tetromino.Tiles[2].Color = Color;

            Tetromino.Tiles[3] = {};
            Tetromino.Tiles[3].IsDrawn = true;
            Tetromino.Tiles[3].X = 5;
            Tetromino.Tiles[3].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[3].Color = Color;
        } break;
        case PIECE_Z:
        {
            v4 Color = v4{ 0.0f, 150.0f, 150.0f, 255.0f };

            Tetromino.Center = 1;

            Tetromino.Tiles[0] = {};
            Tetromino.Tiles[0].IsDrawn = true;
            Tetromino.Tiles[0].X = 3;
            Tetromino.Tiles[0].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[0].Color = Color;

            Tetromino.Tiles[1] = {};
            Tetromino.Tiles[1].IsDrawn = true;
            Tetromino.Tiles[1].X = 4;
            Tetromino.Tiles[1].Y = TILE_COUNT_Y - 1;
            Tetromino.Tiles[1].Color = Color;

            Tetromino.Tiles[2] = {};
            Tetromino.Tiles[2].IsDrawn = true;
            Tetromino.Tiles[2].X = 4;
            Tetromino.Tiles[2].Y = TILE_COUNT_Y - 2;
            Tetromino.Tiles[2].Color = Color;

            Tetromino.Tiles[3] = {};
            Tetromino.Tiles[3].IsDrawn = true;
            Tetromino.Tiles[3].X = 5;
            Tetromino.Tiles[3].Y = TILE_COUNT_Y - 2;
            Tetromino.Tiles[3].Color = Color;
        } break;
    }
    return Tetromino;
}

static u32
CheckAgainstBoundaries(tetromino Tetromino)
{
    u32 Result = 0;
    for(u32 i = 0; i < 4; ++i)
    {
        if(Tetromino.Tiles[i].X < 0)
        {
            Result = 1;
            break;
        }
        else if(Tetromino.Tiles[i].X >= TILE_COUNT_X)
        {
            Result = 2;
            break;
        }
    }
    return Result;
}

static void
CheckBoundsAndFix(tetromino* Tetromino)
{
    u32 Result = CheckAgainstBoundaries(*Tetromino);
    while(Result)
    {
        if(Result == 1)
        {
            for(u32 i = 0; i < 4; ++i)
            {
                ++Tetromino->Tiles[i].X;
            }
        }
        else if(Result == 2)
        {
            for(u32 i = 0; i < 4; ++i)
            {
                --Tetromino->Tiles[i].X;
            }
        }
        Result = CheckAgainstBoundaries(*Tetromino);
    }
}

static b32
ValidPosition(game_scene* Game, tetromino Tetromino)
{
    b32 Result = true;
    for(u32 i = 0; i < 4; ++i)
    {
        if((Tetromino.Tiles[i].X < 0) || (Tetromino.Tiles[i].Y < 0) ||
           (Tetromino.Tiles[i].X >= TILE_COUNT_X) || (Tetromino.Tiles[i].Y >= TILE_COUNT_Y) ||
            Game->Tiles[Tetromino.Tiles[i].Y][Tetromino.Tiles[i].X].IsDrawn)
        {
            Result = false;
            break;
        }
    }
    return Result;
}

static b32
ShouldStop(game_scene* Game, tetromino Tetromino)
{
    b32 Result = false;
    for(u32 i = 0; i < 4; ++i)
    {
        if((Tetromino.Tiles[i].Y == 0) || Game->Tiles[Tetromino.Tiles[i].Y - 1][Tetromino.Tiles[i].X].IsDrawn)
        {
            Result = true;
            break;
        }
    }
    return Result;
}

GAME_UPDATE_AND_RENDER(GameUpdateAndRender)
{
    Assert(GameMemory.IsInit);
    // INIT
    game_state* GameState = (game_state*)GameMemory.Memory;

    menu_scene* Menu = &GameState->Menu;
    info_scene* Info = &GameState->Info;
    game_scene* Game = &GameState->Game;

    if(!GameState->IsInit)
    {
        GameState->IsInit = true;

        GameState->Font = LoadFont("UbuntuMono.ttf", 50);

        GameState->CurrentScene = SCENE_Menu;

        // MENU
        {
            Menu->BackgroundColor = v4{ 100.0f, 100.0f, 100.0f, 255.0f };
            Menu->PlayColor = v4{ 50.0f, 150.0f, 0.0f, 255.0f };
            Menu->InfoColor = v4{ 0.0f, 50.0f, 100.0f, 255.0f };
            Menu->ExitColor = v4{ 150.0f, 0.0f, 0.0f, 255.0f };

            SDL_Rect PlayQuad = {};
            PlayQuad.x = 300;
            PlayQuad.y = 200;
            PlayQuad.w = 400;
            PlayQuad.h = 100;
            Menu->PlayQuad = PlayQuad;

            SDL_Rect InfoQuad = {};
            InfoQuad.x = 300;
            InfoQuad.y = 450;
            InfoQuad.w = 400;
            InfoQuad.h = 100;
            Menu->InfoQuad = InfoQuad;

            SDL_Rect ExitQuad = {};
            ExitQuad.x = 300;
            ExitQuad.y = 700;
            ExitQuad.w = 400;
            ExitQuad.h = 100;
            Menu->ExitQuad = ExitQuad;
        }

        // INFO
        {
            Info->BackgroundColor = v4{ 50.0f, 50.0f, 70.0f, 255.0f };

            SDL_Rect ControlsQuad = {};
            ControlsQuad.x = 200;
            ControlsQuad.y = 100;
            ControlsQuad.w = 200;
            ControlsQuad.h = 50;
            Info->ControlsQuad = ControlsQuad;

            SDL_Rect Placeholder1Quad = {};
            Placeholder1Quad.x = 100;
            Placeholder1Quad.y = 200;
            Placeholder1Quad.w = 200;
            Placeholder1Quad.h = 50;
            Info->Placeholder1Quad = Placeholder1Quad;

            SDL_Rect Placeholder2Quad = {};
            Placeholder2Quad.x = 100;
            Placeholder2Quad.y = 250;
            Placeholder2Quad.w = 200;
            Placeholder2Quad.h = 50;
            Info->Placeholder2Quad = Placeholder2Quad;

            SDL_Rect Placeholder3Quad = {};
            Placeholder3Quad.x = 100;
            Placeholder3Quad.y = 300;
            Placeholder3Quad.w = 200;
            Placeholder3Quad.h = 50;
            Info->Placeholder3Quad = Placeholder3Quad;

            SDL_Rect Placeholder4Quad = {};
            Placeholder4Quad.x = 100;
            Placeholder4Quad.y = 350;
            Placeholder4Quad.w = 200;
            Placeholder4Quad.h = 50;
            Info->Placeholder4Quad = Placeholder4Quad;
        }

        // GAME
        {
            Game->BackgroundColor = v4{ 50.0f, 50.0f, 50.0f, 255.0f };
            Game->GameQuadColor = v4{ 50.0f, 0.0f, 100.0f, 255.0f };
            Game->GameQuadBorderColor = v4{ 225.0f, 0.0f, 00.0f, 255.0f };
            Game->NextTetrominoQuadColor = v4{ 0.0f, 50.0f, 120.0f, 255.0f };
            Game->NextTetrominoQuadBorderColor = v4{ 0.0f, 255.0f, 00.0f, 255.0f };

            SDL_Rect GameQuad = {};
            GameQuad.x = 99;
            GameQuad.y = 99;
            GameQuad.w = TILE_SIZE * TILE_COUNT_X + 2;
            GameQuad.h = TILE_SIZE * TILE_COUNT_Y + 2;
            Game->GameQuad = GameQuad;

            SDL_Rect ScoreTextQuad = {};
            ScoreTextQuad.x = 600;
            ScoreTextQuad.y = 50;
            ScoreTextQuad.w = 300;
            ScoreTextQuad.h = 50;
            Game->ScoreTextQuad = ScoreTextQuad;

            SDL_Rect ScoreCountQuad = {};
            ScoreCountQuad.x = 600;
            ScoreCountQuad.y = 100;
            ScoreCountQuad.w = 300;
            ScoreCountQuad.h = 50;
            Game->ScoreCountQuad = ScoreCountQuad;

            SDL_Rect LineCountTextQuad = {};
            LineCountTextQuad.x = 600;
            LineCountTextQuad.y = 200;
            LineCountTextQuad.w = 300;
            LineCountTextQuad.h = 50;
            Game->LineCountTextQuad = LineCountTextQuad;

            SDL_Rect LineCountQuad = {};
            LineCountQuad.x = 600;
            LineCountQuad.y = 250;
            LineCountQuad.w = 300;
            LineCountQuad.h = 50;
            Game->LineCountQuad = LineCountQuad;

            SDL_Rect NextTetrominoQuad = {};
            NextTetrominoQuad.x = 600;
            NextTetrominoQuad.y = 350;
            NextTetrominoQuad.w = 300;
            NextTetrominoQuad.h = 300;
            Game->NextTetrominoQuad = NextTetrominoQuad;

            for(u32 i = 0; i < TILE_COUNT_Y; ++i)
            {
                for(u32 j = 0; j < TILE_COUNT_X; ++j)
                {
                    Game->Tiles[i][j] = {};
                }
            }
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
                DrawTextQuad("Exit (Escape)", GameState->Font, Menu->ExitColor, Menu->ExitQuad, Renderer);
            }
        } break;
        case SCENE_Info:
        {
            {
                DrawBackground(Info->BackgroundColor, Renderer);

                DrawText("Controls:", GameState->Font, Info->ControlsQuad, Renderer);
                DrawText("* Placeholder", GameState->Font, Info->Placeholder1Quad, Renderer);
                DrawText("* Placeholder", GameState->Font, Info->Placeholder2Quad, Renderer);
                DrawText("* Placeholder", GameState->Font, Info->Placeholder3Quad, Renderer);
                DrawText("* Placeholder", GameState->Font, Info->Placeholder4Quad, Renderer);
            }

            {
                if(Input.Back.Down && Input.Back.Changed)
                {
                    GameState->CurrentScene = SCENE_Menu;
                }
            }

        } break;
        case SCENE_Game:
        {
            {
                DrawBackground(Game->BackgroundColor, Renderer);

                DrawText("Score:", GameState->Font, Game->ScoreTextQuad, Renderer);
                DrawText("000000", GameState->Font, Game->ScoreCountQuad, Renderer);

                DrawText("Line Count:", GameState->Font, Game->LineCountTextQuad, Renderer);
                DrawText("0000", GameState->Font, Game->LineCountQuad, Renderer);

                DrawQuad(Game->NextTetrominoQuadColor, Game->NextTetrominoQuadBorderColor, Game->NextTetrominoQuad, Renderer);

                DrawPreviewTetromino(CreateTetromino(PIECE_Z), Game->NextTetrominoQuad, Renderer);
            }

            {
                if(Input.Back.Down && Input.Back.Changed)
                {
                    GameState->CurrentScene = SCENE_Menu;
                }
            }

            {
                DrawQuad(Game->GameQuadColor, Game->GameQuadBorderColor, Game->GameQuad, Renderer);

                for(u32 i = 0; i < TILE_COUNT_Y; ++i)
                {
                    for(u32 j = 0; j < TILE_COUNT_X; ++j)
                    {
                        if(Game->Tiles[i][j].IsDrawn)
                        {
                            DrawTile(Game->Tiles[i][j], Game->GameQuad, Renderer);
                        }
                    }
                }

                // TODO(rytis): Fix the order in which things are done.

                if(!Game->TetrominoIsFalling)
                {
                    Game->TetrominoIsFalling = true;
                    Game->Tetromino = CreateTetromino(PIECE_I);
                }

                {
                    tetromino Tetromino = Game->Tetromino;
                    if(Input.TranslateDown.Down)// && Input.TranslateDown.Changed)
                    {
                        for(u32 i = 0; i < 4; ++i)
                        {
                            --Tetromino.Tiles[i].Y;
                        }
                    }

                    if(Input.TranslateLeft.Down && Input.TranslateLeft.Changed)
                    {
                        for(u32 i = 0; i < 4; ++i)
                        {
                            --Tetromino.Tiles[i].X;
                        }
                    }

                    if(Input.TranslateRight.Down && Input.TranslateRight.Changed)
                    {
                        for(u32 i = 0; i < 4; ++i)
                        {
                            ++Tetromino.Tiles[i].X;
                        }
                    }

                    if(Input.RotateLeft.Down && Input.RotateLeft.Changed)
                    {
                        if(Tetromino.Center != -1)
                        {
                            for(u32 i = 0; i < 4; ++i)
                            {
                                s32 X = Tetromino.Tiles[i].X - Tetromino.Tiles[Tetromino.Center].X;
                                s32 Y = Tetromino.Tiles[i].Y - Tetromino.Tiles[Tetromino.Center].Y;
                                Tetromino.Tiles[i].X = Tetromino.Tiles[Tetromino.Center].X + Y;
                                Tetromino.Tiles[i].Y = Tetromino.Tiles[Tetromino.Center].Y - X;
                            }
                        }
                    }

                    if(Input.RotateRight.Down && Input.RotateRight.Changed)
                    {
                        if(Tetromino.Center != -1)
                        {
                            for(u32 i = 0; i < 4; ++i)
                            {
                                s32 X = Tetromino.Tiles[i].X - Tetromino.Tiles[Tetromino.Center].X;
                                s32 Y = Tetromino.Tiles[i].Y - Tetromino.Tiles[Tetromino.Center].Y;
                                Tetromino.Tiles[i].X = Tetromino.Tiles[Tetromino.Center].X - Y;
                                Tetromino.Tiles[i].Y = Tetromino.Tiles[Tetromino.Center].Y + X;
                            }
                        }
                    }

                    if(Input.Time > Game->LastTime + 1000)
                    {
                        for(u32 i = 0; i < 4; ++i)
                        {
                            --Tetromino.Tiles[i].Y;
                        }
                        Game->LastTime = Input.Time;
                    }

                    CheckBoundsAndFix(&Tetromino);
                    if(ValidPosition(Game, Tetromino))
                    {
                        Game->Tetromino = Tetromino;
                    }

                    if(Game->TetrominoStop)
                    {
                        for(u32 i = 0; i < 4; ++i)
                        {
                            Game->Tiles[Game->Tetromino.Tiles[i].Y][Game->Tetromino.Tiles[i].X] = Game->Tetromino.Tiles[i];
                        }

                        Game->TetrominoStop = false;
                        Game->TetrominoIsFalling = false;
                    }
                    else
                    {
                        Game->TetrominoStop = ShouldStop(Game, Game->Tetromino);
                    }
                }

                for(u32 i = 0; i < 4; ++i)
                {
                    if(Game->Tetromino.Tiles[i].Y < TILE_COUNT_Y)
                    {
                        DrawTile(Game->Tetromino.Tiles[i], Game->GameQuad, Renderer);
                    }
                }
            }
        } break;
    }
}
