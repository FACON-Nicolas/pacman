#include"../includes/Player.hpp"

bool Player::isCollidingPlayer(Player player) {
    return abs(player.m_x - m_x) < CASE_SIZE && abs(player.m_y - m_y) < CASE_SIZE;
}

bool Player::isPerfectlyPositionned() {
    return (int) m_x % CASE_SIZE == 0 && (int) m_y % CASE_SIZE == 0;
}

Player::~Player() {
    
}
