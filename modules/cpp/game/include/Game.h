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

#include <nyra/game/Options.h>
#include <nyra/game/Map.h>
#include <nyra/core/FPS.h>

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
    Game(const Options& options) :
        mOptions(options),
        mWindow(mOptions.window.name,
                mOptions.window.size,
                mOptions.window.position),
        mTarget(mWindow),
        mMouse(mWindow),
        mKeyboard(mWindow)
    {
        loadMap(mOptions.game.startingMap);

        // Prep the fps object
        mFPS();
    }

    void loadMap(const std::string filename)
    {
        mMap.reset(new Map<GameT>());
        core::read(
                core::path::join(core::DATA_PATH, "maps/" + filename),
                *mMap);
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
            const double delta = mFPS();
            mWindow.update();
            mMouse.update();
            mKeyboard.update();
            mMap->update(delta);
            mTarget.clear(mOptions.graphics.clearColor);
            mMap->render(mTarget);
            mTarget.flush();
        }
    }

private:
    const Options mOptions;
    typename GameT::Window::Window mWindow;
    typename GameT::Graphics::RenderTarget mTarget;
    typename GameT::Input::Mouse mMouse;
    typename GameT::Input::Keyboard mKeyboard;
    std::unique_ptr<Map<GameT>> mMap;
    core::FPS mFPS;
};
}
}

#endif
