#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../includes/Player.hpp"
#include "../includes/Human.hpp"

#include <string>

class Enemy : public Player {

public:

    /**
     * @brief Construct a new Enemy object
     * 
     * @param name player's name
     * 
     * @param x player's x pos
     * 
     * @param y player's y pos
     * 
     * @param speed player's speed
     * 
     */
    Enemy(std::string name, float x, float y, float speed) : Player(name, x, y, speed) {}

    /**
     * @brief Destroy the Enemy object
     * 
     */
    virtual ~Enemy();

    /**
     * @brief Get the Target object
     * 
     * @return Human* target searched
     */
    static Human* getTarget() { return m_target; }

    /**
     * @brief Set the Target object
     * 
     * @param target new target Value
     */
    static void setTarget(Human* target) {
        delete m_target;
        m_target = target;
    }

private:

    /**
     * @brief target value, static because all Enemy have the same target.
     * 
     */
    static inline Human* m_target = new Human("pacman", 0, 0, 0);

};

#endif