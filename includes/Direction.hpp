#ifndef DIRECTION_HPP
#define DIRECTION_HPP

/**
 * @brief Direction enum, used to choice a direction
 * for players and AIs.
 * 
 * Used in a graph implementation to know the AI path from
 * a start to destination point.  
 * 
 */
enum class Direction : int {

    /**
     * @brief top value
     * 
     */
    TOP = 1,

    /**
     * @brief right value
     * 
     */
    RIGHT = 2,

    /**
     * @brief bottom value
     * 
     */
    BOTTOM = 4,

    /**
     * @brief left value
     * 
     */
    LEFT = 8, 

    /**
     * @brief stop value
     * 
     */
    STOP = 0
    
};

#endif //DIRECTION_HPP