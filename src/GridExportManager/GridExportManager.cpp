#include <fstream>
#include <iostream>
#include "GridExportManager.h"

GridExportManager::GridExportManager()
{

}

void GridExportManager::exportGrid(std::vector<std::vector<int>> grid)
{
    std::ofstream file("Grid.txt");
    
    if (!file.is_open())
    {
        std::cout << "File creation error\n";
        return;
    }

    file << grid[0].size() << " "; // width
    file << grid.size(); // height

    for (int y = 0; y < grid.size(); y++)
    {
        file << "\n";
        for (int x = 0; x < grid[0].size(); x++)
        {
            file << grid[y][x];
            if (x != grid[0].size() - 1)
                file << " ";
        }
    }

    file.close();
}

GridExportManager::~GridExportManager()
{

}
