#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <string>

#include "../includes/Player.hpp"

/**
 * @brief Human class, inherited from Player Class, is a Human Player.
 * 
 */
class Human : public Player {

public:

    /**
     * @brief Construct a new Human object
     * 
     * @param name player name
     * 
     * @param x start x pos
     * 
     * @param y start y pos
     * 
     * @param speed speed player.
     */
    Human(std::string name, float x, float y, float speed) : Player(name, x, y, speed) {
        m_remainingLives = 3;
        m_isCollidingEnemy = false;
        m_walkLeftAnim = new Animation(3, name, "walk_left", true);
        m_walkRightAnim = new Animation(3, name, "walk_right", true);
        m_deathAnim = new Animation(11, name, "death");
        m_currentAnim = m_walkRightAnim;
        setCurrentAnimation();
        setCurrentDirection(Direction::STOP);
        setNextDirection(Direction::STOP);
    }

    sf::Texture* getTexture() const { return m_currentAnim->getTexture(); }

    /**
     * @brief Destroy the Human object
     * 
     */
    virtual ~Human();

    /**
     * @brief Set the Current Animation object
     * 
     */
    void setCurrentAnimation();

    /**
     * @brief method called at each frame.
     * 
     */
    void update();

    bool isCollided() const { return m_isCollidingEnemy; }

    bool isAlive();

    void setCurrentAnimation(Animation* animation) { m_currentAnim = animation; }

private:

    /**
     * @brief value that stores the remaining lives
     * 
     */
    int m_remainingLives;

    /**
     * @brief use to know if an enemy is overlapping the player.
     * 
     */
    bool m_isCollidingEnemy;

    /**
     * @brief current animation played
     * 
     */
    Animation* m_currentAnim;

    /**
     * @brief walk animation
     * 
     */
    Animation* m_walkRightAnim;

    /**
     * @brief death animation.
     * 
     */
    Animation* m_deathAnim;

    /**
     * @brief walk left anim
     * 
     */
    Animation* m_walkLeftAnim;
    

};

#endif //HUMAN_HPP