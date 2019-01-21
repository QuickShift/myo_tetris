#pragma once

#include "common.h"
#include "render_data.h"

void PushBackground(render_data* RenderData, v4 Color);
void PushQuad(render_data* RenderData, v4 Color, v4 BorderColor, rect Rectangle);
void PushText(render_data* RenderData, char* Text, rect Rectangle);
void PushTextQuad(render_data* RenderData, char* Text, v4 Color, rect Rectangle);
