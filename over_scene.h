#pragma once

#include "render_common.h"

struct over_scene
{
    u32 LastOverTime;

    v4 BackgroundColor;

    rect GameOverTextRectangle;
    rect ScoreTextRectangle;
    rect ScoreCountRectangle;
    rect LineCountTextRectangle;
    rect LineCountRectangle;

    char ScoreString[10];
    char LineCountString[10];
};

void InitOverScene(over_scene* Over);
void RenderOverScene(render_data* RenderData, over_scene* Over);
