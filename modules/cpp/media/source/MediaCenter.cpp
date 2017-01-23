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
#include <nyra/media/MediaCenter.h>
#include <nyra/media/GameList.h>
#include <nyra/media/PlayGame.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace media
{
//===========================================================================//
MediaCenter::MediaCenter(double scale) :
    mPlatformToBinary(core::read<PlatformToBinary>(
            "/home/clyde/workspace/Nyra/media_data/serial/platform.xml",
            core::XML)),
    mPlatform("nes"),
    mWindow("Media Center",
            math::Vector2U(320 * scale, 240 * scale),
            math::Vector2I(0, 0)),
    mRenderTarget(mWindow)
{
    openGameSelect();
}

//===========================================================================//
void MediaCenter::run()
{
    while (mWindow.isOpen())
    {
        mWindow.update();
        mKeyboard.update();

        mScreen->update(0.0);
        mRenderTarget.clear(img::Color::BLACK);
        mScreen->render();
        mRenderTarget.flush();

        update();
    }
}

//===========================================================================//
void MediaCenter::update()
{
    switch (mState)
    {
    case GAME_SELECT:
        if (mKeyboard.getButtonPressed(input::KEY_ENTER))
        {
            openPlayGame(dynamic_cast<GameList*>(
                    mScreen.get())->getGame().pathname);
        }
        break;
    case PLAYING_GAME:
        if (mKeyboard.getButtonPressed(input::KEY_ESCAPE))
        {
            openGameSelect();
        }
        break;
    }
}

//===========================================================================//
void MediaCenter::openGameSelect()
{
    const std::string romsList = core::path::join(
            "/home/clyde/workspace/Nyra/media_data/roms/", mPlatform);
    mScreen.reset(new GameList(romsList, mRenderTarget, mKeyboard));
    mState = GAME_SELECT;
}

//===========================================================================//
void MediaCenter::openPlayGame(const std::string& pathname)
{
    mScreen.reset(new PlayGame(mPlatformToBinary[mPlatform],
                               pathname,
                               mRenderTarget,
                               mKeyboard));
    mState = PLAYING_GAME;
}
}
}
