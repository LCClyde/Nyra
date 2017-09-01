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

#include <nyra/graphics/Renderable.h>

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
template <typename RenderTargetT,
          typename TransformT,
          typename SpriteT>
struct GraphicsType
{
    typedef RenderTargetT RenderTarget;
    typedef TransformT Transform;
    typedef graphics::Renderable<TransformT> Renderable;
    typedef SpriteT Sprite;
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
 *  \class ScriptType
 *  \brief Defines the Scripting classes
 *
 *  \tparam IncludeT The class used to include modules
 *  \tparam VariableT The variable class used in scripting
 *  \tparam ObjectT The class that represents OO object.
 */
template <typename IncludeT,
          typename VariableT,
          typename ObjectT>
struct ScriptType
{
    typedef IncludeT Include;
    typedef VariableT Variable;
    typedef ObjectT Object;
};

/*
 *  \class GameType
 *  \brief Defines the Game level classes.
 *
 *  \tparam WindowTypeT The window type class.
 *  \tparam GraphicsT The graphics type class.
 *  \tparam InputTypeT The input type class.
 *  \tparam ScriptTypeT The scripting type class.
 */
template <typename WindowTypeT,
          typename GraphicsT,
          typename InputTypeT,
          typename ScriptTypeT>
struct GameType
{
    typedef WindowTypeT Window;
    typedef GraphicsT Graphics;
    typedef InputTypeT Input;
    typedef ScriptTypeT Script;
};
}
}

#endif
