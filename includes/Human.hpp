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
        m_walkTopAnim = new Animation(3, name, "walk_top", true);
        m_walkBottomAnim = new Animation(3, name, "walk_bottom", true);
        m_deathAnim = new Animation(11, name, "death", false, false);
        m_currentAnim = m_walkRightAnim;
        setCurrentAnimation();
        setCurrentDirection(Direction::STOP);
        setNextDirection(Direction::STOP);
        setLastPacGum(PacGum::EMPTY);
        m_startPos = Grid::convertPV2(getGridPosition());
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

    /**
     * @brief check if pacman is collided
     * 
     * @return true if it is collided
     * 
     * @return false if it is not collided
     */
    bool isCollided() const { return m_isCollidingEnemy; }

    /**
     * @brief Set the Collided object
     * 
     * @param collision new collision value
     */
    void setCollided(bool collision) { m_isCollidingEnemy = collision; }

    /**
     * @brief check if the death is over
     * 
     * @return true if the death anim is paused and player is collided 
     * 
     * @return false not true
     */
    bool deathIsOver() { return m_currentAnim == m_deathAnim && m_currentAnim->isPaused(); }

    /**
     * @brief check if pacman is alive
     * 
     * @return true if pacman is alive
     * 
     * @return false if pacman is alive
     */
    bool isAlive();

    int getRemainingLives() { return m_remainingLives; }

    /**
     * @brief Set the Current Animation object
     * 
     * @param animation new anim value
     */
    void setCurrentAnimation(Animation* animation) { m_currentAnim = animation; }

    /**
     * @brief Get the Last Pacgum object
     * 
     * @return PacGum last pacgum value
     */
    PacGum getLastPacgum() const { return m_lastPacGum; }

    /**
     * @brief Set the Last Pac Gum object
     * 
     * @param pacgum new last pacgum value
     */
    void setLastPacGum(PacGum pacgum) { this->m_lastPacGum = pacgum; }

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

    /**
     * @brief walk top anim
     * 
     */
    Animation* m_walkTopAnim;

    /**
     * @brief walk bottom anim.
     * 
     */
    Animation* m_walkBottomAnim;
    
    /**
     * @brief last pacgum eaten, value change each time pacman is fed.
     * 
     */
    PacGum m_lastPacGum;

    /**
     * @brief node start pos
     * 
     */
    int m_startPos;
};

#endif //HUMAN_HPP