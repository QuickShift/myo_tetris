#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "render_data.h"

enum scene
{
    SCENE_Menu,
    SCENE_Info,
    SCENE_Game,
    SCENE_Over,

    SCENE_Count,
};

#include "menu_scene.h"
#include "info_scene.h"
#include "game_scene.h"
#include "over_scene.h"

struct game_state
{
    b32 IsInit;

    scene CurrentScene;

    menu_scene Menu;
    info_scene Info;
    game_scene Game;
    over_scene Over;
};

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
           (Tetromino.Tiles[i].X >= TILE_COUNT_X) ||// (Tetromino.Tiles[i].Y >= TILE_COUNT_Y) ||
            ((Tetromino.Tiles[i].Y < TILE_COUNT_Y) && Game->Tiles[Tetromino.Tiles[i].Y][Tetromino.Tiles[i].X].IsDrawn))
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

static void
CheckForLines(game_scene* Game)
{
    Game->FullLineCount = 0;
    for(int i = 0; i < TILE_COUNT_Y; ++i)
    {
        b32 IsFilled = true;
        for(int j = 0; j < TILE_COUNT_X; ++j)
        {
            if(!Game->Tiles[i][j].IsDrawn)
            {
                IsFilled = false;
                break;
            }
        }

        if(IsFilled)
        {
            Game->LineIndexes[Game->FullLineCount] = i;
            ++Game->FullLineCount;
            for(int j = 0; j < TILE_COUNT_X; ++j)
            {
                Game->Tiles[i][j].Color = v4{ 255.0f, 255.0f, 255.0f, 255.0f };
            }
        }
    }
}

static void
RemoveFullLines(game_scene* Game)
{
    s32 CurrentLine = Game->FullLineCount - 1;
    for(s32 i = Game->FullLineCount - 1; i >= 0; --i)
    {
        for(int j = Game->LineIndexes[i]; j < TILE_COUNT_Y - 1; ++j)
        {
            for(int k = 0; k < TILE_COUNT_X; ++k)
            {
                Game->Tiles[j][k] = Game->Tiles[j + 1][k];
                --Game->Tiles[j][k].Y;
                if(j == Game->LineIndexes[i])
                {
                    Game->Score += (u32)((Game->Tiles[j][k].Color.R + Game->Tiles[j][k].Color.G + Game->Tiles[j][k].Color.B) / 10.0f);
                }
            }
        }

        for(int j = 0; j < TILE_COUNT_X; ++j)
        {
            Game->Tiles[TILE_COUNT_Y - 1][j] = {}; 
        }
        --CurrentLine;
        ++Game->LineCount;
    }
    Game->FullLineCount = 0;
}

static void
ResetGame(game_scene* Game)
{
    for(u32 i = 0; i < TILE_COUNT_Y; ++i)
    {
        for(u32 j = 0; j < TILE_COUNT_X; ++j)
        {
            Game->Tiles[i][j].IsDrawn = false;
        }
    }
    Game->Score = 0;
    Game->LineCount = 0;
}

GAME_UPDATE_AND_RENDER(GameUpdateAndRender)
{
    Assert(GameMemory->IsInit);
    // INIT
    game_state* GameState = (game_state*)GameMemory->Memory;

    menu_scene* Menu = &GameState->Menu;
    info_scene* Info = &GameState->Info;
    game_scene* Game = &GameState->Game;
    over_scene* Over = &GameState->Over;

    if(!GameState->IsInit)
    {
        GameState->IsInit = true;

        GameState->CurrentScene = SCENE_Menu;

        InitMenuScene(Menu);
        InitInfoScene(Info);
        InitGameScene(Game);
        InitOverScene(Over);
    }

    switch(GameState->CurrentScene)
    {
        case SCENE_Menu:
        {
            {
                if(Input->TranslateRight.Down && Input->TranslateRight.Changed)
                {
                    GameState->CurrentScene = SCENE_Game;
                }

                if(Input->TranslateLeft.Down && Input->TranslateLeft.Changed)
                {
                    GameState->CurrentScene = SCENE_Info;
                }
            }
            RenderMenuScene(RenderData, Menu);
        } break;
        case SCENE_Info:
        {
            {
                if(Input->Back.Down && Input->Back.Changed)
                {
                    GameState->CurrentScene = SCENE_Menu;
                }
            }
            RenderInfoScene(RenderData, Info);
        } break;
        case SCENE_Game:
        {
            {
                if(Input->Back.Down && Input->Back.Changed)
                {
                    GameState->CurrentScene = SCENE_Menu;
                    ResetGame(Game);
                }
            }

            {
                // TODO(rytis): Fix the order in which things are done.

                if(!Game->TetrominoIsFalling)
                {
                    Game->LastTime = Input->Time;
                    if(Game->FullLineCount)
                    {
                        RemoveFullLines(Game);
                        sprintf(Game->ScoreString, "%06u", Game->Score);
                        sprintf(Game->LineCountString, "%04u", Game->LineCount);
                    }
                    Game->TetrominoIsFalling = true;
                    Game->Tetromino = Game->NextTetromino;
                    Game->NextTetromino = CreateTetromino((piece)(rand() % PIECE_Count));

                    if(!ValidPosition(Game, Game->Tetromino))
                    {
                        sprintf(Over->ScoreString, "%06u", Game->Score);
                        sprintf(Over->LineCountString, "%04u", Game->LineCount);
                        Over->LastOverTime = Input->Time;
                        GameState->CurrentScene = SCENE_Over;
                        ResetGame(Game);
                    }
                }

                {
                    tetromino Tetromino = Game->Tetromino;
                    if(Input->TranslateDown.Down && Input->Time > Game->LastDownKeyTime + 70)// && Input->TranslateDown.Changed)
                    {
                        for(u32 i = 0; i < 4; ++i)
                        {
                            --Tetromino.Tiles[i].Y;
                        }
                        Game->LastDownKeyTime = Input->Time;
                    }

                    if(Input->TranslateLeft.Down && Input->TranslateLeft.Changed)
                    {
                        for(u32 i = 0; i < 4; ++i)
                        {
                            --Tetromino.Tiles[i].X;
                        }
                    }

                    if(Input->TranslateRight.Down && Input->TranslateRight.Changed)
                    {
                        for(u32 i = 0; i < 4; ++i)
                        {
                            ++Tetromino.Tiles[i].X;
                        }
                    }

                    if(Input->RotateLeft.Down && Input->RotateLeft.Changed)
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

                    if(Input->RotateRight.Down && Input->RotateRight.Changed)
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

                    if(!Input->TranslateDown.Down && Input->Time > Game->LastTime + 1000)
                    {
                        for(u32 i = 0; i < 4; ++i)
                        {
                            --Tetromino.Tiles[i].Y;
                        }
                        Game->LastTime = Input->Time;
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

                        CheckForLines(Game);
                    }
                    else
                    {
                        Game->TetrominoStop = ShouldStop(Game, Game->Tetromino);
                    }
                }
            }
            RenderGameScene(RenderData, Game);
        } break;
        case SCENE_Over:
        {
            if(Input->Time > Over->LastOverTime + 2000)
            {
                GameState->CurrentScene = SCENE_Menu;
            }
            RenderOverScene(RenderData, Over);
        } break;
    }
}
