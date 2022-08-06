#include "../includes/Tile.hpp"

bool Tile::operator==(Tile const& tile) const {
    return m_value == tile.m_value;
}

bool Tile::operator!=(Tile const& tile) const {
    return !(*this == tile);
}

bool Tile::operator<=(Tile const& tile) const {
    return m_value <= tile.m_value;
}

bool Tile::operator>(Tile const& tile) const {
    return !(*this <= tile);
}

bool Tile::operator>=(Tile const& tile) const {
    return (m_value >= tile.m_value);
}

bool Tile::operator<(Tile const& tile) const {
    return !(*this >= tile);
}

int Tile::getValue() const {
    return m_value;
}

void Tile::setValue(int value) {
    this->m_value = value;
}

int* Tile::wallToBin() {
    int value = m_value;
    int walls[4];
    for (int i = 0; i < 4; i++) {
        walls[i] = value%2;
        value /= 2;
    } return walls;
}

bool Tile::isWallPresent(Wall wall) {
    int* walls = wallToBin();
    int w = static_cast<int>(wall);
    for (int i = 0; i < 4; i++)
        if (walls[i]*pow(2, i) == w)
            return true;
    return false;
}