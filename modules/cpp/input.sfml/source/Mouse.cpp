/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include <nyra/input/sfml/Mouse.h>
#include <SFML/Window.hpp>

namespace nyra
{
namespace input
{
namespace sfml
{
//===========================================================================//
Mouse::Mouse(const win::Window& window) :
    mWindow(dynamic_cast<const win::sfml::Window&>(window))
{
    update();

    // Reset the delta to zero
    mDelta.x = 0.0f;
    mDelta.y = 0.0f;
}

//===========================================================================//
math::Vector2F Mouse::getPosition() const
{
    return mPosition;
}

//===========================================================================//
math::Vector2F Mouse::getDelta() const
{
    return mDelta;
}

//===========================================================================//
float Mouse::getScroll() const
{
    return 0.0f;
}

//===========================================================================//
void Mouse::update()
{
    const sf::Window& window =
            *static_cast<const sf::Window*>(mWindow.getNative());
    const sf::Vector2i position = sf::Mouse::getPosition(window);
    mDelta.x = position.x - mPosition.x;
    mDelta.y = position.y - mPosition.y;
    mPosition.x = position.x;
    mPosition.y = position.y;

    std::bitset<input::MOUSE_MAX> buttons;
    buttons[input::MOUSE_LEFT] = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    buttons[input::MOUSE_RIGHT] = sf::Mouse::isButtonPressed(sf::Mouse::Right);
    buttons[input::MOUSE_MIDDLE] = sf::Mouse::isButtonPressed(sf::Mouse::Middle);
    updateButtons(buttons);
}
}
}
}
