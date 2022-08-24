#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../includes/Human.hpp"
#include "../includes/Player.hpp"
#include "../includes/Target.hpp"

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
    Enemy(std::string name, float x, float y, float speed, Target targetType) : Player(name, x, y, speed), m_targetType(targetType) {}

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

    /**
     * @brief Get the Path In Directions object.
     * 
     * Choose the path thanks to methods written to get the perfect path ghost by ghost.
     * 
     * @return std::vector<Direction> direction to follow from ghost to destination.
     */
    std::vector<Direction> transformPathInDirections();

    /**
     * @brief get a direction thanks to the start and the end (node A / B)
     * 
     * @param a start
     * 
     * @param b end
     * 
     * @return Direction direction to go from A to B.
     */
    static Direction fromNodesToDirection(int a, int b);

private:

    /**
     * @brief Get the Random Node object
     * 
     * @return int random node
     */
    int getRandomNode();

    /**
     * @brief Get the Path object
     * 
     * @return std::vector<boost::graph_traits<PGraph>::vertex_descriptor> new path.
     */
    std::vector<boost::graph_traits<PGraph>::vertex_descriptor> getPath();

    /**
     * @brief get path from ghost to pacman
     * 
     * @return std::vector<boost::graph_traits<PGraph>::vertex_descriptor> 
     */
    std::vector<boost::graph_traits<PGraph>::vertex_descriptor> getpathToPlayer();

    /**
     * @brief get path from ghost to next player node.
     * 
     * @return std::vector<boost::graph_traits<PGraph>::vertex_descriptor> 
     */
    std::vector<boost::graph_traits<PGraph>::vertex_descriptor> getpathToNextPlayerPosition();

    /**
     * @brief getPath from ghost and random position.
     * 
     * @return std::vector<boost::graph_traits<PGraph>::vertex_descriptor> 
     */
    std::vector<boost::graph_traits<PGraph>::vertex_descriptor> getpathToRandom();

    /**
     * @brief target value, static because all Enemy have the same target.
     * 
     */
    static inline Human* m_target = new Human("pacman", 0, 0, 0);

    /**
     * @brief Target type, might be player, its next position or completely random.
     * 
     */
    Target m_targetType;

};

#endif