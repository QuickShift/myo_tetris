#include <string.h>

#include "render_common.h"

void
PushBackground(render_data* RenderData, v4 Color)
{
    RenderData->BackgroundColor = Color;
}

void
PushQuad(render_data* RenderData, v4 Color, v4 BorderColor, rect Rectangle)
{
    quad Quad = {};
    Quad.Rectangle = Rectangle;
    Quad.RectangleColor = Color;
    Quad.BorderColor = BorderColor;
    RenderData->Quads[RenderData->QuadCount++] = Quad;
}

void
PushText(render_data* RenderData, char* Text, rect Rectangle)
{
    string String = {};
    Assert(strlen(Text) < MAX_STRING_LENGTH);
    strcpy(String.String, Text);
    String.Rectangle = Rectangle;
    RenderData->Strings[RenderData->StringCount++] = String;
}

void
PushTextQuad(render_data* RenderData, char* Text, v4 Color, rect Rectangle)
{
    PushQuad(RenderData, Color, v4{ 0.0f, 0.0f, 0.0f, 255.0f }, Rectangle);
    PushText(RenderData, Text, Rectangle);
}
