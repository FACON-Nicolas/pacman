#include "../includes/Tile.hpp"
using namespace std;

bool Tile::operator==(Tile const& tile) const {
    return get() == tile.get();
}

bool Tile::operator!=(Tile const& tile) const {
    return !(*this == tile);
}

bool Tile::operator<=(Tile const& tile) const {
    return get() <= tile.get();
}

bool Tile::operator>(Tile const& tile) const {
    return !(*this <= tile);
}

bool Tile::operator>=(Tile const& tile) const {
    return (get() >= tile.get());
}

bool Tile::operator<(Tile const& tile) const {
    return !(*this >= tile);
}

int Tile::get() const {
    return m_value;
}

void Tile::set(int value) {
    this->m_value = value;
}

vector<int> Tile::wallToBin() {
    int value = get();
    vector<int> walls;
    for (int i = 0; i < 4; i++) {
        walls.push_back(value%2);
        value /= 2;
    } return walls;
}

bool Tile::isWallPresent(Wall wall) {
    vector<int> walls = wallToBin();
    int w = static_cast<int>(wall);
    for (int i = 0; i < 4; i++)
        if (walls[i]*pow(2, i) == w)
            return true;
    return false;
}