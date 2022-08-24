#include "../includes/Enemy.hpp"
using namespace std;

Enemy::~Enemy() {
    delete m_walkBottomAnim;
    delete m_walkLeftAnim;
    delete m_walkTopAnim;
    delete m_walkBottomAnim;
    m_enemyCounter--;
    if (m_enemyCounter == 0) {
        delete m_target;
        delete m_walkRandomlyAnim;
    }
}

int Enemy::getRandomNode() {
    int random = rand() % getGrid()->getNodesValues().size();
    return getGrid()->getNodesValues()[random];
}

vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getpathToPlayer() {
    vector<boost::graph_traits<PGraph>::vertex_descriptor> path;
    path = getGrid()->dijkstraShortestPaths(getLastNode(), m_target->getLastNode());
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

vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getPath() {
    switch (m_targetType) {
        case Target::PLAYER:
            return getpathToPlayer();
        case Target::NEXT_POS_PLAYER:
            return getpathToNextPlayerPosition();
        default:
            return getpathToRandom();
    }
}

Direction Enemy::fromNodesToDirection(int a, int b) {
    if (a == b) return Direction::STOP;
    else if (a > b) return (a / 1000 == b / 1000) ? Direction::LEFT : Direction::TOP;
    else return (a / 1000 == b / 1000) ? Direction::RIGHT : Direction::BOTTOM;
}

vector<Direction> Enemy::transformPathInDirections() {
    vector<boost::graph_traits<PGraph>::vertex_descriptor> path = getPath();
    vector<Direction> directions;
    for (auto it = path.begin(); it != path.end()-1; it++)
        directions.push_back(fromNodesToDirection(*it, *(it+1)));
    return directions;
}