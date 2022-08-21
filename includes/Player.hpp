#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../includes/Constant.hpp"

#include "SFML/Graphics.hpp"
#include "../includes/Grid.hpp"
#include "../includes/Wall.hpp"
#include "../includes/Direction.hpp"
#include "../includes/Animation.hpp"

#include <stdexcept>

/**
 * @brief Player class, used to create players (human, AI)
 * 
 */
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
    Player(std::string name, float x, float y, float speed) {
        m_name = name;
        m_x = x;
        m_y = y;
        m_speed = speed;
    }

    /**
     * @brief Destroy the Player object
     * 
     */
    virtual ~Player();

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
    bool isPerfectlyPositionned();

    /**
     * @brief Get the Sprite object
     * 
     * @return sf::Sprite currentSprite
     */
    sf::Sprite* getSprite() const { return m_sprite; }

    void setSprite(sf::Sprite* sprite) { m_sprite = sprite; }

    bool nextDirectionIsValid(Direction direction);

    bool nextDirectionIsOnSameAxis(Direction direction);

    /**
     * @brief manage the player movements.
     * 
     */
    void move();

    /**
     * @brief getter for m_x
     * 
     * @return float m_x value
     */
    float getX() const { return m_x; }

    /**
     * @brief setter for m_x
     * 
     * @param x new m_x value
     */
    void setX(float x) { m_x = ((int) x % (CASE_SIZE * GRID_WIDTH)); }

    /**
     * @brief getter for m_y
     * 
     * @return float m_y value
     */
    float getY() const { return m_y; }

    /**
     * @brief setter for m_x
     * 
     * @param y new m_y value
     */
    void setY(float y) { m_y = y; }

    /**
     * @brief Get the Horizontal Movement object
     * 
     * @return int hmove value
     */
    int getHorizontalMovement() const { return m_horizontalMovement; }

    /**
     * @brief Set the Horizontal Movement object
     * 
     * @param horizontalMovement new hmove value
     */
    void setHorizontalMovement(float horizontalMovement) { m_horizontalMovement = horizontalMovement; }

    /**
     * @brief Get the Vertical Movement object
     * 
     * @return int vmove value
     */
    int getVerticalMovement() const { return m_verticalMovement; }

    /**
     * @brief Set the Vertical Movement object
     * 
     * @param verticalMovement new vmove value
     */
    void setVerticalMovement(float verticalMovement) { m_verticalMovement = verticalMovement; }

    /**
     * @brief Get the Current Direction object
     * 
     * @return Direction current direction
     */
    Direction getCurrentDirection() const { return m_direction; }

    /**
     * @brief Get the Next Direction object
     * 
     * @return Direction next direction
     */
    Direction getNextDirection() const { return m_nextDirection; }

    /**
     * @brief Set the Current Direction object
     * 
     * @param direction new direction value
     */
    void setCurrentDirection(Direction direction);

    /**
     * @brief Set the Next Direction object
     * 
     * @param direction 
     */
    void setNextDirection(Direction direction) { this->m_nextDirection = direction; }

    /**
     * @brief Set the Movement object
     * 
     * @param horizontal horizontal value
     * 
     * @param vertical vertical Value
     */
    void setMovement(int horizontal, int vertical);

    /**
     * @brief Get the Speed object
     * 
     * @return float player's speed
     */
    float getSpeed() const { return m_speed; }

    /**
     * @brief Set the Speed object
     * 
     * @param speed new player's speed
     */
    void setSpeed(float speed) { this->m_speed = speed; }

    /**
     * @brief Get the Path object
     * 
     * @return std::string path to get sprites.
     */
    std::string getPath() const { return "images/" + m_name + "/"; }

    /**
     * @brief check the current case walls and the direction and determines if the player cans move
     * 
     * @return true if the player cans move
     * 
     * @return false if the player cans not move
     */
    bool canMove();

    /**
     * @brief Get the Grid Position object
     * 
     * @return PVector2Grid current grid position
     */
    PVector2Grid getGridPosition() const { return PVector2Grid((int) m_y / CASE_SIZE, (int) m_x / CASE_SIZE); }

    /**
     * @brief Get the Tile Value object
     * 
     * @return int current tile value
     */
    int getTileValue() const { return m_currentPositionTileValue; }

    /**
     * @brief Set the Tile Value object
     * 
     * @param tileValue new tile value
     */
    void setTileValue(int tileValue) { m_currentPositionTileValue = tileValue; }

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
     * @brief horizontal movement, might be -1, 0, 1
     * 
     */
    int m_horizontalMovement;

    /**
     * @brief vertical movement, might be -1, 0, 1
     * 
     */
    int m_verticalMovement;

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

    /**
     * @brief current direction, might be top, down, left, right or stop.
     * 
     */
    Direction m_direction;

    /**
     * @brief player's speed
     * 
     */
    float m_speed;

    /**
     * @brief current sprite player.
     * 
     */
    sf::Sprite* m_sprite;

    /**
     * @brief tile value at this position.
     * 
     */
    int m_currentPositionTileValue;

};

#endif //PLAYER_HPP