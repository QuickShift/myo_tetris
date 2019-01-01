#pragma once

#include "render_common.h"

#define TILE_SIZE 40
#define TILE_COUNT_X 10
#define TILE_COUNT_Y 20

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
    u32 LastDownKeyTime;

    v4 GameRectangleColor;
    v4 GameRectangleBorderColor;
    v4 NextTetrominoRectangleColor;
    v4 NextTetrominoRectangleBorderColor;

    rect ScoreTextRectangle;
    rect ScoreCountRectangle;
    rect LineCountTextRectangle;
    rect LineCountRectangle;
    rect NextTetrominoRectangle;
    rect GameRectangle;

    tile Tiles[TILE_COUNT_Y][TILE_COUNT_X];

    b32 TetrominoStop;
    b32 TetrominoIsFalling;
    tetromino Tetromino;
    tetromino NextTetromino;

    u32 Score;
    u32 LineCount;

    char ScoreString[10];
    char LineCountString[10];

    u32 FullLineCount;
    u32 LineIndexes[TILE_COUNT_Y];
};

tetromino CreateTetromino(piece Type);
void InitGameScene(game_scene* Game);
void RenderGameScene(render_data* RenderData, game_scene* Game);
