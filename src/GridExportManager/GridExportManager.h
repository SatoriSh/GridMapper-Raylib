#pragma once
#include <vector>
#include "raylib.h"

class GridExportManager
{
  public:
    GridExportManager();
    ~GridExportManager();

    static void exportGrid(std::vector<std::vector<int>> grid);
};
