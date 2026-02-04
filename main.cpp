#include <memory>
#include "raylib.h"
#include "stdio.h"
#include "src/grid/grid.h"

const int screenWidth = 1280;
const int screenHeight = 720;
const int FPS = 60;

enum State
{
    GUIState,
    GRIDState
};

void initWindow()
{
    InitWindow(screenWidth, screenHeight, "GridMapper");
    SetTargetFPS(FPS);
}

int main()
{
    State currentState = GUIState;
    initWindow();
    auto gui = std::make_unique<GUI>();

    auto backCallback = [&currentState]() { currentState = GUIState; };
    gui->onBackButtonClicked = backCallback;

    Grid grid(std::move(gui));

    while (!WindowShouldClose())
    {
        switch (currentState)
        {
        case GUIState:
            if (grid.gui->getGridSize())
            {
                grid.reset(grid.gui->mapWidth, grid.gui->mapHeight);
                currentState = GRIDState;
            }
            break;
        case GRIDState:
            grid.process();
            break;
        }
    }
    return 0;
}
