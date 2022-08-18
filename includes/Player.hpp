#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../includes/Direction.hpp"
#include "../includes/Animation.hpp"

class Player {

public:

    /**
     * @brief Construct a new Player object
     * 
     * @param name name of character
     * 
     * @param x start horizontal pos
     * 
     * @param y start vertical pos
     */
    Player(std::string name, float x, float y) : m_name(name), m_x(x), m_y(y) {}

    /**
     * @brief Destroy the Player object
     * 
     */
    ~Player();

    /**
     * @brief 
     * 
     * @param player check if this player is colliding another player
     * 
     * @return true if they are overlapping
     * 
     * @return false if they are not oberlapping
     */
    bool isCollidingPlayer(Player player);

    /**
     * @brief check if a player is correctly positionned on a case
     * 
     * @return true if x % CASE_SIZE == 0 and y % CASE_SIZE == 0
     * 
     * @return false if x % CASE_SIZE != 0 or y % CASE_SIZE != 0
     */
    bool isPerfectlyPositionnedOnCase();

    /**
     * @brief Get the Current Animation object
     * 
     * @return Animation animation got.
     */
    virtual Animation getCurrentAnimation();

    /**
     * @brief Set the Current Animation object
     * 
     * @param anim new Anim value
     */
    virtual void setCurrentAnimation();

private:

    /**
     * @brief current horizontal position 
     * 
     */
    float m_x;

    /**
     * @brief current vertical position
     * 
     */
    float m_y;

    /**
     * @brief player name, used to search its sprites
     * 
     */
    std::string m_name;

    /**
     * @brief next direction, used to improve ergonomic for human player and AIs
     * 
     */
    Direction m_nextDirection;

};

#endif //PLAYER_HPP