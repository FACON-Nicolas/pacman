#ifndef WALL_HPP
#define WALL_HPP


/**
 * @brief Wall class, used to make wall and detect collisions easily.
 * 
 * 
 * example: in the shape just bellow, all of walls are here, there the value is 1+2+4+8, then this wall value is 15
 * 
 * 
 *     1
 *    ___
 *   |   |
 * 8 |   | 2
 *   |___|
 *    
 *     4
 * 
 */
enum class Wall : int {

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
    LEFT = 8
};

#endif //WALL_HPP