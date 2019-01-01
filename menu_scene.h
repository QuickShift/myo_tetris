#pragma once

#include "render_common.h"

struct menu_scene
{
    v4 BackgroundColor;

    v4 PlayColor;
    v4 InfoColor;
    v4 ExitColor;

    rect PlayRectangle;
    rect InfoRectangle;
    rect ExitRectangle;
};

void InitMenuScene(menu_scene* Menu);
void RenderMenuScene(render_data* RenderData, menu_scene* Menu);
