#include <stdio.h>
#include <stdlib.h>

#include "game_scene.H"

tetromino
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

void
InitGameScene(game_scene* Game)
{
    Game->BackgroundColor = v4{ 50.0f, 50.0f, 50.0f, 255.0f };
    Game->GameRectangleColor = v4{ 50.0f, 0.0f, 100.0f, 255.0f };
    Game->GameRectangleBorderColor = v4{ 225.0f, 0.0f, 00.0f, 255.0f };
    Game->NextTetrominoRectangleColor = v4{ 0.0f, 50.0f, 120.0f, 255.0f };
    Game->NextTetrominoRectangleBorderColor = v4{ 0.0f, 255.0f, 00.0f, 255.0f };

    rect GameRectangle = {};
    GameRectangle.X = 99;
    GameRectangle.Y = 99;
    GameRectangle.W = TILE_SIZE * TILE_COUNT_X + 2;
    GameRectangle.H = TILE_SIZE * TILE_COUNT_Y + 2;
    Game->GameRectangle = GameRectangle;

    rect ScoreTextRectangle = {};
    ScoreTextRectangle.X = 600;
    ScoreTextRectangle.Y = 50;
    ScoreTextRectangle.W = 300;
    ScoreTextRectangle.H = 50;
    Game->ScoreTextRectangle = ScoreTextRectangle;

    rect ScoreCountRectangle = {};
    ScoreCountRectangle.X = 600;
    ScoreCountRectangle.Y = 100;
    ScoreCountRectangle.W = 300;
    ScoreCountRectangle.H = 50;
    Game->ScoreCountRectangle = ScoreCountRectangle;

    rect LineCountTextRectangle = {};
    LineCountTextRectangle.X = 600;
    LineCountTextRectangle.Y = 200;
    LineCountTextRectangle.W = 300;
    LineCountTextRectangle.H = 50;
    Game->LineCountTextRectangle = LineCountTextRectangle;

    rect LineCountRectangle = {};
    LineCountRectangle.X = 600;
    LineCountRectangle.Y = 250;
    LineCountRectangle.W = 300;
    LineCountRectangle.H = 50;
    Game->LineCountRectangle = LineCountRectangle;

    rect NextTetrominoRectangle = {};
    NextTetrominoRectangle.X = 600;
    NextTetrominoRectangle.Y = 350;
    NextTetrominoRectangle.W = 300;
    NextTetrominoRectangle.H = 300;
    Game->NextTetrominoRectangle = NextTetrominoRectangle;

    for(u32 i = 0; i < TILE_COUNT_Y; ++i)
    {
        for(u32 j = 0; j < TILE_COUNT_X; ++j)
        {
            Game->Tiles[i][j] = {};
        }
    }

    sprintf(Game->ScoreString, "%06u", Game->Score);
    sprintf(Game->LineCountString, "%04u", Game->LineCount);

    Game->NextTetromino = CreateTetromino((piece)(rand() % PIECE_Count));
}

#define PushPreviewTetromino(Tetromino, Rectangle) _PushPreviewTetromino(RenderData, Tetromino, Rectangle)
static void
_PushPreviewTetromino(render_data* RenderData, tetromino Tetromino, rect PreviewRectangle)
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
            OffsetX = 4;
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

    s32 DrawCornerX = (PreviewRectangle.W - TetrominoWidth) / 2.0f;
    s32 DrawCornerY = (PreviewRectangle.H - TetrominoHeight) / 2.0f;

    for(u32 i = 0; i < 4; ++i)
    {
        s32 RectOffsetY = -Tetromino.Tiles[i].Y + TILE_COUNT_Y - 1;

        rect TileRectangle = {};
        TileRectangle.X = PreviewRectangle.X + DrawCornerX + (Tetromino.Tiles[i].X - OffsetX) * TILE_SIZE;
        TileRectangle.Y = PreviewRectangle.Y + DrawCornerY + RectOffsetY * TILE_SIZE;
        TileRectangle.W = TILE_SIZE;
        TileRectangle.H = TILE_SIZE;

        v4 TileBorderColor = { 255.0f, 255.0f, 255.0f, 255.0f };
        PushQuad(Tetromino.Tiles[i].Color, TileBorderColor, TileRectangle);
    }
}

#define PushTile(Tile, Rectangle) _PushTile(RenderData, Tile, Rectangle)
static void
_PushTile(render_data* RenderData, tile Tile, rect GameRectangle)
{
    rect TileRectangle = {};
    TileRectangle.X = GameRectangle.X + 1 + Tile.X * TILE_SIZE;
    TileRectangle.Y = GameRectangle.Y - 1 + GameRectangle.H - (Tile.Y + 1) * TILE_SIZE;
    TileRectangle.W = TILE_SIZE;
    TileRectangle.H = TILE_SIZE;

    v4 TileBorderColor = { 255.0f, 255.0f, 255.0f, 255.0f };
    PushQuad(Tile.Color, TileBorderColor, TileRectangle);
}

void
RenderGameScene(render_data* RenderData, game_scene* Game)
{
    PushBackground(Game->BackgroundColor);

    PushText("Score:", Game->ScoreTextRectangle);
    PushText(Game->ScoreString, Game->ScoreCountRectangle);

    PushText("Line Count:", Game->LineCountTextRectangle);
    PushText(Game->LineCountString, Game->LineCountRectangle);

    PushQuad(Game->NextTetrominoRectangleColor, Game->NextTetrominoRectangleBorderColor, Game->NextTetrominoRectangle);

    PushPreviewTetromino(Game->NextTetromino, Game->NextTetrominoRectangle);

    PushQuad(Game->GameRectangleColor, Game->GameRectangleBorderColor, Game->GameRectangle);

    for(u32 i = 0; i < TILE_COUNT_Y; ++i)
    {
        for(u32 j = 0; j < TILE_COUNT_X; ++j)
        {
            if(Game->Tiles[i][j].IsDrawn)
            {
                PushTile(Game->Tiles[i][j], Game->GameRectangle);
            }
        }
    }

    for(u32 i = 0; i < 4; ++i)
    {
        if(Game->Tetromino.Tiles[i].Y < TILE_COUNT_Y)
        {
            PushTile(Game->Tetromino.Tiles[i], Game->GameRectangle);
        }
    }
}
