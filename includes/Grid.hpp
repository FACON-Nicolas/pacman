#ifndef GRID_HPP
#define GRID_HPP

#define GRID_WIDTH 21
#define GRID_HEIGHT 20

#define LINE_VALUE 1000
#define COLUMN_VALUE 1

#include <utility>
#include "../includes/Tile.hpp"
#include <algorithm>               
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

/**
 * @brief PVector2Grid is a Vector used in the pacman grids.
 * 
 * the first value is used to initialize the row, and the second for the columns.
 * 
 */
typedef std::pair<int, int> PVector2Grid;

/**
 * @brief Property used to define Edge Weight.
 * 
 */
typedef boost::property<boost::edge_weight_t, double> PEdgeWeight;

/**
 * @brief define PGraph type, used to get a path between two points in a map.
 * 
 */
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, PEdgeWeight> PGraph;

/**
 * @brief define an iterator of edge for a PGraph
 * 
 */
typedef boost::graph_traits<PGraph>::edge_iterator PEdgeIterator;

/**
 * @brief Grid class, store the datas in matrix (normalGrid, and pacGumGrid). 
 * 
 */
class Grid {

public:

    /**
     * @brief Construct a new Grid object, initializes the grids.
     * 
     */
    Grid();

    /**
     * @brief method used to initialize the grids.
     * 
     */
    void initializeGrids();

    /**
     * @brief getter to get the tile value in a specific row and a specific column.
     * 
     * @param position position in PVector2Grid (row, col)
     */
    int get(PVector2Grid position) const;

    /**
     * @brief setter to set the tile value in a specific row and a specific column.
     * 
     * @param position position in PVector2Grid (row, col)
     * 
     * @param value the new m_value.
     */
    void set(PVector2Grid position, int value);

    /**
     * @brief convert m_value of a specific tile in a reversed array binary
     * 
     * @param position position in PVector2Grid (row, col)
     * 
     * @return int* the array
     */
    int* wallToBin(PVector2Grid position);

    /**
     * @brief check if a specific wall is present in a tile value
     * 
     * @param position position in PVector2Grid (row, col)
     * 
     * @param wall the wall reached.
     * 
     * @return true if the wall is present
     * 
     * @return false if the wall is not present
     */
    bool isWallPresent(PVector2Grid position, Wall wall);
    
private:

    /**
     * @brief initialize main grid
     * 
     */
    void initializeMainGrid();

    /**
     * @brief converts the main grid in a graph.
     * 
     */
    void initializeGraphGrid();

    /**
     * @brief initialize the grid with the pacGum values.
     * 
     */
    void initializePacGumGrid();

    /**
     * @brief main grid.
     * 
     */
    Tile m_grid[GRID_HEIGHT][GRID_WIDTH];

    /**
     * @brief grid used as PGraph to get paths for AIs
     * 
     */
    PGraph m_gridGraph;

};

#endif //GRID_HPP