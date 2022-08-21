#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "SFML/Graphics.hpp"
#include "../includes/Grid.hpp"
#include "../includes/Human.hpp"
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
     * @param title title of the window
     */
    Window(sf::VideoMode video, const sf::String& title) : sf::RenderWindow(video, title) {
        setFramerateLimit(FRAME_RATE);
        initGrid();
        initPlayers();
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

};

#endif //PACMAN_HPP