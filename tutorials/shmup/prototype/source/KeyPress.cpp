#include "KeyPress.h"

KeyPress::KeyPress(sf::Keyboard::Key key) :
    mKey(key),
    mPrevState(false)
{
}

bool KeyPress::get()
{
    const bool current = sf::Keyboard::isKeyPressed(mKey);
    const bool prev = mPrevState;
    mPrevState = current;

    return current && !prev;
}
