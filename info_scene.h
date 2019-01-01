#pragma once

#include "render_common.h"

#define MAX_TEXT_RECTANGLE_COUNT 20

struct info_scene
{
    v4 BackgroundColor;

    rect ControlsRectangle;

    u32 TextRectangleCount;
    rect TextRectangles[MAX_TEXT_RECTANGLE_COUNT];
};

void InitInfoScene(info_scene* Info);
void RenderInfoScene(render_data* RenderData, info_scene* Info);
