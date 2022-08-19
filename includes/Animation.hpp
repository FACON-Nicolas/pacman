#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>

#include "SFML/Graphics.hpp"

class Animation {

public:

    /**
     * @brief Construct a new Animation object
     * 
     * @param size size of textures' array
     * 
     * @param name name of animation
     */
    Animation(int size, std::string name) : m_size(size), m_name(name), m_index(0) {}

    /**
     * @brief Destroy the Animation object
     * 
     */
    ~Animation();

    /**
     * @brief play animation.
     * 
     */
    void play();

    /**
     * @brief 
     * 
     */
    void pause();

    /**
     * @brief stop animation
     * 
     */
    void stop();

    /**
     * @brief Get the Sprite object
     * 
     * @return sf::Sprite 
     */
    sf::Sprite getSprite() const { return m_sprite; }

    /**
     * @brief check if the animation is paused
     * 
     * @return true if the animation is paused
     * 
     * @return false if the animation is not paused
     */
    bool isPaused();

    /**
     * @brief Get the Texture object
     * 
     * @return sf::Texture current texture
     */
    sf::Texture getTexture() const { return m_textures[m_index]; }

    /**
     * @brief method called at each frame.
     * 
     */
    void update();

private:

    /**
     * @brief number of textures
     * 
     */
    int m_size;

    /**
     * @brief index of texture loaded.
     * 
     */
    int m_index;

    /**
     * @brief define if the animation is paused.
     * 
     */
    bool m_isPaused;

    /**
     * @brief name of animation
     * 
     */
    std::string m_name;

    /**
     * @brief array of textures
     * 
     */
    std::vector<sf::Texture> m_textures;

    /**
     * @brief sprite
     * 
     */
    sf::Sprite m_sprite;
    
};

#endif //ANIMATION_HPP