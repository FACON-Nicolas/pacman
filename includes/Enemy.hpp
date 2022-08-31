#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../includes/Human.hpp"
#include "../includes/Player.hpp"
#include "../includes/Target.hpp"

#include <string>

/**
 * @brief enemy class inherited from player class, is a class used by pacman ghost to find pacman.
 * 
 */
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
    Enemy(std::string name, float x, float y, float speed, Target targetType) : Player(name, x, y, speed), m_targetType(targetType) {
        m_enemyCounter++;
        m_isEaten = false;
        m_isVunerable = false;
        m_walkLeftAnim = new Animation(2, name, "left");
        m_walkRightAnim = new Animation(2, name, "right");
        m_walkTopAnim = new Animation(2, name, "top");
        m_walkBottomAnim = new Animation(2, name, "bottom");
        m_walkRandomlyAnim = new Animation(2, "AI", "vulnerability");
        m_goToBaseBottomAnim = new Animation(1, "AI", "eaten_bottom");
        m_goToBaseRightAnim = new Animation(1, "AI", "eaten_right");
        m_goToBaseTopAnim = new Animation(1, "AI", "eaten_top");
        m_goToBaseLeftAnim = new Animation(1, "AI", "eaten_left");
        m_currentAnimation = m_walkRightAnim;
        m_startPos = Grid::convertPV2(getGridPosition());
        std::cout << getName() << ": " << m_startPos << std::endl;
    }

    /**
     * @brief Destroy the Enemy object
     * 
     */
    virtual ~Enemy();

    sf::Texture* getTexture() const { return m_currentAnimation->getTexture(); }

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
        if (m_target != nullptr) delete m_target;
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

    /**
     * @brief update method, called at each frame.
     * 
     */
    void update();

    /**
     * @brief Set the Direction object
     * 
     */
    void setDirection();

    /**
     * @brief Set the Animation object
     * 
     */
    void setAnimation();

    /**
     * @brief reverse enemy direction.
     * 
     * RIGHT    =>   LEFT
     * TOP      =>   BOTTOM
     * LEFT     =>   RIGHT
     * BOTTOM   =>   TOP
     * 
     */
    void reverseDirection();

    /**
     * @brief change vulnerabilty of enemy
     * 
     */
    void changeVulnerability();

    /**
     * @brief Set the Vulnerability object
     * 
     */
    void setVulnerability();

    /**
     * @brief method called if pacman and this ghost are overlapping.
     * 
     */
    void collideTarget();

    ///**
    // * @brief check if the target is near of the ghost
    // * 
    // * @return true if the target is near of the ghost
    // * 
    // * @return false if the target is not near of the ghost
    // */
    //bool isNearTarget();

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
     * @brief getPath from ghost to rigth bottom corner position.
     * 
     * @return std::vector<boost::graph_traits<PGraph>::vertex_descriptor> 
     */
    std::vector<boost::graph_traits<PGraph>::vertex_descriptor> getpathToRightBottomCorner();

    /**
     * @brief get path from position to base
     * 
     * @return std::vector<boost::graph_traits<PGraph>::vertex_descriptor> 
     */
    std::vector<boost::graph_traits<PGraph>::vertex_descriptor> getpathToBase();

    /**
     * @brief target value, static because all Enemy have the same target.
     * 
     */
    static inline Human* m_target = nullptr;

    /**
     * @brief Target type, might be player, its next position or completely random.
     * 
     */
    Target m_targetType;

    /**
     * @brief ptr to current anim.
     * 
     */
    Animation* m_currentAnimation;

    /**
     * @brief ptr to walk left 
     * 
     */
    Animation* m_walkLeftAnim;

    /**
     * @brief ptr to walk right
     * 
     */
    Animation* m_walkRightAnim;

    /**
     * @brief ptr to walk top
     * 
     */
    Animation* m_walkTopAnim;

    /**
     * @brief ptr to walk bottom
     * 
     */
    Animation* m_walkBottomAnim;

    /**
     * @brief ptr to walk randomly
     * 
     */
    Animation* m_walkRandomlyAnim;

    /**
     * @brief go to base left anim
     * 
     */
    Animation* m_goToBaseLeftAnim;

    /**
     * @brief go to base right anim
     * 
     */
    Animation* m_goToBaseRightAnim;

    /**
     * @brief go to base top anim
     * 
     */
    Animation* m_goToBaseTopAnim;

    /**
     * @brief go to base bottom anim
     * 
     */
    Animation* m_goToBaseBottomAnim;

    /**
     * @brief ghost counter, increments in constructor and decrements in destructor.
     * 
     */
    static inline int m_enemyCounter = 0;

    /**
     * @brief path to go from A to B
     * 
     */
    std::vector<Direction> m_path;

    /**
     * @brief time start
     * 
     */
    std::chrono::system_clock::time_point m_timeStart;

    /**
     * @brief defines if pacman could eat the enemy
     * 
     */
    bool m_isVunerable;

    /**
     * @brief defines if the ghost is eaten by pacman.
     * 
     */
    bool m_isEaten;

    /**
     * @brief start pos in grid.
     * 
     */
    int m_startPos;

};

#endif