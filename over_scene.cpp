#include "over_scene.h"

void
InitOverScene(over_scene* Over)
{
    Over->BackgroundColor = v4{ 50.0f, 50.0f, 50.0f, 255.0f };

    rect GameOverTextRectangle = {};
    GameOverTextRectangle.X = 400;
    GameOverTextRectangle.Y = 200;
    GameOverTextRectangle.W = 200;
    GameOverTextRectangle.H = 50;
    Over->GameOverTextRectangle = GameOverTextRectangle;

    rect ScoreTextRectangle = {};
    ScoreTextRectangle.X = 400;
    ScoreTextRectangle.Y = 400;
    ScoreTextRectangle.W = 200;
    ScoreTextRectangle.H = 50;
    Over->ScoreTextRectangle = ScoreTextRectangle;

    rect ScoreCountRectangle = {};
    ScoreCountRectangle.X = 400;
    ScoreCountRectangle.Y = 450;
    ScoreCountRectangle.W = 200;
    ScoreCountRectangle.H = 50;
    Over->ScoreCountRectangle = ScoreCountRectangle;

    rect LineCountTextRectangle = {};
    LineCountTextRectangle.X = 400;
    LineCountTextRectangle.Y = 550;
    LineCountTextRectangle.W = 200;
    LineCountTextRectangle.H = 50;
    Over->LineCountTextRectangle = LineCountTextRectangle;

    rect LineCountRectangle = {};
    LineCountRectangle.X = 400;
    LineCountRectangle.Y = 600;
    LineCountRectangle.W = 200;
    LineCountRectangle.H = 50;
    Over->LineCountRectangle = LineCountRectangle;
}

void
RenderOverScene(render_data* RenderData, over_scene* Over)
{
    PushBackground(RenderData, Over->BackgroundColor);

    PushText(RenderData, "Game Over!", Over->GameOverTextRectangle);

    PushText(RenderData, "Score:", Over->ScoreTextRectangle);
    PushText(RenderData, Over->ScoreString, Over->ScoreCountRectangle);

    PushText(RenderData, "Line Count:", Over->LineCountTextRectangle);
    PushText(RenderData, Over->LineCountString, Over->LineCountRectangle);
}
