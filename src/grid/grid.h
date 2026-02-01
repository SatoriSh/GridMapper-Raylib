#pragma once
#include <vector>
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
    const Color backgroundColor = {30, 80, 140, 255};
    int gridWidth;
    int gridHeight;
    int cellSize;
    int mouseGridX;
    int mouseGridY;
    UserCamera userCamera;
    void render();
    void initWindow();
    void initCells();

    struct Cell
    {
        Cell(int x, int y, int cellSize, int minLayer, int maxLayer);
        ~Cell();

        const int x;
        const int y;
        const int cellSize;
        const float defaultLineThick = 1.0f;
        const float hoverLineThick = 2.5f;
        int layer = 0;
        int minLayer;
        int maxLayer;
        bool isHovered = false;
        Rectangle rect;
        float lineThick = defaultLineThick;
        const Color cellLinesColor = {100, 150, 200, 255};
        const Color layerNumColor = GREEN;
        void render() const;
        void updateHover(int mouseGridX, int mouseGridY);
        void updateCellLayer();
    };

    std::vector<std::vector<Cell>> cells;
};
