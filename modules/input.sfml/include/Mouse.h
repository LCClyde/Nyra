/*
 * Copyright (c) 2017 Clyde Stanfield
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
#ifndef __NYRA_INPUT_SFML_MOUSE_H__
#define __NYRA_INPUT_SFML_MOUSE_H__

#include <nyra/input/Mouse.h>
#include <nyra/win/sfml/Window.h>

namespace nyra
{
namespace input
{
namespace sfml
{
/*
 *  \class Mouse
 *  \brief Class to represent user input from the Mouse.
 */
class Mouse : public input::Mouse
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the Mouse object.
     *
     *  \param window The window associated with this Mouse. This must
     *         be an SFML window.
     */
    Mouse(win::Window& window);

    /*
     *  \func update
     *  \brief Must be called to update mouse information.
     */
    void update() override;

    /*
     *  \func getPosition
     *  \brief Gets the position of the mouse relative to the window
     *         associated with the device.
     */
    math::Vector2F getPosition() const override;

    /*
     *  \func getDelta
     *  \brief Gets the change in position of the position of the mouse
     *         since the last update.
     */
    math::Vector2F getDelta() const override;

    /*
     *  \func getScroll
     *  \brief Gets the change in the scroll value since the last update.
     *         TODO: This does not work.
     */
    float getScroll() const override;

    void setScroll(float delta);

private:
    const win::sfml::Window& mWindow;
    math::Vector2F mPosition;
    math::Vector2F mDelta;
    bool mScrollSet;
    float mScroll;
};
}
}
}

#endif
