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
#ifndef __NYRA_GAME_OPTIONS_H__
#define __NYRA_GAME_OPTIONS_H__

#include <string>
#include <nyra/math/Vector2.h>
#include <nyra/img/Color.h>

namespace nyra
{
namespace game
{
/*
 *  \class WindowOptions
 *  \brief Options related to the Window the game is running in.
 */
struct  WindowOptions
{
    /*
     *  \func Constructor
     *  \brief Sets default values for the Window
     */
    WindowOptions();

    /*
     *  \var name
     *  \brief The name(title) of the Window.
     */
    std::string name;

    /*
     *  \var size
     *  \brief The initial size of the render area of the window in pixels.
     */
    math::Vector2U size;

    /*
     *  \var position
     *  \brief The position of the window in pixels from the top left corner
     *         of the primary monitor.
     */
    math::Vector2I position;
};

/*
 *  \class GraphicsOptions
 *  \brief Options related to the Graphics within the game.
 */
struct GraphicsOptions
{
    /*
     *  \func Constructor
     *  \brief Sets default values for the Graphics
     */
    GraphicsOptions();

    /*
     *  \var clearColor
     *  \brief The color to use when clearing the render target.
     */
    img::Color clearColor;
};

/*
 *  \class Options
 *  \brief The top level game options.
 */
struct Options
{
    /*
     *  \var window
     *  \brief The window options (see above)
     */
    WindowOptions window;

    /*
     *  \var graphics
     *  \brief The graphics options (see above)
     */
    GraphicsOptions graphics;
};
}
}

#endif
