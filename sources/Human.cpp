#include "../includes/Human.hpp"

Human::~Human() {
    delete m_currentAnim;
    delete m_deathAnim;
    delete m_walkAnim;
}

void Human::setCurrentAnimation() {
    setCurrentAnimation(m_isCollidingEnemy ? m_deathAnim : m_walkAnim);
    setSprite(m_currentAnim->getSprite());
}

bool Human::isAlive() {
    return m_remainingLives > 0;
}

void Human::update() {
    move();
    if (m_currentAnim == m_walkAnim && getCurrentDirection() == Direction::STOP) m_currentAnim->pause();
    else if (m_currentAnim == m_walkAnim && m_currentAnim->isPaused() && getCurrentDirection() != Direction::STOP) 
        m_currentAnim->play();
    m_currentAnim->update();
}