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
#include <nyra/media/GameList.h>
#include <nyra/core/Path.h>
#include <nyra/graphics/sfml/Sprite.h>
#include <nyra/graphics/sfml/Video.h>

namespace nyra
{
namespace media
{
//===========================================================================//
GameList::GameList(const std::string& pathname,
                   graphics::RenderTarget& target,
                   input::Keyboard& keyboard) :
    Screen(target, keyboard),
    mPlatform(core::path::split(pathname).back()),
    mDataDir(core::path::join(pathname, "../../")),
    mVideo(new graphics::sfml::Video()),
    mIndex(0),
    mSpacing(5.0 * mTarget.getSize().x() / 320)
{
    const std::vector<std::string> gameFiles =
            core::path::listDirectory(pathname);
    const std::string serialDir = core::path::join(mDataDir, "serial");

    FileToName fileToName = core::read<FileToName>(core::path::join(
            serialDir, mPlatform + "_file_to_name.xml"), core::XML);

    NameToMediaFiles nameToMediaFiles = core::read<NameToMediaFiles>(
            core::path::join(serialDir, mPlatform + "_name_to_media_files.xml"),
            core::XML);

    const double maxWidth = target.getSize().x() / 9.0;

    for (size_t ii = 0; ii < gameFiles.size(); ++ii)
    {
        mGames.push_back(Game());
        Game& game = mGames.back();
        game.pathname = core::path::join(pathname, gameFiles[ii]);
        game.filename = gameFiles[ii];
        game.name = fileToName[game.filename];
        game.files = nameToMediaFiles[game.name];
        game.sprite.reset(new graphics::sfml::Sprite(core::path::join(
                mDataDir, "textures/" + mPlatform + "/" + game.files.boxArtFile)));
        game.sprite->setScale(maxWidth / game.sprite->getSize().x());
    }

    updateIndex();
    playVideo();
}

//===========================================================================//
void GameList::update(double deltaTime)
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
void GameList::render()
{
    mVideo->render(mTarget);
    for (int64_t ii = mIndex - 4; ii < mIndex + 5; ++ii)
    {
        mGames[ii % mGames.size()].sprite->render(mTarget);
    }
}

//===========================================================================//
void GameList::updateIndex()
{
    const float indexCenter = mTarget.getSize().x() / 2.0;

    // Update the center sprite
    updatePosition(*mGames[mIndex].sprite, indexCenter);

    // Update the sprites to the left
    float center = indexCenter - getSpacing(*mGames[mIndex].sprite);
    for (int64_t ii = mIndex - 1; ii > mIndex - 5; --ii)
    {
        updatePosition(*mGames[ii % mGames.size()].sprite, center);
        center -= getSpacing(*mGames[ii % mGames.size()].sprite);
    }

    center = indexCenter + getSpacing(*mGames[mIndex].sprite);
    for (int64_t ii = mIndex + 1; ii < mIndex + 5; ++ii)
    {
        updatePosition(*mGames[ii % mGames.size()].sprite, center);
        center += getSpacing(*mGames[ii % mGames.size()].sprite);
    }
}

//===========================================================================//
float GameList::getSpacing(const graphics::Sprite& sprite) const
{
    return (sprite.getSize().x() * sprite.getScale().x()) + mSpacing;
}

//===========================================================================//
void GameList::updatePosition(graphics::Sprite& sprite,
                              float center) const
{
    static math::Transform2D ident;
    sprite.setPosition(math::Vector2F(center,
            mTarget.getSize().y() * (200.0f / 240.0f)));
    sprite.updateTransform(ident);
}

//===========================================================================//
void GameList::playVideo()
{
    mVideo->initialize(core::path::join(
            mDataDir,
            "videos/" + mPlatform + "/" + mGames[mIndex].files.videoFile));
    mVideo->play();
    mVideo->setScale(mTarget.getSize().x() / mVideo->getSize().x());
    mVideo->setPosition(mTarget.getSize() / 2);
    mVideo->updateTransform(math::Transform2D());
}
}
}
