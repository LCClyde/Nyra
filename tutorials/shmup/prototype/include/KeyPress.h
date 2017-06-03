#ifndef __SHMUP_KEY_PRESS_H__
#define __SHMUP_KEY_PRESS_H__

#include <SFML/Graphics.hpp>

class KeyPress
{
public:
    KeyPress(sf::Keyboard::Key key);

    bool get();

private:
    const sf::Keyboard::Key mKey;
    bool mPrevState;
};

#endif
