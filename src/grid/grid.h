#pragma once
#include <vector>
#include <map>
#include "raylib.h"
#include "../camera/UserCamera.h"
#include "../GUI/GUI.h"

class Grid
{
  public:
    Grid();
    ~Grid();

    void process();
  private:
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int FPS = 60;
    const int minLayer = 0;
    const int maxLayer = 9;
    const Color backgroundColor = {27, 38, 59, 255};
    int currentLayer = 1;
    int gridWidth;
    int gridHeight;
    int cellSize;
    int mouseGridX;
    int mouseGridY;
    bool drawLayerNums = true;
    int hoveredGUILayer = -1;
    UserCamera userCamera;
    GUI gui;
    std::map<int, Color> layerColor;
    void render();
    void drawGrid();
    void drawHints();
    void initWindow();
    void initCells();
    void initLayerColors();
    void initGUI();
    void initUserCamera();
    void resetCells();
    void inputHandler();

    struct Cell
    {
        Cell(int x, int y, int cellSize, Rectangle cellRect, int minLayer, int maxLayer);
        ~Cell();

        const int x;
        const int y;
        const int cellSize;
        const float defaultLineThick = 1.0f;
        const float hoverLineThick = 2.0f;
        Rectangle rect;
        int layer = 0;
        int minLayer;
        int maxLayer;
        bool layerBeenChanged = false;
        bool isHovered = false;
        float lineThick = defaultLineThick;
        const Color cellLinesColor = {65, 90, 119, 150};
        const Color cellLinesHoverColor = {255, 215, 30, 255};
        const Color layerNumColor = {224, 225, 221, 255};
        void render(bool drawLayerNums, Color layerColor, int hoveredGUILayer);
        void updateHover(int mouseGridX, int mouseGridY);
        void updateCellLayer(int currentLayer);
    };

    std::vector<std::vector<Cell>> cells;
};
