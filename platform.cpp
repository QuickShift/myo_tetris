#include <windows.h>
#include <stdio.h>
#include <ShellScalingAPI.h>

#include "common.h"

void
Platform::SetHighDPIAwareness()
{
    if(SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE) != S_OK)
    {
        printf("DPI awareness was not set!\n");
    }
}

s64 g_PerformanceFrequency = 0;

float
Platform::GetTimeInSeconds()
{
    if(g_PerformanceFrequency == 0){
        LARGE_INTEGER PerformanceFrequencyResult;
        QueryPerformanceFrequency(&PerformanceFrequencyResult);
        g_PerformanceFrequency = PerformanceFrequencyResult.QuadPart;
    }

    LARGE_INTEGER CurrentPerformanceCounter;
    QueryPerformanceCounter(&CurrentPerformanceCounter);
    return (r32)CurrentPerformanceCounter.QuadPart/(r32)g_PerformanceFrequency;
}
