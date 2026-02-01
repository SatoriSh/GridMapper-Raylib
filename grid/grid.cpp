#include "grid.h"

Grid::Grid() : backgroundColor(GRAY)
{
    InitWindow(screenWidth, screenHeight, "GridMapper-Raylib");
    SetTargetFPS(FPS);
}

void Grid::process()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);

        EndDrawing();
    }
}

void Grid::render()
{

}

Grid::~Grid()
{
    CloseWindow();
}
