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
#include <nyra/game/Input.h>
#include <nyra/game/Types.h>

namespace nyra
{
namespace game
{
/*
 *  \class Game
 *  \brief Top level class to encapsulate a video game away into a single
 *         object.
 */
class Game
{
public:
    /*
     *  \func Constructor
     *  \brief Sets the game object.
     *
     *  \param options A nested struct of game options.
     */
    Game(const Options& options);

    /*
     *  \func loadMap
     *  \brief Loads a map object
     *
     *  \param The filename of the map.
     */
    void loadMap(const std::string filename);

    /*
     *  \func run
     *  \brief Runs the game. This function blocks until the game
     *         has ended.
     */
    void run();

private:
    const Options mOptions;
    WindowT mWindow;
    Input mInput;
    RenderTargetT mTarget;
    std::unique_ptr<Map> mMap;
    core::FPS mFPS;
};
}
}

#endif
