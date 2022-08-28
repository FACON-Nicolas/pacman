#ifndef TARGET_HPP
#define TARGET_HPP


/**
 * @brief defines the target to trap pacman
 * 
 */
enum class Target {

    /**
     * @brief if target is PLAYER then the ghost follows directly pacman.
     * 
     */
    PLAYER,

    /**
     * @brief if target is NEXT_POS_PLAYER, the ghost follows the next node met by pacman.
     * 
     */
    NEXT_POS_PLAYER,

    /**
     * @brief if target is RANDOM, the ghost follows a random direction.
     * 
     */
    RANDOM,

    /**
     * @brief alternate is a value that switch between PLAYER and THE RIGHT BOTTOM CORNER.
     * 
     */
    ALTERNATE,

    /**
     * @brief if a ghost has "corner to corner" as target value, then he'll move from a corner, to another corner.
     * 
     */
    CORNER_TO_CORNER

};

#endif //TARGET_HPP