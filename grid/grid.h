#pragma once
#include "raylib.h"

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
    const Color backgroundColor = {30, 80, 140, 255};
    const Color cellLinesColor = {100, 150, 200, 255};
    int gridWidth;
    int gridHeight;
    int cellSize;
    void render();
    void initWindow();


    Camera2D camera;
};
