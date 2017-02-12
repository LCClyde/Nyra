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
#ifndef __NYRA_MEDIA_SCREEN_H__
#define __NYRA_MEDIA_SCREEN_H__

#include <nyra/input/Keyboard.h>
#include <nyra/graphics/RenderTarget.h>
#include <nyra/media/Config.h>

namespace nyra
{
namespace media
{
/*
 *  \class Screen
 *  \brief Base class for all media center screens.
 */
class Screen
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the screen object
     *
     *  \param target The render target
     *  \param keyboard The keyboard for input
     */
    Screen(const Config& config,
           graphics::RenderTarget& target,
           input::Keyboard& keyboard);

    /*
     *  \func Destructor
     *  \brief Necessary for proper inheritance.
     */
    virtual ~Screen() = default;

    /*
     *  \func update
     *  \brief Updates the screen
     *
     *  \param delta The time in seconds since the last update
     */
    virtual void update(double delta) = 0;

    /*
     *  \func render
     *  \brief Renders the screen
     */
    virtual void render() = 0;

protected:
    const Config& mConfig;
    graphics::RenderTarget& mTarget;
    input::Keyboard& mKeyboard;
};
}
}

#endif

