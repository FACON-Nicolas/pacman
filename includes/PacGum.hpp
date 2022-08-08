#ifndef PACGUM_HPP
#define PACGUM_HPP

/**
 * @brief enum defines the differents types of pacman.
 * 
 *  - 0 is considered as empty 
 *  - 1 as dot (normal pac gum)
 *  - 2 as energizer (super pac gum)
 * 
 */
enum class PacGum : int {

    /**
     * @brief empty pac gum
     * 
     */
    EMPTY = 0,

    /**
     * @brief normal pac gum
     * 
     */
    DOT = 1,

    /**
     * @brief super pac gum
     * 
     */
    ENERGIZER = 2

};

#endif //PACGUM_HPP