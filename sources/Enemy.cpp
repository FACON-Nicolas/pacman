#include "../includes/Enemy.hpp"
using namespace std;

Enemy::~Enemy() {
    m_currentAnimation = nullptr;
    delete m_walkBottomAnim;
    delete m_walkLeftAnim;
    delete m_walkTopAnim;
    delete m_walkRightAnim;
    delete m_goToBaseBottomAnim;
    delete m_goToBaseRightAnim;
    delete m_goToBaseTopAnim;
    delete m_goToBaseLeftAnim;
    m_enemyCounter--;
    if (m_enemyCounter == 0) {
        m_target = nullptr;
        delete m_walkRandomlyAnim;
    }
}

int Enemy::getRandomNode() {
    return getGrid()->getRandomNode();
}

vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getpathToPlayer() {
    vector<boost::graph_traits<PGraph>::vertex_descriptor> path;
    int dest = (m_target->getLastNode() == getLastNode()) ? m_target->getNextNode() : m_target->getLastNode();
    path = getGrid()->dijkstraShortestPaths(getLastNode(), dest);
    path.push_back(Grid::convertPV2(m_target->getGridPosition()));
    return path;
}

vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getpathToNextPlayerPosition() {
    vector<boost::graph_traits<PGraph>::vertex_descriptor> path;
    path = getGrid()->dijkstraShortestPaths(getLastNode(), m_target->getNextNode());
    return path;
}

vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getpathToRandom() {
    vector<boost::graph_traits<PGraph>::vertex_descriptor> path;
    path = getGrid()->dijkstraShortestPaths(getLastNode(), getRandomNode());
    return path;
}

vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getpathToBase() {
    vector<boost::graph_traits<PGraph>::vertex_descriptor> path;
    path = getGrid()->dijkstraShortestPaths(getLastNode(), m_startPos);
    return path;
}

vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getPath() {
    if (m_isEaten) return getpathToBase();
    if (!m_isVunerable) {
        switch (m_targetType) {
            case Target::PLAYER:
                return getpathToPlayer();
            case Target::NEXT_POS_PLAYER:
                return getpathToNextPlayerPosition();
            case Target::ALTERNATE:
                return (rand() % 2 == 0) ? getpathToPlayer() : getpathToRightBottomCorner();
            default:
                return getpathToRandom();
        }
    } return getpathToRandom();
}

void Enemy::collideTarget() {
    if (isCollidingPlayer(*m_target)) {
        if (!m_isEaten && m_isVunerable) {
             m_isEaten = true;
             int lastNode = getLastNode();
             setX((lastNode % 1000) * CASE_SIZE);
             setY((lastNode / 1000) * CASE_SIZE);
             setSpeed(GO_TO_BASE_SPEED);
             m_path = transformPathInDirections();
        } else if (!m_isEaten && !m_isVunerable) {
            m_target->setCollided(true);
            m_target->setCurrentAnimation();
        }
    }
}

Direction Enemy::fromNodesToDirection(int a, int b) {
    if (a < b) {
        if (a / 1000 != b / 1000) return Direction::BOTTOM;
        else return Direction::RIGHT;
    } else if (a > b) {
        if (a / 1000 != b / 1000) return Direction::TOP;
        else return Direction::LEFT;
    } return Direction::STOP;
}

vector<Direction> Enemy::transformPathInDirections() {
    vector<boost::graph_traits<PGraph>::vertex_descriptor> path = getPath();
    vector<Direction> directions;
    //directions.push_back(Direction::STOP);
    for (auto it = path.rbegin(); it != path.rend()-1; it++)
        directions.push_back(fromNodesToDirection(*it, *(it+1)));
    directions.push_back(Direction::STOP);
    if (getName() != "pinky" && !m_isEaten) directions.erase(directions.begin());
    return directions;
}

void Enemy::setDirection() {
    if (m_path.empty()) setNextDirection(Direction::STOP);
    else {
        setNextDirection(*m_path.begin());
        m_path.erase(m_path.begin());
    } setAnimation();
}

void Enemy::changeVulnerability() {
    auto time = chrono::duration_cast<chrono::seconds>(chrono::system_clock::now()-m_timeStart).count();
    if (!m_isVunerable) {
        m_isVunerable = true;
        m_currentAnimation = m_walkRandomlyAnim;
        reverseDirection();
        setSpeed(VULNERABILITY_SPEED);
        m_timeStart = chrono::system_clock::now();
    } else if (time >= 15 || (Grid::convertPV2(getGridPosition()) == m_startPos && m_isEaten)) {
        m_isVunerable = false;
        setAnimation();
        setX(getX() - ((int) getX() % NORMAL_SPEED));
        setY(getY() - ((int) getY() % NORMAL_SPEED));
        setSpeed(NORMAL_SPEED);
        m_isEaten = false;
    }
}

void Enemy::setAnimation() {
    if (m_target->getLastPacgum() == PacGum::ENERGIZER) changeVulnerability();
    else if (m_isEaten) {
        switch (getCurrentDirection())
        {
        case Direction::LEFT:
            m_currentAnimation = m_goToBaseLeftAnim;
            break;
        case Direction::TOP:
            m_currentAnimation = m_goToBaseTopAnim;
            break;
        case Direction::BOTTOM:
            m_currentAnimation = m_goToBaseBottomAnim;
            break;
        case Direction::RIGHT:
            m_currentAnimation = m_goToBaseRightAnim;
            break;
        default:
            m_currentAnimation = m_goToBaseRightAnim;
            break;
        }
    } else if (!m_isVunerable) {
        if  (getCurrentDirection() == Direction::LEFT) m_currentAnimation = m_walkLeftAnim;
        else if (getCurrentDirection() == Direction::RIGHT) m_currentAnimation = m_walkRightAnim;
        else if (getCurrentDirection() == Direction::TOP) m_currentAnimation = m_walkTopAnim;
        else if (getCurrentDirection() == Direction::BOTTOM) m_currentAnimation = m_walkBottomAnim;
    } setSprite(m_currentAnimation->getSprite());
}

void Enemy::reverseDirection() {
    if (getCurrentDirection() == Direction::LEFT) setCurrentDirection(Direction::RIGHT);
    else if (getCurrentDirection() == Direction::RIGHT) setCurrentDirection(Direction::LEFT);
    else if (getCurrentDirection() == Direction::TOP) setCurrentDirection(Direction::BOTTOM);
    else if (getCurrentDirection() == Direction::BOTTOM) setCurrentDirection(Direction::TOP);
    else setCurrentDirection(Direction::STOP);
}

/*
bool Enemy::isNearTarget() {
    return (m_target->getNextNode() == getLastNode());
}*/

std::vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getpathToRightBottomCorner() {
    PVector2Grid corner(GRID_HEIGHT-1, GRID_WIDTH-1);
    vector<boost::graph_traits<PGraph>::vertex_descriptor> path;
    path = getGrid()->dijkstraShortestPaths(getLastNode(), Grid::convertPV2(corner));
    return path;
}

void Enemy::update() {
    if (isPerfectlyPositionned()) {
        int pos = getGrid()->convertPV2(getGridPosition());
        if (getGrid()->isNode(pos)) {
            setLastNode(pos);
            if (m_target != nullptr)
                m_path = transformPathInDirections();
            setDirection();
        }
    }
    setTileValue(getGrid()->get(getGridPosition()));
    if (!m_target->isCollided()) {
        m_currentAnimation->update();
        if (m_isVunerable) changeVulnerability();
        collideTarget();
        setAnimation();
        move();
    }

    if (m_target->deathIsOver() && m_target->isCollided()) {
        PVector2Grid startPos = Grid::convertNode(m_startPos);
        setX(startPos.second * CASE_SIZE);
        setY(startPos.first * CASE_SIZE);
    }
}