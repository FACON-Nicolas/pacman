#ifndef GRID_HPP
#define GRID_HPP

#define GRID_WIDTH 21
#define GRID_HEIGHT 20

#include <utility>
#include "../includes/Tile.hpp"

typedef std::pair<int, int> PVector2;

class Grid {

public:
    Grid();

    void initializeGrid();
    //write a method to transform grid in Graph;
    void get(PVector2 position);
    void set(PVector2 position, int value);
    int* wallToBin(PVector2 position);
    bool isWallPresent(PVector2 position, Wall wall);
    
private:

    int grid[GRID_HEIGHT][GRID_WIDTH];

};

#endif //GRID_HPP