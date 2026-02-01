#include <cmath>
#include "grid.h"

Grid::Grid() : gridWidth(30), gridHeight(30), cellSize(16)
{
    initWindow();
    initCells();

    userCamera.setCameraTarget({float(gridWidth * cellSize) / 2, float(gridHeight * cellSize) / 2});
}

void Grid::process()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);

        userCamera.process();

        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), userCamera.camera);
        mouseGridX = (int)floor(mouseWorldPos.x / cellSize);
        mouseGridY = (int)floor(mouseWorldPos.y / cellSize);

        BeginMode2D(userCamera.camera);
        render();
        EndMode2D();

        DrawText(TextFormat("MouseX: %d\n\nMouseY: %d", mouseGridX, mouseGridY), 15, 15, 20, WHITE);
        EndDrawing();
    }
}

void Grid::render()
{
    for (int y = 0; y < cells[0].size(); y++)
    {
        for (int x = 0; x < cells.size(); x++)
        {
            cells[x][y].updateHover(mouseGridX, mouseGridY);
            cells[x][y].render();
        }
    }
}

void Grid::initWindow()
{
    InitWindow(screenWidth, screenHeight, "GridMapper-Raylib");
    SetTargetFPS(FPS);
}

void Grid::initCells()
{
    for (int y = 0; y < gridHeight; y++)
    {
        cells.emplace_back();
        for (int x = 0; x < gridWidth; x++)
        {
            cells.back().emplace_back(x, y, cellSize);
        }
    }
}

Grid::~Grid()
{
    CloseWindow();
}

void Grid::Cell::render() const
{
    DrawRectangleLinesEx(rect, lineThick, cellLinesColor);
    DrawText(TextFormat("%d", layerNum), x * cellSize + cellSize / 4, y * cellSize + cellSize / 4, 10, layerNumColor);
}

void Grid::Cell::updateHover(int mouseGridX, int mouseGridY)
{
    if (x == mouseGridX && y == mouseGridY)
    {
        lineThick = hoverLineThick;
        isHovered = true;
    }
    else
    {
        lineThick = defaultLineThick;
        isHovered = false;
    }
}

Grid::Cell::Cell(int x, int y, int cellSize)
    : x(x), y(y), cellSize(cellSize)
{
    rect = {(float)x * cellSize, (float)y * cellSize, (float)cellSize, (float)cellSize};
}

Grid::Cell::~Cell()
{

}
