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
#include <nyra/media/GameSelectionScreen.h>
#include <nyra/graphics/sfml/Sprite.h>
#include <nyra/graphics/sfml/Video.h>
#include <nyra/media/Config.h>

namespace nyra
{
namespace media
{
//===========================================================================//
GameSelectionScreen::GameSelectionScreen(const std::string& platform,
                                         const Config& config,
                                         graphics::RenderTarget& target,
                                         input::Keyboard& keyboard) :
    Screen(config, target, keyboard),
    mGamePath(core::path::join(mConfig.dataPath,
                               "roms/" + mPlatform)),
    mPlatform(platform),
    mGames(core::read<std::vector<Game> >(
            core::path::join(mConfig.dataPath,
                             "serial/games_" + mPlatform + ".json"))),
    mVideo(new graphics::sfml::Video()),
    mIndex(0),
    mLayout(core::read<GameListLayout>(
            core::path::join(mConfig.dataPath,
                             "serial/game_list_layout.json"))),
    mBoxArt(mLayout, mGames)
{
    const std::string boxArtPath = core::path::join(
            mConfig.dataPath, "textures/" + mPlatform);

    for (Game& game : mGames)
    {
        if (!game.boxArtFile.empty())
        {
            game.sprite.reset(new graphics::sfml::Sprite(
                    core::path::join(boxArtPath, game.boxArtFile)));
        }
        else
        {
            game.sprite.reset(new graphics::sfml::Sprite(
                    core::path::join(boxArtPath, "Dragon Warrior (USA).png")));
        }
    }
    mBoxArt.resetLayout(mTarget.getSize());
    updateIndex();
    playVideo();
}

//===========================================================================//
void GameSelectionScreen::update(double deltaTime)
{
    bool update = false;
    if (mKeyboard.getButtonPressed(input::KEY_RIGHT))
    {
        ++mIndex;
        update = true;
    }
    else if (mKeyboard.getButtonPressed(input::KEY_LEFT))
    {
        --mIndex;
        update = true;
    }

    if (update)
    {
        mIndex %= mGames.size();
        updateIndex();
    }

    if (mKeyboard.getButtonReleased(input::KEY_RIGHT) ||
        mKeyboard.getButtonReleased(input::KEY_LEFT))
    {
        playVideo();
    }

    mVideo->update();
}

//===========================================================================//
void GameSelectionScreen::render()
{
    mVideo->render(mTarget);
    mBoxArt.render(mTarget);
}

//===========================================================================//
void GameSelectionScreen::updateIndex()
{
    mBoxArt.updateIndex(mIndex);
}

//===========================================================================//
void GameSelectionScreen::playVideo()
{
    std::cout << mGames[mIndex].name << "\n";
    if (!mGames[mIndex].videoFile.empty())
    {
        mVideo->initialize(core::path::join(
                mConfig.dataPath,
                "videos/" + mPlatform + "/" + mGames[mIndex].videoFile));
        mVideo->play();
        const double scale = mLayout.videoScale * mConfig.getMinScreenScale();
        mVideo->setScale(scale);
        mVideo->setPosition(mLayout.videoPosition * mConfig.getScreenScale());
        mVideo->updateTransform(math::Transform2D());
    }
    else
    {
        mVideo->stop();
    }
}
}
}
