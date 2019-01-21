#include "info_scene.h"

void
InitInfoScene(info_scene* Info)
{
    Info->BackgroundColor = v4{ 50.0f, 50.0f, 70.0f, 255.0f };

    rect ControlsRectangle = {};
    ControlsRectangle.X = 400;
    ControlsRectangle.Y = 100;
    ControlsRectangle.W = 200;
    ControlsRectangle.H = 50;
    Info->ControlsRectangle = ControlsRectangle;

    Info->TextRectangleCount = 15;
    Assert(Info->TextRectangleCount < MAX_TEXT_RECTANGLE_COUNT);
    for(u32 i = 0; i < Info->TextRectangleCount; ++i)
    {
        rect TextRectangle = {};
        TextRectangle.X = 100;
        TextRectangle.Y = 200 + i * 50;
        TextRectangle.W = 800;
        TextRectangle.H = 50;
        Info->TextRectangles[i] = TextRectangle;
    }
}

void
RenderInfoScene(render_data* RenderData, info_scene* Info)
{
    PushBackground(RenderData, Info->BackgroundColor);

    PushText(RenderData, "Controls", Info->ControlsRectangle);

    PushText(RenderData, "Depending on the flag set in the game", Info->TextRectangles[0]);
    PushText(RenderData, "code, you can control the game", Info->TextRectangles[1]);
    PushText(RenderData, "in 2 ways - Myo Armband or Keyboard", Info->TextRectangles[2]);
    PushText(RenderData, " ", Info->TextRectangles[3]);
    PushText(RenderData, "Move left - Wave In (A key)", Info->TextRectangles[4]);
    PushText(RenderData, "Move right - Wave Out (D key)", Info->TextRectangles[5]);
    PushText(RenderData, "Rotate - Spread Fingers (Shift key)", Info->TextRectangles[6]);
    PushText(RenderData, "Move down - Fist (S key)", Info->TextRectangles[7]);
    PushText(RenderData, "Back - Double Tap (Tab key)", Info->TextRectangles[8]);
    PushText(RenderData, "Exit game - Spread Fingers with", Info->TextRectangles[9]);
    PushText(RenderData, "the arm pitched 45 degrees (Escape key)", Info->TextRectangles[10]);
}
