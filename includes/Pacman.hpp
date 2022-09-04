#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "SFML/Graphics.hpp"
#include "../includes/Grid.hpp"
#include "../includes/Human.hpp"
#include "../includes/Enemy.hpp"
#include "../includes/Constant.hpp"

#include <cmath>

/**
 * @brief Window class, inherited from sf::RenderWindow  class.
 * 
 * Used to show at user's screen the pacman game.
 * 
 */
class Window : public sf::RenderWindow {

public:

    /**
     * @brief Construct a new Window.
     * 
     * Call the super constructor (sf::RenderWindow(sf::VideoMode, const sf::String&))
     * 
     * @param video videoMode
     * 
     * @param title title of the window
     */
    Window(sf::VideoMode video, const sf::String& title) : sf::RenderWindow(video, title) {
        setFramerateLimit(FRAME_RATE);
        m_pacmanLiveTexture.loadFromFile("images/pacman/walk_right2.png");
        m_pacGumTexture.loadFromFile("images/point.png");
        m_superPacGumTexture.loadFromFile("images/coin.png");
        initGrid();
        initPlayers();
        m_pacmanLiveSprites = new sf::Sprite[m_pacman->getRemainingLives()];
        for (int i = 0; i < m_pacman->getRemainingLives(); i++) {
            m_pacmanLiveSprites[i].setTexture(m_pacmanLiveTexture);
            m_pacmanLiveSprites[i].setPosition(CASE_SIZE * GRID_WIDTH, CASE_SIZE * i);
        }
        initPacGums();
        run();
    }

    /**
     * @brief Destroy the Window object
     * 
     */
    virtual ~Window();

    /**
     * @brief draw the grid on the screen
     * 
     */
    void drawGrid();

    /**
     * @brief method use to update the window.
     * 
     */
    void update();

    /**
     * @brief method used to launch the game.
     * 
     */
    void run();

    /**
     * @brief check the input in keyboard and play actions.
     * 
     */
    void keyboardControls(sf::Keyboard::Key key);

    /**
     * @brief check events (key pressed, mouse used, window closed, etc)
     * 
     */
    void event();

    /**
     * @brief init the players.
     * 
     */
    void initPlayers();

    /**
     * @brief method to update players' sprite to avoid white background on sprite.
     * 
     */
    void updatePlayers();

    /**
     * @brief init a vector of sprites for pacgums
     * 
     */
    void initPacGums();

    /**
     * @brief draw the pacGums' sprites.
     * 
     */
    void drawPacGums();

private:

    /**
     * @brief draw the grid walls on the screen
     * 
     */
    void drawGridWalls();

    /**
     * @brief draw the pacgums used by a grid on the screen
     * 
     */
    void drawGridPacGum();

    /**
     * @brief method that initializes the main grid.
     * 
     */
    void initGrid();

    /**
     * @brief texture of grid image
     * 
     */
    sf::Texture m_gridTexture;

    /**
     * @brief sprite of grid image.
     * 
     */
    sf::Sprite m_gridSprite;

    /**
     * @brief game grid.
     * 
     */
    Grid m_grid;

    /**
     * @brief human player.
     * 
     */
    Human* m_pacman;

    /**
     * @brief blinky ghost
     * 
     */
    Enemy* m_blinky;

    /**
     * @brief pinky ghost
     * 
     */
    Enemy* m_pinky;

    /**
     * @brief clyde ghost
     * 
     */
    Enemy* m_clyde;

    /**
     * @brief vector of sf::Sprites to draw pacgum Sprites
     * 
     */
    std::vector<sf::Sprite> m_pacGumSprites;

    /**
     * @brief texture used to pacgumSprite.
     * 
     */
    sf::Texture m_pacGumTexture;

    /**
     * @brief texture used to superPacgumSprite.
     * 
     */
    sf::Texture m_superPacGumTexture;

    sf::Texture m_pacmanLiveTexture;

    sf::Sprite* m_pacmanLiveSprites;

};

#endif //PACMAN_HPP