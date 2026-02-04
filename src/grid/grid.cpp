#include <cmath>
#include "grid.h"

#include <iostream>

Grid::Grid(std::unique_ptr<GUI> guiPtr) : gui(std::move(guiPtr)), cellSize(16)
{
    initCells();
    initLayerColors();
    initGUI();
    initUserCamera();
}

void Grid::reset(int gridWidth, int gridHeight)
{
    cells.clear();
    this->gridWidth = gridWidth;
    this->gridHeight = gridHeight;
    initCells();
    initUserCamera();
}

void Grid::process()
{
    BeginDrawing();
    ClearBackground(backgroundColor);

    userCamera.process();

    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), userCamera.camera);
    mouseGridX = (int)floor(mouseWorldPos.x / cellSize);
    mouseGridY = (int)floor(mouseWorldPos.y / cellSize);

    inputHandler();

    BeginMode2D(userCamera.camera);
    render();

    EndDrawing();
}

void Grid::render()
{
    drawGrid();
    EndMode2D();
    gui->drawHints();
    gui->drawLayersHint(layerColor, currentLayer, maxLayer);
    gui->drawBackButton();
}

void Grid::drawGrid()
{
    for (int y = 0; y < cells[0].size(); y++)
    {
        for (int x = 0; x < cells.size(); x++)
        {
            cells[x][y].updateHover(mouseGridX, mouseGridY);
            cells[x][y].render(drawLayerNums, layerColor[cells[x][y].layer], cells[x][y].layer == hoveredGUILayer ? hoveredGUILayer : -1);
            cells[x][y].updateCellLayer(currentLayer);
        }
    }
}

void Grid::resetCells()
{
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridWidth; x++)
        {
            cells[x][y].layer = minLayer;
        }
    }
}

void Grid::inputHandler()
{
    if (IsKeyPressed(KEY_R))
        resetCells();

    if (IsKeyPressed(KEY_N))
        drawLayerNums = !drawLayerNums;

    for (int i = minLayer; i < maxLayer + 1; i++)
    {
        if (IsKeyPressed(KEY_ZERO + i))
            currentLayer = i;
    }
}

void Grid::initCells()
{
    for (int y = 0; y < gridHeight; y++)
    {
        cells.emplace_back();
        for (int x = 0; x < gridWidth; x++)
        {
            Rectangle cellRect = {(float)x * cellSize, (float)y * cellSize, (float)cellSize, (float)cellSize};
            cells.back().emplace_back(x, y, cellSize, cellRect, minLayer, maxLayer);
        }
    }
}

void Grid::initLayerColors()
{
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

void Grid::initGUI()
{
    gui->setCellSize(cellSize * 2);
    gui->onClickGUI = [this](int layer) { currentLayer = layer; };
    gui->onHoverGUI = [this](int layer) { hoveredGUILayer = layer; };
    gui->onMouseLeaveGUI = [this]() { hoveredGUILayer = -1; };
}

void Grid::initUserCamera()
{
    userCamera.setCameraTarget({float(gridWidth * cellSize) / 2, float(gridHeight * cellSize) / 2});
    userCamera.setCameraWorldBounds({(float)-GetScreenWidth() / 2, (float)-GetScreenHeight() / 2, (float)GetScreenWidth(), (float)GetScreenHeight() + GetScreenHeight() / 2});
}

Grid::~Grid()
{
    CloseWindow();
}

Grid::Cell::Cell(int x, int y, int cellSize, Rectangle cellRect, int minLayer, int maxLayer)
    : x(x), y(y), cellSize(cellSize), rect(cellRect), minLayer(minLayer), maxLayer(maxLayer)
{
}

void Grid::Cell::render(bool drawLayerNums, Color layerColor, int hoveredGUILayer)
{
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, layerColor);
    DrawRectangleLinesEx(rect, lineThick, isHovered || hoveredGUILayer == layer ? cellLinesHoverColor : cellLinesColor);

    if (drawLayerNums)
        DrawText(TextFormat("%d", layer), x * cellSize + cellSize / (layer == 1 ? 2.2f : 2.7f), y * cellSize + cellSize / 4.5, 6, layerNumColor);
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

void Grid::Cell::updateCellLayer(int currentLayer)
{
    if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) || IsKeyReleased(KEY_SPACE)) || !isHovered)
        layerBeenChanged = false;

    if (!isHovered)
        return;

    if ((IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyDown(KEY_SPACE)) && !layerBeenChanged)
    {
        layer = currentLayer;
        layerBeenChanged = true;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && !layerBeenChanged)
    {
        layer = 0;
        layerBeenChanged = true;
    }

    layer = Clamp(layer, minLayer, maxLayer);
}

Grid::Cell::~Cell()
{
}
