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
#include <nyra/input/ois/Mouse.h>

namespace nyra
{
namespace input
{
namespace ois
{
//===========================================================================//
Mouse::Mouse(const win::Window& window) :
    mWinID(window.getID()),
    mMouse(*static_cast<OIS::Mouse*>(getGlobalInstance().get(mWinID)->
            createInputObject(OIS::OISMouse, false)))
{
    // TODO: This should register itself with the window to change extents
    //       if they do change.
    const OIS::MouseState& mouseState = mMouse.getMouseState();
    mouseState.width  = window.getSize().x();
    mouseState.height = window.getSize().y();
}

//===========================================================================//
Mouse::~Mouse()
{
    if (getGlobalInstance().isInitialized())
    {
        getGlobalInstance().get(mWinID)->destroyInputObject(&mMouse);
    }
}

//===========================================================================//
math::Vector2F Mouse::getPosition() const
{
    const OIS::MouseState& state = mMouse.getMouseState();
    return math::Vector2F(static_cast<float>(state.X.abs),
                          static_cast<float>(state.Y.abs));
}

//===========================================================================//
math::Vector2F Mouse::getDelta() const
{
    const OIS::MouseState& state = mMouse.getMouseState();
    return math::Vector2F(static_cast<float>(state.X.rel),
                          static_cast<float>(state.Y.rel));
}

//===========================================================================//
float Mouse::getScroll() const
{
    return static_cast<float>(mMouse.getMouseState().Z.rel);
}

//===========================================================================//
void Mouse::update()
{
    mMouse.capture();
    std::bitset<3> buttons;
    const OIS::MouseState& state = mMouse.getMouseState();
    buttons[input::Mouse::MOUSE_LEFT] = state.buttonDown(OIS::MB_Left);
    buttons[input::Mouse::MOUSE_RIGHT] = state.buttonDown(OIS::MB_Right);
    buttons[input::Mouse::MOUSE_MIDDLE] = state.buttonDown(OIS::MB_Middle);
    updateButtons(buttons);

}
}
}
}
