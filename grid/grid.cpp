#include <cmath>
#include "grid.h"

Grid::Grid() : gridWidth(30), gridHeight(30), cellSize(16)
{
    initWindow();

    camera = {0};
    camera.target = {0.0f, 0.0f};
    camera.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f}; 
    camera.zoom = 1.0f;                                
    camera.rotation = 0.0f;
}

void Grid::process()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);

        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        int mouseGridX = (int)floor(mouseWorldPos.x / cellSize);
        int mouseGridY = (int)floor(mouseWorldPos.y / cellSize);

        BeginMode2D(camera);
        render();
        EndMode2D();

        DrawText(TextFormat("MouseX: %d\n\nMouseY: %d", mouseGridX, mouseGridY), 15, 15, 20, WHITE);
        EndDrawing();
    }
}

void Grid::render()
{
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize, cellLinesColor);
            DrawText("0", x * cellSize + cellSize / 4, y * cellSize + cellSize / 4, 10, GREEN);
        }
    }
}

void Grid::initWindow()
{
    InitWindow(screenWidth, screenHeight, "GridMapper-Raylib");
    SetTargetFPS(FPS);
}

Grid::~Grid()
{
    CloseWindow();
}
