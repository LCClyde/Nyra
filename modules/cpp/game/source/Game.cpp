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
#include <nyra/game/Game.h>
#include <nyra/core/Path.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace game
{
Game::Game(const Options& options) :
    mOptions(options),
    mWindow(mOptions.window.name,
            mOptions.window.size,
            mOptions.window.position),
    mInput(mWindow, mOptions.game.inputMap),
    mTarget(mWindow)
{
    loadMap(mOptions.game.startingMap);

    // Prep the fps object
    mFPS();
}

void Game::loadMap(const std::string filename)
{
    mMap.reset(new Map(mInput, mTarget));
    core::read(
            core::path::join(core::DATA_PATH, "maps/" + filename),
            *mMap);
}

void Game::run()
{
    double elapsed = 0.0;
    while (mWindow.isOpen())
    {
        const double delta = mFPS();
        elapsed += delta;

        if (elapsed > 1.0)
            {
            mWindow.setName(mOptions.window.name + " " +
                    core::str::toString(mFPS.getFPS()) +
                    " FPS");
            elapsed = 0.0;
        }
        mWindow.update();
        mInput.update();
        mMap->update(delta);
        mTarget.clear(mOptions.graphics.clearColor);
        mMap->render(mTarget);
        mTarget.flush();
    }
}
}
}
