#pragma once
#include <map>
#include <functional>
#include "raylib.h"
#include "../../packages/raygui/src/raygui.h"

class GUI
{
  public:
    GUI();
    ~GUI();

    std::function<void(int layer)> onHoverGUI;
    std::function<void(int layer)> onClickGUI;
    std::function<void()> onMouseLeaveGUI;
    std::function<void()> onBackButtonClicked;
    std::function<void()> onSaveButtonClicked;

    bool getGridSize();
    void drawLayersHint(std::map<int, Color> layerColor, int currentLayer, int maxLayer);
    void drawBackButton();
    void drawHints();
    void setCellSize(int cellSize);
    void drawSaveButton();
    void showFileBeenSaved(double currentTime);
    bool fileBeenSaved = false;

    int mapWidth;
    int mapHeight;
  private:
    const float textBoxWidth = 65;
    const float textBoxHeight = 65;
    char textBoxWidthText[35] = "map width";
    char textBoxHeightText[35] = "map height";
    bool isInEditModTextBoxWidth = false;
    bool isInEditModTextBoxHeight = false;
    Rectangle textBoxWidthRect = {(float)GetScreenWidth() / 2 - textBoxWidth / 2, (float)GetScreenHeight() / 2 - textBoxHeight / 2 - textBoxHeight, textBoxWidth, textBoxHeight};
    Rectangle textBoxHeightRect = {(float)GetScreenWidth() / 2 - textBoxWidth / 2, (float)GetScreenHeight() / 2 - textBoxHeight / 2 + textBoxHeight / 2, textBoxWidth, textBoxHeight};
    const int mapWidthMin = 4;
    const int mapHeightMin = 4;
    const int mapWidthMax = 64;
    const int mapHeightMax = 64;
    const float timeToShowFileBeenSaved = 2.0f;

    Rectangle cellRect = {0, 0, 0, 0};
    Rectangle helpRect = {5, 5, 35, 35};
    Rectangle continueRect = {(float)GetScreenWidth() / 2 - 17, ((float)GetScreenHeight() / 2 - textBoxHeight / 2 + textBoxHeight / 2) + 100, 35, 35};
    Rectangle backButtonRect = {5, (float)GetScreenHeight() - 40, 35, 35};
    Rectangle saveButtonRect = {(float)GetScreenWidth() - 95, 5, 90, 35};
    bool drawHelpRect = false;
    int cellSize = 0;
    const int offsetX = 50;
    int offsetY = 0;
    const float lineThick = 3.5f;
    const Color cellLinesCurrentLayerColor = {255, 215, 30, 255};
    const Color hintColor = ORANGE;

    void inputHandler(int layer);
    void sanitizeInput(char *buffer);
};
