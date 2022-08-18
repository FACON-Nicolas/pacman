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

    /**
     * @brief top value
     * 
     */
    TOP,

    /**
     * @brief right value
     * 
     */
    RIGHT,

    /**
     * @brief bottom value
     * 
     */
    BOTTOM,

    /**
     * @brief left value
     * 
     */
    LEFT, 

    /**
     * @brief stop value
     * 
     */
    STOP
    
};

#endif //DIRECTION_HPP