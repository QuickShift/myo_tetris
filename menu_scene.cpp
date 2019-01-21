#include "menu_scene.h"

void
InitMenuScene(menu_scene* Menu)
{
    Menu->BackgroundColor = v4{ 100.0f, 100.0f, 100.0f, 255.0f };
    Menu->PlayColor = v4{ 50.0f, 150.0f, 0.0f, 255.0f };
    Menu->InfoColor = v4{ 0.0f, 50.0f, 100.0f, 255.0f };
    Menu->ExitColor = v4{ 150.0f, 0.0f, 0.0f, 255.0f };

    rect PlayRectangle = {};
    PlayRectangle.X = 200;
    PlayRectangle.Y = 200;
    PlayRectangle.W = 600;
    PlayRectangle.H = 100;
    Menu->PlayRectangle = PlayRectangle;

    rect InfoRectangle = {};
    InfoRectangle.X = 200;
    InfoRectangle.Y = 450;
    InfoRectangle.W = 600;
    InfoRectangle.H = 100;
    Menu->InfoRectangle = InfoRectangle;

    rect ExitRectangle = {};
    ExitRectangle.X = 200;
    ExitRectangle.Y = 700;
    ExitRectangle.W = 600;
    ExitRectangle.H = 100;
    Menu->ExitRectangle = ExitRectangle;
}

void
RenderMenuScene(render_data* RenderData, menu_scene* Menu)
{
    PushBackground(RenderData, Menu->BackgroundColor);

    PushTextQuad(RenderData, "Play (Wave Out)", Menu->PlayColor, Menu->PlayRectangle);
    PushTextQuad(RenderData, "Info (Wave In)", Menu->InfoColor, Menu->InfoRectangle);
    PushTextQuad(RenderData, "Exit (Spread Fingers)", Menu->ExitColor, Menu->ExitRectangle);
}
