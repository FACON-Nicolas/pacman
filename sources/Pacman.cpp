#include "../includes/Pacman.hpp"
using namespace std;

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
    clear();
    drawGrid();
    display();
}

void Window::drawGrid() {
    draw(m_gridSprite);
}

void Window::initGrid() {
    m_gridTexture.loadFromFile("images/walls/platform.png");
    m_gridSprite.setTexture(m_gridTexture);
}

void Window::keyboardControls() {

}

int main() {
    Window w(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pacman");
}