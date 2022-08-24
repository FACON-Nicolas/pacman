#include "../includes/Enemy.hpp"

Enemy::~Enemy() {
    
}

int Enemy::getRandomNode() {
    int random = rand() % getGrid()->getNodesValues().size();
    return getGrid()->getNodesValues()[random];
}

std::vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getpathToPlayer() {
    std::vector<boost::graph_traits<PGraph>::vertex_descriptor> path;
    path = getGrid()->dijkstraShortestPaths(getLastNode(), m_target->getLastNode());
    path.push_back(Grid::convertPV2(m_target->getGridPosition()));
    return path;
}

std::vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getpathToNextPlayerPosition() {
    std::vector<boost::graph_traits<PGraph>::vertex_descriptor> path;
    path = getGrid()->dijkstraShortestPaths(getLastNode(), m_target->getNextNode());
    return path;
}

std::vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getpathToRandom() {
std::vector<boost::graph_traits<PGraph>::vertex_descriptor> path;
    path = getGrid()->dijkstraShortestPaths(getLastNode(), getRandomNode());
}

std::vector<boost::graph_traits<PGraph>::vertex_descriptor> Enemy::getPath() {

}

std::vector<Direction> Enemy::transformPathInDirections() {

}