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
#ifndef __NYRA_GAME_GAME_H__
#define __NYRA_GAME_GAME_H__

#include <nyra/game/GameOptions.h>

namespace nyra
{
namespace game
{
/*
 *  \class Game
 *  \brief Top level class to encapsulate a video game away into a single
 *         object.
 *
 *  \tparam GameT The game type information. This should be something from
 *          GameTypes.h to be sure to include everything necessary.
 */
template <typename GameT>
class Game
{
public:
    /*
     *  \func Constructor
     *  \brief Sets the game object.
     *
     *  \param options A nested struct of game options.
     */
    Game(const GameOptions& options) :
        mOptions(options),
        mWindow(mOptions.window.name,
                mOptions.window.size,
                mOptions.window.position),
        mTarget(mWindow),
        mMouse(mWindow),
        mKeyboard(mWindow)
    {
    }

    /*
     *  \func run
     *  \brief Runs the game. This function blocks until the game
     *         has ended.
     */
    void run()
    {
        while (mWindow.isOpen())
        {
            mWindow.update();
            mMouse.update();
            mKeyboard.update();
            mTarget.clear(mOptions.graphics.clearColor);
            mTarget.flush();
        }
    }

private:
    const GameOptions mOptions;
    typename GameT::Window::Window mWindow;
    typename GameT::Graphics::RenderTarget mTarget;
    typename GameT::Input::Mouse mMouse;
    typename GameT::Input::Keyboard mKeyboard;
};
}
}

#endif
