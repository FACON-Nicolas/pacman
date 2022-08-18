#ifndef TILE_HPP
#define TILE_HPP

#include "Wall.hpp"
#include <stdexcept>
#include <vector>
#include <cmath>

/**
 * @brief 
 * 
 */
class Tile {

public:

    //constructors

    /**
     * @brief Construct a new Tile object
     * 
     * @param value value to define m_value
     */
    Tile(int value) : m_value(value) {
        if (value < 0 || value >= 16)
            throw std::invalid_argument("the value is not on range [0, 16 [");
    }

    /**
     * @brief Construct a new Tile object. 
     * 
     * Initializes the tile value to 0.
     * 
     */
    Tile() : m_value(0) {}


    /**
     * @brief compare two tiles and defines if they're equals.
     * 
     * @param tile tile to compare.
     * 
     * @return true if value == tile value
     * 
     * @return false if value != tile value.
     */
    bool operator==(Tile const& tile) const;

    /**
     * @brief compare two tiles and defines if this is less or equals than tile
     * 
     * @param tile tile to compare.
     * 
     * @return true if this is less or equals than tile.
     * 
     * @return false if this is greater than tile.
     */
    bool operator<=(Tile const& tile) const;

    /**
     * @brief compare two tiles and defines if this is greater or equals than tile
     * 
     * @param tile tile to compare
     * 
     * @return true if this is greater or equals than tile
     * 
     * @return false if tile is greater than this 
     */
    bool operator>=(Tile const& tile) const;

    /**
     * @brief compare two tiles and defines if this is greater is different than tile
     * 
     * @param tile tile to compare
     * 
     * @return true if this != tile
     * 
     * @return false if this == tile
     */
    bool operator!=(Tile const& tile) const;

    /**
     * @brief compare two tiles and defines if this is greater than tile
     * 
     * @param tile tile to compare
     * 
     * @return true if this is greater than tile
     * 
     * @return false if tile is greater or equals than this 
     */
    bool operator>(Tile const& tile) const;
    
    /**
     * @brief compare two tiles and defines if this is less than tile
     * 
     * @param tile tile to compare
     * 
     * @return true if this is less than tile
     * 
     * @return false if tile is less or equals than this 
     */
    bool operator<(Tile const& tile) const;

    /**
     * @brief Get the Value object
     * 
     * @return int return the value stored in m_value.
     */
    int get() const;

    /**
     * @brief Set the Value object
     * 
     * @param value new Tile m_value
     */
    void set(int value);

    /**
     * @brief convert m_value to an array of int equivalent to a reversed binary.
     * 
     * example : m_value = 8 -> 0b1000 -> [0,0,0,1]
     * 
     * @return vector<int> reversed binary.
     */
    std::vector<int> wallToBin();

    /**
     * @brief check if a number 
     * 
     * @param number 
     * 
     * @return true 
     * 
     * @return false 
     */
    bool isWallPresent(Wall wall);

private:
    /**
     * @brief tile value ([0, 16 [)
     * 
     */
    int m_value;
};

#endif //TILE_HPP