#ifndef PACMAN_HPP
#define PACMAN_HPP

#define WINDOW_WIDTH    1600
#define WINDOW_HEIGHT   900
#define CASE_SIZE       45
#define FRAME_RATE      60

#include "SFML/Graphics.hpp"
#include "../includes/Grid.hpp"

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
    void keyboardControls();

    /**
     * @brief check events (key pressed, mouse used, window closed, etc)
     * 
     */
    void event();

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

    void drawWall(PVector2Grid position);

    sf::Texture textures[GRID_HEIGHT][GRID_WIDTH];
    sf::Sprite sprites[GRID_HEIGHT][GRID_WIDTH];

    Grid m_grid;

};

#endif //PACMAN_HPP