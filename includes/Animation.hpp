#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>

class Animation {

public:

    Animation(int size, std::string name) : m_size(size), m_name(name) {}
    void play();
    void pause();

private:

    int m_size;
    bool m_isPaused;
    std::string m_name;
    
};

#endif //ANIMATION_HPP