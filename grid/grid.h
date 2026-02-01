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
    const Color backgroundColor;
    void render();
};
