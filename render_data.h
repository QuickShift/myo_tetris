#pragma once

#include "common.h"

#define MAX_QUAD_COUNT 100
#define MAX_STRING_COUNT 20
#define MAX_STRING_LENGTH 100

struct rect
{
    s32 X;
    s32 Y;
    s32 W;
    s32 H;
};

struct quad
{
    v4 RectangleColor;
    v4 BorderColor;
    rect Rectangle;
};

struct string
{
    char String[MAX_STRING_LENGTH];
    rect Rectangle;
};

struct render_data
{
    u32 QuadCount;
    u32 StringCount;

    v4 BackgroundColor;

    quad Quads[MAX_QUAD_COUNT];
    string Strings[MAX_STRING_COUNT];
};

#define GAME_UPDATE_AND_RENDER(name) void name(game_memory* GameMemory, game_input* Input, render_data* RenderData)
typedef GAME_UPDATE_AND_RENDER(game_update_and_render);
game_update_and_render GameUpdateAndRender;
