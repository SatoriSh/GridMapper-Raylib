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

        if (IsKeyPressed(KEY_R))
            resetCells();

        BeginMode2D(userCamera.camera);
        render();
        EndMode2D();

        DrawText(TextFormat("MouseX: %d\nMouseY: %d", mouseGridX, mouseGridY), 15, 15, 20, WHITE);
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
            cells[x][y].updateCellLayer();
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
            cells.back().emplace_back(x, y, cellSize, minLayer, maxLayer);
        }
    }
}

void Grid::resetCells()
{
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            cells[x][y].layer = 0;
        }
    }
}

Grid::~Grid()
{
    CloseWindow();
}

Grid::Cell::Cell(int x, int y, int cellSize, int minLayer, int maxLayer)
    : x(x), y(y), cellSize(cellSize), minLayer(minLayer), maxLayer(maxLayer)
{
    rect = {(float)x * cellSize, (float)y * cellSize, (float)cellSize, (float)cellSize};

    layerColor[0] = {34, 51, 82, 255};
    layerColor[1] = {33, 47, 69, 255};
    layerColor[2] = {46, 68, 105, 255};
    layerColor[3] = {62, 88, 121, 255};
    layerColor[4] = {83, 113, 145, 255};
    layerColor[5] = {60, 130, 140, 255};
    layerColor[6] = {70, 110, 90, 255};
    layerColor[7] = {120, 90, 80, 255};
    layerColor[8] = {94, 84, 115, 255};
    layerColor[9] = {20, 30, 50, 255};
}

void Grid::Cell::render() 
{
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, layerColor.at(layer));
    DrawRectangleLinesEx(rect, lineThick, isHovered ? cellLinesHoverColor : cellLinesColor);
    DrawText(TextFormat("%d", layer), x * cellSize + cellSize / 3, y * cellSize + cellSize / 5, 11, layerNumColor);
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

void Grid::Cell::updateCellLayer()
{
    if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) || !isHovered)
        layerBeenChanged = false;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !layerBeenChanged && isHovered)
    {
        layer++;
        layerBeenChanged = true;
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && !layerBeenChanged && isHovered)
    {
        layer--;
        layerBeenChanged = true;
    }

    layer = Clamp(layer, minLayer, maxLayer);
}

Grid::Cell::~Cell()
{

}
