#pragma once

#include <stdint.h>

#define ArrayCount(Array) sizeof((Array)) / sizeof(Array[0])
#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}

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
