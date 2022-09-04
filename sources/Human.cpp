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
    if (isCollided() && m_currentAnim != m_deathAnim) {
        setCurrentAnimation(m_deathAnim);
        m_remainingLives--;
    } else {
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

    if (deathIsOver() && isCollided()) {
        setCollided(false);
        PVector2Grid startPos = Grid::convertNode(m_startPos);
        setX(startPos.second * CASE_SIZE);
        setY(startPos.first * CASE_SIZE);
        m_currentAnim->reset();
        m_deathAnim->play();
        setCurrentDirection(Direction::RIGHT);
    }

    //movements
    if (!isCollided()) {
        move();
        setCurrentAnimation();
        //update anim
        if ((m_currentAnim == m_walkRightAnim || m_currentAnim == m_walkLeftAnim
        || m_currentAnim == m_walkBottomAnim || m_currentAnim == m_walkTopAnim))
            if (getCurrentDirection() == Direction::STOP) m_currentAnim->pause();
            else m_currentAnim->play();

    }

    m_currentAnim->update();

    cout << (m_currentAnim == m_deathAnim) << endl;

    //tile value
    setTileValue(getGrid()->get(PVector2Grid(getGridPosition())));
    if (getLastPacgum() == PacGum::ENERGIZER) setLastPacGum(PacGum::EMPTY);

    //pacgum
    if (Player::getGrid()->getPacGum(getGridPosition()) != PacGum::EMPTY && isPerfectlyPositionned()) {
        m_lastPacGum = getGrid()->getPacGum(getGridPosition());
        Player::getGrid()->setPacGum(getGridPosition(), PacGum::EMPTY);
    }

    // last node
    if (Player::getGrid()->isNode(getGrid()->convertPV2(getGridPosition()))) setLastNode(getGrid()->convertPV2(getGridPosition())); 
}