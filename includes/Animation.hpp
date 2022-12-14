#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <iostream>

#include "../includes/Constant.hpp"

#include "SFML/Graphics.hpp"

/**
 * @brief Animation class is used to sort textures in an array and link them to a sprite to make an animation.
 * 
 */
class Animation {

public:

    /**
     * @brief Construct a new Animation object
     * 
     * @param size size of textures' array
     * 
     * @param name name of animation
     */
    Animation(int size, std::string character, std::string name, bool reverse=false, bool loop=true) : m_size(size), m_character(character), m_name(name), m_loop(loop), m_index(0) {
        m_isPaused = false; 
        m_valueToInc = 0;
        for (int i = 1; i <= size; i++) {
            sf::Texture t;
            t.loadFromFile("images/" + character + "/" + name + std::to_string(i) + ".png", sf::IntRect(0, 0, CASE_SIZE, CASE_SIZE));
            m_textures.push_back(t);
        } if (reverse) 
            for (int i = 1; i < size-1; i++) {
                sf::Texture t;
                t.loadFromFile("images/" + character + "/" + name + std::to_string(size-i) + ".png",  sf::IntRect(0, 0, CASE_SIZE, CASE_SIZE));
                m_textures.push_back(t);
                m_size++;
            }
        update();
    }

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
    sf::Sprite* getSprite() { return &m_sprite; }

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
    sf::Texture* getTexture() { return &m_textures[m_index]; }

    /**
     * @brief method called at each frame.
     * 
     */
    void update();

    /**
     * @brief reset animation
     * 
     */
    void reset() { m_index = 0; }

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

    /**
     * @brief character's name
     * 
     */
    std::string m_character;

    /**
     * @brief at each time m_valueToInc will be % m_dividerUpdate, then the sprite's texture will change
     * 
     */
    static inline int m_dividerUpdate = 5;

    /**
     * @brief value to increment at each update method calls.
     * 
     */
    int m_valueToInc;

    /**
     * @brief boolean use to know if the animation should be played infinitely
     * 
     */
    bool m_loop;
    
};

#endif //ANIMATION_HPP