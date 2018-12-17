#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"

#define USE_MYO 0
#if USE_MYO
#include <myo/libmyo.h>
#include <math.h>
#endif

static b32
Init(SDL_Window** Window, SDL_Renderer** Renderer)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL_Init failed!\nERROR: %s\n", SDL_GetError());
        return false;
    }

    *Window = SDL_CreateWindow("Myo Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if(!*Window)
    {
        printf("SDL_CreateWindow failed!\nERROR: %s\n", SDL_GetError());
        return false;
    }

    *Renderer = SDL_CreateRenderer(*Window, -1, SDL_RENDERER_ACCELERATED);

    if(!*Renderer)
    {
        printf("SDL_CreateRenderer failed!\nERROR: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

static b32
ProcessInput(game_input* NewInput, game_input* OldInput)
{
    *NewInput = *OldInput;
    SDL_Event Event;

    while(SDL_PollEvent(&Event))
    {
        switch(Event.type)
        {
            case SDL_QUIT:
            {
                return false;
            } break;
            case SDL_KEYDOWN:
            {
                if(Event.key.keysym.sym == SDLK_a)
                {
                    NewInput->TranslateLeft.Down = true;
                }
                if(Event.key.keysym.sym == SDLK_s)
                {
                    NewInput->TranslateDown.Down = true;
                }
                if(Event.key.keysym.sym == SDLK_d)
                {
                    NewInput->TranslateRight.Down = true;
                }
                if(Event.key.keysym.sym == SDLK_LSHIFT)
                {
                    NewInput->RotateLeft.Down = true;
                }
                if(Event.key.keysym.sym == SDLK_SPACE)
                {
                    NewInput->RotateRight.Down = true;
                }
                if(Event.key.keysym.sym == SDLK_TAB)
                {
                    NewInput->Back.Down = true;
                }
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    NewInput->Exit.Down = true;
                }
            } break;
            case SDL_KEYUP:
            {
                if(Event.key.keysym.sym == SDLK_a)
                {
                    NewInput->TranslateLeft.Down = false;
                }
                if(Event.key.keysym.sym == SDLK_s)
                {
                    NewInput->TranslateDown.Down = false;
                }
                if(Event.key.keysym.sym == SDLK_d)
                {
                    NewInput->TranslateRight.Down = false;
                }
                if(Event.key.keysym.sym == SDLK_LSHIFT)
                {
                    NewInput->RotateLeft.Down = false;
                }
                if(Event.key.keysym.sym == SDLK_SPACE)
                {
                    NewInput->RotateRight.Down = false;
                }
                if(Event.key.keysym.sym == SDLK_TAB)
                {
                    NewInput->Back.Down = false;
                }
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    NewInput->Exit.Down = false;
                }
            } break;
        }
    }

    for(u32 i = 0; i < ArrayCount(NewInput->Keys); ++i)
    {
        NewInput->Keys[i].Changed = NewInput->Keys[i].Down == OldInput->Keys[i].Down ? false : true;
    }

    NewInput->Time = SDL_GetTicks();

    *OldInput = *NewInput;

    return true;
}

#if USE_MYO
struct myo_input
{
    libmyo_pose_t Pose;
    struct
    {
        float X;
        float Y;
        float Z;
        float W;
    } Quaternion;
    struct
    {
        float Roll;
        float Pitch;
        float Yaw;
    } Euler;
    struct
    {
        float A;
        float B;
        float C;
    } Accelerometer;
    struct
    {
        float A;
        float B;
        float C;
    } Gyroscope;
};

static libmyo_handler_result_t
GetMyoDevice(void* user_data, libmyo_event_t event)
{
    libmyo_myo_t* MyoDevice = (libmyo_myo_t*)user_data;

    if(libmyo_event_get_type(event) == libmyo_event_paired)
    {
        *MyoDevice = libmyo_event_get_myo(event);
        return libmyo_handler_stop;
    }
    return libmyo_handler_continue;
}

static libmyo_handler_result_t
GetMyoInput(void* user_data, libmyo_event_t event)
{
    myo_input* MyoInput = (myo_input*)user_data;

    switch(libmyo_event_get_type(event))
    {
        case libmyo_event_orientation:
        {
            MyoInput->Quaternion.X = libmyo_event_get_orientation(event, libmyo_orientation_x);
            MyoInput->Quaternion.Y = libmyo_event_get_orientation(event, libmyo_orientation_y);
            MyoInput->Quaternion.Z = libmyo_event_get_orientation(event, libmyo_orientation_z);
            MyoInput->Quaternion.W = libmyo_event_get_orientation(event, libmyo_orientation_w);

            MyoInput->Accelerometer.A = libmyo_event_get_accelerometer(event, 0);
            MyoInput->Accelerometer.B = libmyo_event_get_accelerometer(event, 1);
            MyoInput->Accelerometer.C = libmyo_event_get_accelerometer(event, 2);

            MyoInput->Gyroscope.A = libmyo_event_get_gyroscope(event, 0);
            MyoInput->Gyroscope.B = libmyo_event_get_gyroscope(event, 1);
            MyoInput->Gyroscope.C = libmyo_event_get_gyroscope(event, 2);
        } break;
        case libmyo_event_pose:
        {
            MyoInput->Pose = libmyo_event_get_pose(event);
        } break;
    }

    return libmyo_handler_continue;
}

static b32
MyoInputConverter(game_input* NewInput, game_input* OldInput, myo_input* NewMyoInput, myo_input* OldMyoInput)
{
    // printf("\nQuaternion:\nX = %f\nY = %f\nZ = %f\nW = %f\n", NewMyoInput->Quaternion.X, NewMyoInput->Quaternion.Y, NewMyoInput->Quaternion.Z, NewMyoInput->Quaternion.W);

    float X = NewMyoInput->Quaternion.X;
    float Y = NewMyoInput->Quaternion.Y;
    float Z = NewMyoInput->Quaternion.Z;
    float W = NewMyoInput->Quaternion.W;
    float SinR_CosP = 2.0f * (W * X + Y * Z);
    float CosR_CosP = 1.0f + 2.0f * (X * X + Y * Y);
    float SinP = 2.0f * (W * Y - Z * X);
    float SinY_CosP = 2.0f * (W * Z + X * Y);
    float CosY_CosP = 1.0f - 2.0f * (Y * Y + Z * Z);

    NewMyoInput->Euler.Roll = atan2(SinR_CosP, CosR_CosP);
    NewMyoInput->Euler.Pitch = fabs(SinP) >= 1 ? copysign(M_PI / 2.0f, SinP) : asin(SinP);
    NewMyoInput->Euler.Yaw = atan2(SinY_CosP, CosY_CosP);

    printf("\nRoll (x) = %f\nPitch (y) = %f\nYaw (z) = %f\n", NewMyoInput->Euler.Roll, NewMyoInput->Euler.Pitch, NewMyoInput->Euler.Yaw);

    if(NewMyoInput->Pose == libmyo_pose_fist)
    {
        NewInput->TranslateDown.Down = true;
    }
    else
    {
        NewInput->TranslateDown.Down = false;
    }

    if(NewMyoInput->Pose == libmyo_pose_wave_in)
    {
        NewInput->TranslateLeft.Down = true;
    }
    else
    {
        NewInput->TranslateLeft.Down = false;
    }

    if(NewMyoInput->Pose == libmyo_pose_wave_out)
    {
        NewInput->TranslateRight.Down = true;
    }
    else
    {
        NewInput->TranslateRight.Down = false;
    }

    if(NewMyoInput->Pose == libmyo_pose_fingers_spread)
    {
        NewInput->RotateLeft.Down = true;
    }
    else
    {
        NewInput->RotateLeft.Down = false;
    }

#if 0
    if(NewMyoInput->Pose == libmyo_pose_fist && NewMyoInput->Euler.Yaw > 0.0f)
    {
        NewInput->RotateRight.Down = true;
    }
    else
    {
        NewInput->RotateRight.Down = false;
    }
#endif

    if(NewMyoInput->Pose == libmyo_pose_double_tap && NewMyoInput->Euler.Pitch >= 0.75f)
    {
        NewInput->Back.Down = true;
    }
    else
    {
        NewInput->Back.Down = false;
    }

    if(NewMyoInput->Pose == libmyo_pose_fingers_spread && NewMyoInput->Euler.Pitch >= 0.75f)
    {
        NewInput->Exit.Down = true;
    }

    for(u32 i = 0; i < ArrayCount(NewInput->Keys); ++i)
    {
        NewInput->Keys[i].Changed = NewInput->Keys[i].Down == OldInput->Keys[i].Down ? false : true;
    }

    NewInput->Time = SDL_GetTicks();
    printf("dt = %d ms\n", NewInput->Time - OldInput->Time);

    *OldInput = *NewInput;
    *OldMyoInput = *NewMyoInput;

    return true;
}
#endif

int
main(int ArgCount, char** Args)
{
    Platform::SetHighDPIAwareness();

    SDL_Window* Window = 0;
    SDL_Renderer* Renderer = 0;

    if(!Init(&Window, &Renderer))
    {
        return -1;
    }

    if(TTF_Init() == -1)
    {
        printf("ERROR: Failed to initialize TTF.\n%s\n", SDL_GetError());
    }

    srand(time(NULL));

    game_memory GameMemory = {};
    GameMemory.MemorySize = Mibibytes(10);
    GameMemory.Memory = calloc(1, GameMemory.MemorySize);
    if(GameMemory.Memory)
    {
        GameMemory.IsInit = true;
    }
    else
    {
        printf("ERROR: Memory allocation failed!\n");
        Assert(0);
    }

#if USE_MYO
    libmyo_hub_t MyoHub;
    libmyo_error_details_t MyoError;

    libmyo_result_t MyoResult = libmyo_init_hub(&MyoHub, "com.test.myo_tetris", &MyoError);
    if(MyoResult != libmyo_success)
    {
        printf("Error initializing MyoHub: %s\n", libmyo_error_cstring(MyoError));
        return 1;
    }
    printf("MyoHub initialized.\n");

    MyoResult = libmyo_set_locking_policy(MyoHub, libmyo_locking_policy_none, &MyoError);
    if(MyoResult != libmyo_success)
    {
        printf("Error setting MyoHub locking policy: %s\n", libmyo_error_cstring(MyoError));
        MyoResult = libmyo_shutdown_hub(MyoHub, &MyoError);
        return 1;
    }

    libmyo_myo_t MyoDevice;
    MyoResult = libmyo_run(MyoHub, 10000, GetMyoDevice, &MyoDevice, &MyoError);
    if(MyoResult != libmyo_success)
    {
        printf("Error pairing with Myo Armband device: %s\n", libmyo_error_cstring(MyoError));
        MyoResult = libmyo_shutdown_hub(MyoHub, &MyoError);
        return 1;
    }
    printf("Myo Armband device found.\n");

    MyoResult = libmyo_myo_unlock(MyoDevice, libmyo_unlock_hold, &MyoError);
    if(MyoResult != libmyo_success)
    {
        printf("Error unlocking Myo Armband device: %s\n", libmyo_error_cstring(MyoError));
        MyoResult = libmyo_shutdown_hub(MyoHub, &MyoError);
        return 1;
    }
    printf("Myo Armband unlocked.\n");

    myo_input NewMyoInput = {};
    myo_input OldMyoInput = {};
#endif

    game_input OldInput = {};
    game_input NewInput = {};
    for(;;)
    {
#if USE_MYO == 0
        if(!ProcessInput(&NewInput, &OldInput))
        {
            break;
        }
#endif

#if USE_MYO
        MyoResult = libmyo_run(MyoHub, 4, GetMyoInput, &NewMyoInput, &MyoError);
        MyoInputConverter(&NewInput, &OldInput, &NewMyoInput, &OldMyoInput);
#endif

        if(NewInput.Exit.Down)
        {
            break;
        }

        GameUpdateAndRender(GameMemory, NewInput, Renderer);

        SDL_RenderPresent(Renderer);
#if USE_MYO == 0
        SDL_Delay(FRAME_TIME_MS);
#endif
    }

#if USE_MYO
    MyoResult = libmyo_myo_unlock(MyoDevice, libmyo_unlock_timed, &MyoError);
    if(MyoResult != libmyo_success)
    {
        printf("Error setting Myo Armband device lock: %s\n", libmyo_error_cstring(MyoError));
        MyoResult = libmyo_shutdown_hub(MyoHub, &MyoError);
        return 1;
    }
    printf("Myo Armband unlock set to timed .\n");

    MyoResult = libmyo_shutdown_hub(MyoHub, &MyoError);
#endif

    free(GameMemory.Memory);
    TTF_Quit();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);

    SDL_Quit();

    return 0;
}
