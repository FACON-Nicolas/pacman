#include "../includes/Pacman.hpp"
using namespace std;

Window::~Window() {
    cout << "Window deleted successfully" << endl;
    delete m_pacman;
    delete m_blinky;
}

void Window::run() {
    while (isOpen()) {
        event();
        m_pacman->update();
        m_blinky->update();
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
    drawPacGums();
    draw(*m_pacman->getSprite());
    draw(*m_blinky->getSprite());
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
    Player::setGrid(&m_grid);
    m_pacman = new Human("pacman", 495, 855, NORMAL_SPEED);
    m_blinky = new Enemy("blinky", 0, 0, NORMAL_SPEED, Target::PLAYER);
    Enemy::setTarget(m_pacman);
}

void Window::updatePlayers() {
    m_pacman->getSprite()->setTexture(*m_pacman->getTexture());
    m_pacman->getSprite()->setPosition(m_pacman->getX(), m_pacman->getY());
    m_blinky->getSprite()->setTexture(*m_blinky->getTexture());
    m_blinky->getSprite()->setPosition(m_blinky->getX(), m_blinky->getY());

}

void Window::initPacGums() {
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++) {
        int row (i / GRID_WIDTH), column(i % GRID_WIDTH);
        sf::Sprite sprite;
        if (m_grid.getPacGum(PVector2Grid(row, column)) == PacGum::DOT) sprite.setTexture(m_pacGumTexture);
        else sprite.setTexture(m_superPacGumTexture);
        float x = CASE_SIZE * column + ((CASE_SIZE/2)); (sprite.getTexture()->getSize().x / 2);
        float y = CASE_SIZE * row + ((CASE_SIZE/2)); + (sprite.getTexture()->getSize().y / 2);

        if (m_grid.getPacGum(PVector2Grid(row, column)) == PacGum::ENERGIZER) {
            x -= (sprite.getTexture()->getSize().x / 2);
            y -= (sprite.getTexture()->getSize().y / 2);
        }
        sprite.setPosition(x, y);
        m_pacGumSprites.push_back(sprite);
    }
}

void Window::drawPacGums() {
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++) {
        int row(i / GRID_WIDTH), column(i % GRID_WIDTH);
        if (m_grid.getPacGum(PVector2Grid(row, column)) != PacGum::EMPTY) draw(m_pacGumSprites[i]);
    }
}



int main() {
    cout << "PANCAKES GOOOOOOO" << endl;
    Window w(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pacman");
}