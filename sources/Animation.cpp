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
    m_sprite.setTexture(*getTexture());
    if (!isPaused()) {
        if (m_loop) m_index = ((m_valueToInc++)/m_dividerUpdate) % m_size;
        else if (m_index < m_textures.size()) m_index++;
        else pause();
    }
}

Animation::~Animation() {
    
}