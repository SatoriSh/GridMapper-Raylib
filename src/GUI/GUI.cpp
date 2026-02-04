#include "GUI.h"

GUI::GUI()
{
}

void GUI::drawLayersHint(std::map<int, Color> layerColor, int currentLayer, int maxLayer)
{
    float totalHeight = (maxLayer + 1) * cellSize + maxLayer * (offsetY - cellSize); // (offsetY - cellSize) = 8px offsetY if cellSize = 16
    int y = (GetScreenHeight() / 2) - (totalHeight / 2);

    int currentHoveredInsideLoop = -1;

    for (int i = maxLayer; i >= 0; i--)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            currentLayer = 0;

        cellRect = {(float)GetScreenWidth() - offsetX, (float)y, (float)cellSize, (float)cellSize};

        inputHandler(i);

        DrawRectangle(cellRect.x, cellRect.y, cellRect.width, cellRect.height, layerColor[i]);

        if (CheckCollisionPointRec(GetMousePosition(), cellRect))
        {
            DrawRectangleLinesEx(cellRect, lineThick / 2, WHITE);
            currentHoveredInsideLoop = i;
        }

        if (i == currentLayer)
            DrawRectangleLinesEx(cellRect, lineThick, cellLinesCurrentLayerColor);

        DrawText(TextFormat("%d", i), cellRect.x + cellSize / 2 - 4, cellRect.y + cellSize / 2 - 6, 12, {224, 225, 221, 255});

        y += offsetY;
    }

    currentHoveredInsideLoop != -1 ? onHoverGUI(currentHoveredInsideLoop) : onMouseLeaveGUI();
}

void GUI::drawHints()
{
    DrawRectangleRec(helpRect, DARKBLUE);
    DrawText("H", 16, 14, 20, WHITE);
    
    if (drawHelpRect)
    {
        int y = 60;
        DrawRectangle(5, y - 10, 240, 85, BLUE);
        DrawText("Select a layer: keys [0-9]", 10, y, 17, WHITE);
        DrawText("Show/Hide layer numbers: N", 10, y += 25, 17, WHITE);
        DrawText("Reset grid: R", 10, y += 25, 17, WHITE);
    }
}

void GUI::inputHandler(int layer)
{
    if (CheckCollisionPointRec(GetMousePosition(), cellRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        onClickGUI(layer);

    if (CheckCollisionPointRec(GetMousePosition(), helpRect))
        drawHelpRect = true;
    else if (!CheckCollisionPointRec(GetMousePosition(), helpRect) && !IsKeyDown(KEY_H))
        drawHelpRect = false;

    if (IsKeyDown(KEY_H))
        drawHelpRect = true;
}

void GUI::setCellSize(int cellSize)
{
    this->cellSize = cellSize;
    offsetY = cellSize + cellSize / 2;
}

GUI::~GUI()
{
}
