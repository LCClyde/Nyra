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
#ifndef __NYRA_GAME_TYPES_H__
#define __NYRA_GAME_TYPES_H__

namespace nyra
{
namespace game
{
/*
 *  \class WindowType
 *  \brief Defines the Window classes.
 *
 *  \tparam WindowT The class for the primary Window
 */
template <typename WindowT>
struct WindowType
{
    typedef WindowT Window;
};

/*
 *  \class GraphicsType
 *  \brief Defines the Graphic classes.
 *
 *  \tparam RenderTargetT The class for the render target.
 */
template <typename RenderTargetT>
struct GraphicsType
{
    typedef RenderTargetT RenderTarget;
};

/*
 *  \class InputType
 *  \brief Defines the Input classes.
 *
 *  \tparam MouseT The class for the mouse.
 *  \tparam KeyboardT The class for the keyboard.
 */
template <typename MouseT,
          typename KeyboardT>
struct InputType
{
    typedef MouseT Mouse;
    typedef KeyboardT Keyboard;
};

/*
 *  \class GameType
 *  \brief Defines the Game level classes.
 *
 *  \tparam WindowTypeT The window type class.
 *  \tparam GraphicsT The graphics type class.
 *  \tparam InputTypeT The input type class.
 */
template <typename WindowTypeT,
          typename GraphicsT,
          typename InputTypeT>
struct GameType
{
    typedef WindowTypeT Window;
    typedef GraphicsT Graphics;
    typedef InputTypeT Input;
};
}
}

#endif
