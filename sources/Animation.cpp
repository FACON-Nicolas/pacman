#include "../includes/Animation.hpp"

void Animation::play() {
    m_isPaused = false; 
}

void Animation::pause() { 
    m_isPaused = true; 
}

void Animation::stop() {
    pause();
    m_index = 0;
}

bool Animation::isPaused() {
    return m_isPaused;
}

void Animation::update() {
    if (!isPaused()) {
        m_sprite.setTexture(*getTexture());
        m_index = ((m_valueToInc++)/m_dividerUpdate) % m_size;
        std::cout << "/images/" + m_character + "/" + m_name + std::to_string(m_index) + ".png" << std::endl;
    }
}

Animation::~Animation() {
    
}