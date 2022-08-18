#include "../includes/Pacman.hpp"

Window::~Window() {

}

void Window::run() {
    while (isOpen()) {
        event();
        update();
    }
}

void Window::event() {
    sf::Event m_event;
    while(pollEvent(m_event)) {
        switch (m_event.type)
        {
        case sf::Event::Closed:
            close();
            break;
        case sf::Event::KeyPressed:
            keyboardControls();
            break;
        default:
            break;
        }
    }
}

void Window::update() {
    drawGrid();
}

void Window::drawGrid() {
    drawGridWalls();
    drawGridPacGum();
}

void Window::drawGridWalls() {

} 

void Window::drawGridPacGum() {

}

void Window::drawWall(PVector2Grid position) {
    int tileValue = m_grid.get(position);
    int row(position.first), column(position.second);
    for (int i = 0; i <= 3; i++)
    // if 2 ** i == tile value then it's a simple wall (1, 2, 4, 8)
        if (pow(2, i) == tileValue) {
            textures[row][column].loadFromFile("../images/walls/single_line.png");
            sprites[row][column].setTexture(textures[row][column]);
            sprites[row][column].setRotation(90 * i);
        } 
    // if tileValue % 3 == 0  and <= 12 then its a corner (3, 6, 9, 12)
    if (tileValue % 3 == 0 && tileValue <= 12) {
        textures[row][column].loadFromFile("../images/walls/corner.png");
        sprites[row][column].setTexture(textures[row][column]);
        sprites[row][column].setRotation(90 * ((tileValue % 3)-1));
    }
    // if tileValue % 5 == 0  and <= 10 then its a double line (5, 10)
    if (tileValue % 5 == 0 && tileValue <= 10) {
        textures[row][column].loadFromFile("../images/walls/double_line.png");
        sprites[row][column].setTexture(textures[row][column]);
        sprites[row][column].setRotation(tileValue == 10 ? 90 : 0);
    }

    // else its a semi circle
    else {
        textures[row][column].loadFromFile("../images/walls/semi_circle2.png");
        sprites[row][column].setTexture(textures[row][column]);
        int rotation = tileValue == 11 ? 90 : tileValue == 7 ? 180 : tileValue == 14 ? 270 : 0;
        sprites[row][column].setRotation(rotation);
    } sprites[row][column].setPosition(sf::Vector2f(row * CASE_SIZE, column * CASE_SIZE));
}