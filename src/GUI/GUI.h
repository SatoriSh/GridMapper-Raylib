#pragma once
#include <map>
#include <functional>
#include "raylib.h"

class GUI
{
  public:
    GUI();
    ~GUI();

    std::function<void(int layer)> onHoverGUI;
    std::function<void(int layer)> onClickGUI;
    std::function<void()> onMouseLeaveGUI;

    void drawLayersHint(std::map<int, Color> layerColor, int currentLayer, int maxLayer);
    void setCellSize(int cellSize);
  private:
    Rectangle cellRect = {0,0,0,0};
    int cellSize = 0;
    const int offsetX = 50;
    int offsetY = 0;
    const float lineThick = 3.5f;
    const Color cellLinesCurrentLayerColor = {255, 215, 30, 255};

    void inputHandler(int layer) const;
};
