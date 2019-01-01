#pragma once

#include "common.h"
#include "render_data.h"

#define PushBackground(Color) _PushBackgroundColor(RenderData, Color)
#define PushQuad(Color, BorderColor, Rectangle) _PushQuad(RenderData, Color, BorderColor, Rectangle)
#define PushText(Text, Rectangle) _PushText(RenderData, Text, Rectangle)
#define PushTextQuad(Text, Color, Rectangle) _PushTextQuad(RenderData, Text, Color, Rectangle)

void _PushBackgroundColor(render_data* RenderData, v4 Color);
void _PushQuad(render_data* RenderData, v4 Color, v4 BorderColor, rect Rectangle);
void _PushText(render_data* RenderData, char* Text, rect Rectangle);
void _PushTextQuad(render_data* RenderData, char* Text, v4 Color, rect Rectangle);
