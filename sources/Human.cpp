#include "../includes/Human.hpp"
using namespace std;

Human::~Human() {
    delete m_currentAnim;
    delete m_deathAnim;
    delete m_walkRightAnim;
    delete m_walkLeftAnim;
}

void Human::setCurrentAnimation() {
    cout << "je suis passé par là" << endl;
    if (isCollided()) setCurrentAnimation(m_deathAnim);
    else {
        switch (getCurrentDirection()) {
            case Direction::RIGHT:
                m_currentAnim = m_walkRightAnim;
                break;
            case Direction::LEFT:
                m_currentAnim = m_walkLeftAnim;
                break;
        }
    }
    setSprite(m_currentAnim->getSprite());
}

bool Human::isAlive() {
    return m_remainingLives > 0;
}

void Human::update() {
    move();
    setCurrentAnimation();
    if (m_currentAnim == m_walkRightAnim && getCurrentDirection() == Direction::STOP) m_currentAnim->pause();
    else if (m_currentAnim == m_walkRightAnim && m_currentAnim->isPaused() && getCurrentDirection() != Direction::STOP) 
        m_currentAnim->play();
    m_currentAnim->update();
}