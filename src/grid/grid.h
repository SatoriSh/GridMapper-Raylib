#pragma once
#include <vector>
#include <map>
#include "raylib.h"
#include "../camera/UserCamera.h"

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
    int gridWidth;
    int gridHeight;
    int cellSize;
    int mouseGridX;
    int mouseGridY;
    UserCamera userCamera;
    void render();
    void initWindow();
    void initCells();
    void resetCells();

    struct Cell
    {
        Cell(int x, int y, int cellSize, int minLayer, int maxLayer);
        ~Cell();

        const int x;
        const int y;
        const int cellSize;
        const float defaultLineThick = 1.0f;
        const float hoverLineThick = 2.0f;
        int layer = 0;
        int minLayer;
        int maxLayer;
        bool layerBeenChanged = false;
        bool isHovered = false;
        Rectangle rect;
        float lineThick = defaultLineThick;
        const Color cellLinesColor = {65, 90, 119, 150};
        const Color cellLinesHoverColor = {255, 215, 30, 255};
        const Color layerNumColor = {224, 225, 221, 255};
        std::map<int, Color> layerColor;
        void render();
        void updateHover(int mouseGridX, int mouseGridY);
        void updateCellLayer();
    };

    std::vector<std::vector<Cell>> cells;
};
