#include"../includes/Player.hpp"
using namespace std;

bool Player::isCollidingPlayer(Player player) {
    return (abs(player.m_x - m_x) < CASE_SIZE && player.m_y == m_y)
        || (abs(player.m_y - m_y) < CASE_SIZE && player.m_x == m_x);
    //return abs(player.m_x - m_x) < CASE_SIZE && abs(player.m_y - m_y) < CASE_SIZE;
}

Player::~Player() {
    m_sprite = nullptr;
}

bool Player::isPerfectlyPositionned() {
    return (int) m_x % CASE_SIZE == 0 && (int) m_y % CASE_SIZE == 0;
}

void Player::setMovement(int horizontal, int vertical) {
    if (vertical != 0 && horizontal != 0) throw std::invalid_argument("hmove et vmove are not valid");
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

void Player::move() {
    if(isPerfectlyPositionned()) {
        if (!canMove() || nextDirectionIsValid(getNextDirection())) {
            setCurrentDirection(getNextDirection());
            setNextDirection(Direction::STOP);
        } if (!canMove()) setCurrentDirection(getNextDirection());
    }
    setX(m_x + (m_speed * m_horizontalMovement));
    setY(m_y + (m_speed * m_verticalMovement));
    m_x = (int) m_x < 0 ? (GRID_WIDTH-1)*CASE_SIZE : m_x;
}

bool Player::canMove() {
    return (m_direction == Direction::LEFT && !Tile::isWallPresent(getTileValue(), Wall::LEFT))
        || (m_direction == Direction::RIGHT && !Tile::isWallPresent(getTileValue(), Wall::RIGHT))
        || (m_direction == Direction::BOTTOM && !Tile::isWallPresent(getTileValue(), Wall::BOTTOM))
        || (m_direction == Direction::TOP && !Tile::isWallPresent(getTileValue(), Wall::TOP))
        || (m_direction == Direction::STOP);
}

bool Player::nextDirectionIsValid(Direction direction) {
    return (direction == Direction::LEFT && !Tile::isWallPresent(getTileValue(), Wall::LEFT)
        || (direction == Direction::BOTTOM && !Tile::isWallPresent(getTileValue(), Wall::BOTTOM))
        || (direction == Direction::TOP && !Tile::isWallPresent(getTileValue(), Wall::TOP))
        || (direction == Direction::RIGHT && !Tile::isWallPresent(getTileValue(), Wall::RIGHT)));
}

bool Player::nextDirectionIsOnSameAxis(Direction direction) {
    return (m_direction == Direction::RIGHT && direction == Direction::LEFT)
        || (m_direction == Direction::LEFT && direction == Direction::RIGHT)
        || (m_direction == Direction::TOP && direction == Direction::BOTTOM)
        || (m_direction == Direction::BOTTOM && direction == Direction::TOP);
}

int Player::getNextNode() {
    int currentPos = Grid::convertPV2(getGridPosition());
    while (!getGrid()->isNode(currentPos)) {
        switch(getCurrentDirection()) {
        case Direction::RIGHT:
            currentPos++;
            if (currentPos % 1000 >= GRID_WIDTH) currentPos -= currentPos % 1000;
            break;
        case Direction::LEFT:
            currentPos--;
            if (currentPos / 1000 != (currentPos+1) / 1000) currentPos += GRID_WIDTH;
            break;
        case Direction::BOTTOM:
            currentPos += ROW_VALUE;
            break;
        case Direction::TOP:
            currentPos -= COLUMN_VALUE;
            break;
        }
    } return currentPos;
}