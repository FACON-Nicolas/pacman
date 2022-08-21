#include "../includes/Pacman.hpp"
using namespace std;

Window::~Window() {
    cout << "Window deleted successfully" << endl;
    delete m_pacman;
}

void Window::run() {
    while (isOpen()) {
        event();
        m_pacman->update();
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
            keyboardControls(m_event.key.code);
            break;
        default:
            break;
        }
    }
}

void Window::update() {
    clear();
    drawGrid();
    updatePlayers();
    draw(*m_pacman->getSprite());
    display();
}

void Window::drawGrid() {
    draw(m_gridSprite);
}

void Window::initGrid() {
    m_gridTexture.loadFromFile("images/walls/platform.png");
    m_gridSprite.setTexture(m_gridTexture);
}

void Window::keyboardControls(sf::Keyboard::Key key) {
    switch (key) {
    case sf::Keyboard::Right:
        if (!m_pacman->isCollided()) 
            if ((m_pacman->nextDirectionIsOnSameAxis(Direction::RIGHT) || m_pacman->isPerfectlyPositionned()) && m_pacman->nextDirectionIsValid(Direction::RIGHT)) 
                m_pacman->setCurrentDirection(Direction::RIGHT);
            else m_pacman->setNextDirection(Direction::RIGHT);
        break;
    case sf::Keyboard::Left:
        if (!m_pacman->isCollided()) 
            if ((m_pacman->nextDirectionIsOnSameAxis(Direction::LEFT) || m_pacman->isPerfectlyPositionned()) && m_pacman->nextDirectionIsValid(Direction::LEFT)) 
                m_pacman->setCurrentDirection(Direction::LEFT);
            else m_pacman->setNextDirection(Direction::LEFT);
        break;
    case sf::Keyboard::Down:
        if (!m_pacman->isCollided()) 
            if ((m_pacman->nextDirectionIsOnSameAxis(Direction::BOTTOM) || m_pacman->isPerfectlyPositionned()) && m_pacman->nextDirectionIsValid(Direction::BOTTOM)) 
                m_pacman->setCurrentDirection(Direction::BOTTOM);
            else m_pacman->setNextDirection(Direction::BOTTOM);
        break;
    case sf::Keyboard::Up:
        if (!m_pacman->isCollided()) 
            if ((m_pacman->nextDirectionIsOnSameAxis(Direction::TOP) || m_pacman->isPerfectlyPositionned()) && m_pacman->nextDirectionIsValid(Direction::TOP)) 
                m_pacman->setCurrentDirection(Direction::TOP);
            else m_pacman->setNextDirection(Direction::TOP);
        break;
    default:
        break;
    }
}

void Window::initPlayers() {
    m_pacman = new Human("pacman", 450, 855, NORMAL_SPEED);
}

void Window::updatePlayers() {
    m_pacman->getSprite()->setTexture(*m_pacman->getTexture());
    m_pacman->getSprite()->setPosition(m_pacman->getX(), m_pacman->getY());
    m_pacman->setTileValue(m_grid.get(PVector2Grid(m_pacman->getGridPosition())));
}

int main() {
    Window w(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pacman");
}