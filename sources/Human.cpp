#include "../includes/Human.hpp"

Human::~Human() {

}

void Human::setCurrentAnimation() {
    m_currentAnim =  m_isCollidingEnemy ? m_deathAnim : m_walkAnim;
    setSprite(&m_currentAnim->getSprite());
}

void Human::update() {
    move();
    if (m_currentAnim == m_walkAnim && getCurrentDirection() == Direction::STOP) m_currentAnim->pause();
    else if (m_currentAnim == m_walkAnim && m_currentAnim->isPaused() && getCurrentDirection() != Direction::STOP) 
        m_currentAnim->play();
}