#include"../includes/Player.hpp"
using namespace std;

bool Player::isCollidingPlayer(Player player) {
    return abs(player.m_x - m_x) < CASE_SIZE && abs(player.m_y - m_y) < CASE_SIZE;
}

bool Player::isPerfectlyPositionned() {
    return (int) m_x % CASE_SIZE == 0 && (int) m_y % CASE_SIZE == 0;
}

Player::~Player() {
    
}

void Player::setMovement(int horizontal, int vertical) {
    if (vertical != 0 && horizontal != 0) throw std::invalid_argument("hmove et vmove might are not valid");
    setHorizontalMovement(horizontal);
    setVerticalMovement(vertical);
}

void Player::setCurrentDirection(Direction direction) {
    this->m_direction = direction;
    if (direction == Direction::STOP) setMovement(0, 0);
    else if (direction == Direction::TOP) setMovement(0, -1);
    else if (direction == Direction::BOTTOM) setMovement(0, 1);
    else if (direction == Direction::LEFT) setMovement(-1, 0);
    else setMovement(1, 0);
}
