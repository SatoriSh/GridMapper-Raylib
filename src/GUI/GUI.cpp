#include "GUI.h"

GUI::GUI()
{
}

void GUI::drawLayersHint(std::map<int, Color> layerColor, int currentLayer, int maxLayer)
{
    float totalHeight = (maxLayer + 1) * cellSize + maxLayer * (offsetY - cellSize); // (offsetY - cellSize) = 8px offsetY if cellSize = 16
    int y = (GetScreenHeight() / 2) - (totalHeight / 2);

    for (int i = maxLayer; i >= 0; i--)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            currentLayer = 0;

        cellRect = {(float)GetScreenWidth() - offsetX, (float)y, (float)cellSize, (float)cellSize};

        inputHandler(i);

        DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, layerColor[i]);
        if (i == currentLayer)
            DrawRectangleLinesEx(cellRect, lineThick, cellLinesCurrentLayerColor);

        y += offsetY;
    }
}

void GUI::inputHandler(int layer) const
{
    if (CheckCollisionPointRec(GetMousePosition(), cellRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        onClickGUI(layer);
}

void GUI::setCellSize(int cellSize)
{
    this->cellSize = cellSize;
    offsetY = cellSize + cellSize / 2;
}

GUI::~GUI()
{
}
