#pragma once

#include <stdint.h>

#define ArrayCount(Array) sizeof((Array)) / sizeof(Array[0])
#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}

#define Kibibytes(Count) (1024 * (Count))
#define Mibibytes(Count) (1024 * Kibibytes(Count))
#define Gibibytes(Count) (1024 * Mibibytes(Count))

#define FRAME_TIME_MS 15
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

typedef int8_t s8;
typedef int8_t s08;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef s32 b32;

typedef uint8_t u8;
typedef uint8_t u08;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float r32;
typedef double r64;
typedef float f32;
typedef double f64;

namespace Platform
{
    float GetTimeInSeconds();
    void  SetHighDPIAwareness();
}

struct key
{
    b32 Down;
    b32 Changed;
};

struct game_input
{
    union 
    {
        key Keys[7];
        struct
        {
            key TranslateLeft;
            key TranslateRight;
            key TranslateDown;
            key RotateLeft;
            key RotateRight;
            key Back;
            key Exit;
        };
    };
};

struct game_memory
{
    b32 IsInit;
    u32 MemorySize;
    void* Memory;
};

#include <SDL2/SDL.h>

#define GAME_UPDATE_AND_RENDER(name) void name(game_memory GameMemory, game_input Input, SDL_Renderer* Renderer)
typedef GAME_UPDATE_AND_RENDER(game_update_and_render);
game_update_and_render GameUpdateAndRender;
