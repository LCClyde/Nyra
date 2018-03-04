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
#ifndef __NYRA_INPUT_MOUSE_H__
#define __NYRA_INPUT_MOUSE_H__

#include <nyra/math/Vector2.h>
#include <nyra/input/Buttons.h>

namespace nyra
{
namespace input
{
/*
 *  \type MouseButton
 *  \brief Index of mouse buttons.
 */
enum MouseButton
{
    MOUSE_LEFT = 0,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,
    MOUSE_MAX
};

/*
 *  \class Mouse
 *  \brief Class to represent user input from the Mouse.
 */
class Mouse : public Buttons<MOUSE_MAX>
{
public:
    /*
     *  \func update
     *  \brief Must be called to update mouse information.
     */
    virtual void update() = 0;

    /*
     *  \func getPosition
     *  \brief Gets the position of the mouse relative to the window
     *         associated with the device.
     */
    virtual math::Vector2F getPosition() const = 0;

    /*
     *  \func getDelta
     *  \brief Gets the change in position of the position of the mouse
     *         since the last update.
     */
    virtual math::Vector2F getDelta() const = 0;

    /*
     *  \func getScroll
     *  \brief Gets the change in the scroll value since the last update.
     */
    virtual float getScroll() const = 0;
};
}
}

#endif
