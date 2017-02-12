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
#include <nyra/core/Path.h>
#include <nyra/graphics/sfml/Sprite.h>
#include <nyra/graphics/sfml/Video.h>
#include <nyra/media/Config.h>

namespace nyra
{
namespace media
{
//===========================================================================//
GameSelectionScreen::GameSelectionScreen(const std::string& pathname,
                                         const Config& config,
                                         graphics::RenderTarget& target,
                                         input::Keyboard& keyboard) :
    Screen(config, target, keyboard),
    mPlatform(core::path::split(pathname).back()),
    mVideo(new graphics::sfml::Video()),
    mIndex(0),
    mLayout(core::read<GameListLayout>(
            core::path::join(mConfig.dataPath,
                             "serial/game_list_layout.json"))),
    mBoxArt(mLayout, mGames)
{
    const std::vector<std::string> gameFiles =
            core::path::listDirectory(pathname);
    const std::string serialDir = core::path::join(mConfig.dataPath, "serial");

    FileToName fileToName = core::read<FileToName>(core::path::join(
            serialDir, mPlatform + "_file_to_name.xml"), core::XML);

    NameToMediaFiles nameToMediaFiles = core::read<NameToMediaFiles>(
            core::path::join(serialDir, mPlatform + "_name_to_media_files.xml"),
            core::XML);

    for (size_t ii = 0; ii < gameFiles.size(); ++ii)
    {
        mGames.push_back(Game());
        Game& game = mGames.back();
        game.pathname = core::path::join(pathname, gameFiles[ii]);
        game.filename = gameFiles[ii];
        game.name = fileToName[game.filename];
        game.files = nameToMediaFiles[game.name];
        game.sprite.reset(new graphics::sfml::Sprite(core::path::join(
                mConfig.dataPath, "textures/" + mPlatform + "/" + game.files.boxArtFile)));
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
float GameSelectionScreen::getSpacing(const graphics::Sprite& sprite) const
{
    return (sprite.getSize().x() * sprite.getScale().x()) + 5;//mSpacing;
}

//===========================================================================//
void GameSelectionScreen::playVideo()
{
    mVideo->initialize(core::path::join(
            mConfig.dataPath,
            "videos/" + mPlatform + "/" + mGames[mIndex].files.videoFile));
    mVideo->play();
    mVideo->setScale(mTarget.getSize().x() / mVideo->getSize().x());
    mVideo->setPosition(mTarget.getSize() / 2);
    mVideo->updateTransform(math::Transform2D());
}
}
}
