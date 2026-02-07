#include <string>

#include "GUI.h"

GUI::GUI()
{
}

bool GUI::getGridSize()
{
    if (WindowShouldClose()) return true;

    BeginDrawing();

    ClearBackground({27, 38, 59, 255});

    GuiTextBox(textBoxWidthRect, textBoxWidthText, 35, isInEditModTextBoxWidth);
    GuiTextBox(textBoxHeightRect, textBoxHeightText, 35, isInEditModTextBoxHeight);

    DrawRectangleRounded(continueRect, 0.3f, 4, DARKBLUE);
    DrawText(">", continueRect.x + 13, continueRect.y + 5, 30, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), continueRect))
        DrawRectangleRoundedLinesEx(continueRect, 0.3f, 4, 1.15f, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), textBoxWidthRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isInEditModTextBoxWidth)
    {
        textBoxWidthText[0] = '\0';
        isInEditModTextBoxWidth = true;
        isInEditModTextBoxHeight = false;
    }
    else if (CheckCollisionPointRec(GetMousePosition(), textBoxHeightRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isInEditModTextBoxHeight)
    {
        textBoxHeightText[0] = '\0';
        isInEditModTextBoxHeight = true;
        isInEditModTextBoxWidth = false;
        
    }
    if (IsKeyPressed(KEY_ENTER) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !CheckCollisionPointRec(GetMousePosition(), textBoxWidthRect) && !CheckCollisionPointRec(GetMousePosition(), textBoxHeightRect)))
    {
        isInEditModTextBoxWidth = false;
        isInEditModTextBoxHeight = false;
    }

    if ((IsKeyPressed(KEY_ENTER) || (CheckCollisionPointRec(GetMousePosition(), continueRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) && textBoxWidthText[0] != '\0' && textBoxHeightText[0] != '\0')
    {
        try
        {
            sanitizeInput(textBoxWidthText);
            sanitizeInput(textBoxHeightText);

            std::string tempStringWidth(textBoxWidthText); // конвертируем массив char в строку
            if (!tempStringWidth.empty())
            {
                mapWidth = std::stoi(tempStringWidth);
            }

            std::string tempStringHeight(textBoxHeightText);
            if (!tempStringHeight.empty())
            {
                mapHeight = std::stoi(tempStringHeight);
            }

            if (mapWidth >= mapWidthMin && mapWidth <= mapWidthMax && mapHeight >= mapHeightMin && mapHeight <= mapHeightMax) 
            {
                return true;
            }
        }
        catch (...)
        {

        }
    }

    if (IsKeyPressed(KEY_TAB))
    {
        if (isInEditModTextBoxWidth)
        {
            isInEditModTextBoxWidth = false;
            isInEditModTextBoxHeight = true;
            textBoxHeightText[0] = '\0';
        }
        else if (isInEditModTextBoxHeight)
        {
            isInEditModTextBoxWidth = true;
            isInEditModTextBoxHeight = false;
            textBoxWidthText[0] = '\0';
        }
        else if (!isInEditModTextBoxWidth && !isInEditModTextBoxHeight)
        {
            textBoxWidthText[0] = '\0';
            isInEditModTextBoxWidth = true;
        }
    }

    if (!isInEditModTextBoxWidth && textBoxWidthText[0] == '\0')
    {
        strcpy_s(textBoxWidthText, "map width");
    }
    if (!isInEditModTextBoxHeight && textBoxHeightText[0] == '\0')
    {
        strcpy_s(textBoxHeightText, "map height");
    }

    EndDrawing();
    return false;
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

        DrawRectangleRounded(cellRect, 0.3f, 16, layerColor[i]);

        if (CheckCollisionPointRec(GetMousePosition(), cellRect))
        {
            DrawRectangleRoundedLinesEx(cellRect, 0.3f, 16, lineThick / 2, WHITE);
            currentHoveredInsideLoop = i;
        }

        if (i == currentLayer)
            DrawRectangleRoundedLinesEx(cellRect, 0.3f, 16, lineThick, cellLinesCurrentLayerColor);

        DrawText(TextFormat("%d", i), cellRect.x + cellSize / 2 - (i == 1 ? 1 : 4), cellRect.y + cellSize / 2 - 6, 12, {224, 225, 221, 255});

        y += offsetY;
    }

    currentHoveredInsideLoop != -1 ? onHoverGUI(currentHoveredInsideLoop) : onMouseLeaveGUI();
}

void GUI::drawHints()
{
    //DrawRectangleRec(helpRect, DARKBLUE);
    DrawRectangleRounded(helpRect, 0.3f, 16, DARKBLUE);
    DrawText("?", 15.5, 12, 25, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), helpRect))
        DrawRectangleRoundedLinesEx(helpRect, 0.3f, 16, 1.15f, WHITE);
    
    if (drawHelpRect)
    {
        int x = 12;
        int y = 60;

        DrawRectangleRounded({5, (float)y - 10, 240, 112}, 0.3f, 16, BLUE);
        DrawText("Select a layer: keys [0-9]", x, y, 17, WHITE);
        DrawText("Show/Hide layer numbers: N", x, y += 25, 17, WHITE);
        DrawText("Reset grid: R", x, y += 25, 17, WHITE);
        DrawText("Save grid: CTRL + S", x, y += 25, 17, WHITE);
    }
}

void GUI::drawBackButton()
{
    DrawRectangleRounded(backButtonRect, 0.3f, 16, DARKBLUE);
    DrawText("<", 16, GetScreenHeight() - 39, 35, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), backButtonRect))
        DrawRectangleRoundedLinesEx(backButtonRect, 0.3f, 16, 1.15f, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), backButtonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        onBackButtonClicked();
        fileBeenSaved = false;
        mapWidth = 0;
        mapHeight = 0;
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

void GUI::sanitizeInput(char *buffer)
{
    std::string s(buffer);
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }), s.end());
    snprintf(buffer, 35, "%s", s.c_str());
}

void GUI::setCellSize(int cellSize)
{
    this->cellSize = cellSize;
    offsetY = cellSize + cellSize / 2;
}

void GUI::showFileBeenSaved(double currentTime)
{
    if (fileBeenSaved)
    {
        if (GetTime() - currentTime <= timeToShowFileBeenSaved)
            DrawText("The file is saved!", GetScreenWidth() / 2 - 150, 50, 30, GREEN);
        else
            fileBeenSaved = false;
    }
}

void GUI::drawSaveButton()
{
    DrawRectangleRounded(saveButtonRect, 0.3f, 16, DARKBLUE);
    DrawText("save", GetScreenWidth() - 85, 7, 30, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), saveButtonRect))
        DrawRectangleRoundedLinesEx(saveButtonRect, 0.3f, 16, 1.15f, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), saveButtonRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        onSaveButtonClicked();
}

GUI::~GUI()
{
}
