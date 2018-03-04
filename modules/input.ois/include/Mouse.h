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
#ifndef __NYRA_INPUT_OIS_MOUSE_H__
#define __NYRA_INPUT_OIS_MOUSE_H__

#include <OIS/OISMouse.h>
#include <nyra/input/Mouse.h>
#include <nyra/win/Window.h>
#include <nyra/input/ois/GlobalHandler.h>
#include <nyra/mem/GlobalDependency.h>

namespace nyra
{
namespace input
{
namespace ois
{
/*
 *  \class Mouse
 *  \brief Class to represent user input from the Mouse.
 */
class Mouse : public input::Mouse,
        private mem::GlobalDependency<GlobalHandler>
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the Mouse object.
     *
     *  \param window The window associated with this Mouse.
     */
    Mouse(const win::Window& window);

    /*
     *  \func Destructor
     *  \brief Shuts down the OIS device.
     */
    ~Mouse();

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
     */
    float getScroll() const override;

private:
    const size_t mWinID;
    OIS::Mouse& mMouse;
};
}
}
}

#endif
