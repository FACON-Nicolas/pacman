#include "../includes/Human.hpp"
using namespace std;

Human::~Human() {
    m_currentAnim = nullptr;
    delete m_deathAnim;
    delete m_walkRightAnim;
    delete m_walkLeftAnim;
    delete m_walkTopAnim;
    delete m_walkBottomAnim;
}

void Human::setCurrentAnimation() {
    if (isCollided()) setCurrentAnimation(m_deathAnim);
    else {
        switch (getCurrentDirection()) {
            case Direction::RIGHT:
                m_currentAnim = m_walkRightAnim;
                break;
            case Direction::LEFT:
                m_currentAnim = m_walkLeftAnim;
                break;
            case Direction::TOP:
                m_currentAnim = m_walkTopAnim;
                break;
            case Direction::BOTTOM:
                m_currentAnim = m_walkBottomAnim;
                break;
        }
    }
    setSprite(m_currentAnim->getSprite());
}

bool Human::isAlive() {
    return m_remainingLives > 0;
}

void Human::update() {
    //movements
    move();

    //animation
    setCurrentAnimation();

    //update anim
    if (m_currentAnim == m_walkRightAnim && getCurrentDirection() == Direction::STOP) m_currentAnim->pause();
    else if (m_currentAnim == m_walkRightAnim && m_currentAnim->isPaused() && getCurrentDirection() != Direction::STOP) 
        m_currentAnim->play();
    m_currentAnim->update();

    //tile value
    setTileValue(getGrid()->get(PVector2Grid(getGridPosition())));

    //pacgum
    if (Player::getGrid()->getPacGum(getGridPosition()) != PacGum::EMPTY && isPerfectlyPositionned()) 
        Player::getGrid()->setPacGum(getGridPosition(), PacGum::EMPTY);

    // last node
    if (Player::getGrid()->isNode(getGrid()->convertPV2(getGridPosition()))) setLastNode(getGrid()->convertPV2(getGridPosition())); 
}