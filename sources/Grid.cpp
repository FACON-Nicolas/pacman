#include "../includes/Grid.hpp"
using namespace std;

Grid::Grid() {
    initializeGrids();
}

void Grid::initializeGrids() {
    initializeMainGrid();
}

int Grid::get(PVector2Grid position) const {
    int row = position.first, col = position.second;
    if (row < 0 || row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH)
        throw invalid_argument("row or column out of range");
    return m_grid[row][col].get();
}

void Grid::set(PVector2Grid position, int value) {
    int row = position.first, col = position.second;
    if (row < 0 || row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH)
        throw invalid_argument("row or column out of range");
    m_grid[row][col].set(value);
}

int* Grid::wallToBin(PVector2Grid position) {
    int row = position.first, col = position.second;
    if (row < 0 || row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH)
        throw invalid_argument("row or column out of range");
    return m_grid[row][col].wallToBin();
}

bool Grid::isWallPresent(PVector2Grid position, Wall wall) {
    int row = position.first, col = position.second;
    if (row < 0 || row >= GRID_HEIGHT || col < 0 || col >= GRID_WIDTH)
        throw invalid_argument("row or column out of range");
    return m_grid[row][col].isWallPresent(wall);
}

void Grid::initializeMainGrid() {

    // grid with tiles' wall values.
    int grid[GRID_HEIGHT][GRID_WIDTH] = {
        {9, 5, 5, 5, 1, 5, 5, 5, 5, 3, 10, 9, 5, 5, 5, 5, 1, 5, 5, 5, 3},
        {10, 9, 1, 3, 10, 9, 1, 1, 3, 10, 10, 10, 9, 1, 1, 3, 10, 9, 1, 3, 10},
        {10, 12, 4, 6, 10, 12, 4, 4, 6, 10, 14, 10, 12, 4, 4, 6, 10, 12, 4, 6, 10},
        {8, 5, 5, 5, 0, 5, 1, 5, 5, 4, 5, 4, 5, 5, 1, 5, 0, 5, 5, 5, 2},
        {10, 13, 5, 7, 10, 11, 10, 13, 5, 5, 1, 5, 5, 7, 10, 11, 10, 13, 5, 7, 10},
        {12, 5, 5, 5, 2, 10, 12, 5, 5, 3, 10, 9, 5, 5, 6, 10, 8, 5, 5, 5, 6},
        {1, 1, 1, 3, 10, 8, 5, 5, 7, 10, 14, 10, 13, 5, 5, 2, 10, 9, 1, 1, 1},
        {0, 0, 0, 2, 10, 10, 9, 5, 5, 4, 1, 4, 5, 5, 3, 10, 10, 8, 0, 0, 0},
        {4, 4, 4, 6, 10, 14, 10, 9, 1, 1, 0, 1, 1, 3, 10, 14, 10, 12, 4, 4, 4},
        {5, 5, 5, 5, 0, 5, 2, 8, 0, 0, 0, 0, 0, 2, 8, 5, 0, 5, 5, 5, 5},
        {1, 1, 1, 3, 10, 11, 10, 12, 4, 4, 4, 4, 4, 6, 10, 11, 10, 9, 1, 1, 1},
        {0, 0, 0, 2, 10, 10, 8, 5, 5, 5, 5, 5, 5, 5, 2, 10, 10, 8, 0, 0, 0},
        {4, 4, 4, 6, 10, 14, 10, 13, 5, 5, 1, 5, 5, 7, 10, 14, 10, 12, 4, 4, 4},
        {9, 5, 5, 5, 0, 5, 4, 5, 5, 3, 10, 9, 5, 5, 4, 5, 0, 5, 5, 5, 3},
        {10, 13, 5, 3, 10, 13, 5, 5, 7, 10, 14, 10, 13, 5, 5, 7, 10, 9, 5, 7, 10},
        {12, 5, 3, 10, 8, 5, 1, 5, 5, 4, 5, 4, 5, 5, 1, 5, 2, 10, 9, 5, 6},
        {5, 7, 10, 14, 10, 11, 10, 13, 5, 5, 1, 5, 5, 7, 10, 11, 10, 14, 10, 13, 5},
        {9, 5, 4, 5, 6, 10, 12, 5, 5, 3, 10, 9, 5, 5, 6, 10, 12, 5, 4, 5, 3},
        {10, 13, 5, 5, 5, 4, 5, 5, 7, 10, 14, 10, 13, 5, 5, 4, 5, 5, 5, 7, 10},
        {12, 5, 5, 5, 5, 5, 5, 5, 5, 4, 5, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6},
    };

    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++)
            m_grid[i][j] = Tile(grid[i][j]);
    }
}