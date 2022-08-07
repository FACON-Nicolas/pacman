#ifndef DIRECTION_HPP
#define DIRECTION_HPP


/**
 * @brief Direction enum, used to choice a direction
 * for players and AIs.
 * 
 * Used in a graph implementation to know the AI path between
 * a start and destination point.  
 * 
 * 
 */
enum class Direction : int {

    TOP = 1,
    RIGHT = 2,
    BOTTOM = 4,
    LEFT = 8
};

#endif //DIRECTION_HPP