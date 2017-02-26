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
#include <nyra/media/BoxArtList.h>
#include <nyra/media/Config.h>

namespace nyra
{
namespace media
{
//===========================================================================//
BoxArtList::BoxArtList(const GameListLayout& layout,
                       std::vector<Game>& games) :
    mLayout(layout),
    mGames(games),
    mMinIndex(0),
    mMaxIndex(0)
{
}

//===========================================================================//
void BoxArtList::resetLayout(const math::Vector2U& size)
{
    mSize = size;
}

//===========================================================================//
void BoxArtList::scaleIndex(size_t index,
                            double screenScale)
{
    // Wait for the sprite to show up
    while (!mGames[index].sprite.get())
    {
    }

    const double spriteSize = mLayout.boxLayout ==
            GameListLayout::HORIZONTAL ?
                    mGames[index].sprite->getSize().y() :
                    mGames[index].sprite->getSize().x();
    const double spriteScale =
            mLayout.boxSize / spriteSize;
    mGames[index].sprite->setScale(spriteScale * screenScale);
}

//===========================================================================//
void BoxArtList::updateIndex(size_t index)
{
    scaleIndex(index, getScreenScale());

    if (mLayout.boxLayout == GameListLayout::HORIZONTAL)
    {
        updateIndexImpl(index, mSize.x() / 2.0,
                        mGames[index].sprite->getScaledSize().x());
    }
    else
    {
        updateIndexImpl(index, mSize.y() / 2.0,
                        mGames[index].sprite->getScaledSize().y());
    }
}

//===========================================================================//
void BoxArtList::updateIndexImpl(size_t index,
                                 double center,
                                 double centerSpriteSize)
{
    const double screenScale = getScreenScale();
    double position = center + centerSpriteSize / 2.0;

    updatePosition(index, screenScale, -1.0, position);
    size_t ii = index;

    mMinIndex = index;
    mMaxIndex = index + 1;

    // Add games to the left
    while (position > 0.0 && ii != 0)
    {
        --ii;
        mMinIndex = ii;
        updatePosition(ii, screenScale, -1.0, position);
    }

    // Add games to the right
    // TODO: This is a bit wasteful, but doesn't really matter all that much.
    position = center - centerSpriteSize / 2.0;
    updatePosition(index, screenScale, 1.0, position);
    ii = index + 1;

    while (position < center * 2.0 && ii < mGames.size())
    {
        updatePosition(ii, screenScale, 1.0, position);
        ++ii;
        mMaxIndex = ii;
    }
}

//===========================================================================//
void BoxArtList::render(graphics::RenderTarget& target)
{
    for (size_t ii = mMinIndex; ii < mMaxIndex; ++ii)
    {
        mGames[ii].sprite->render(target);
    }
}

//===========================================================================//
double BoxArtList::getScreenScale() const
{
    if (mLayout.boxLayout == GameListLayout::HORIZONTAL)
    {
        return static_cast<double>(mSize.y()) / Config::DEFAULT_SIZE.y();
    }
    return static_cast<double>(mSize.x()) / Config::DEFAULT_SIZE.x();
}

//===========================================================================//
void BoxArtList::updatePosition(size_t ii,
                                double screenScale,
                                double direction,
                                double& position)
{
    scaleIndex(ii, screenScale);
    if (mLayout.boxLayout == GameListLayout::HORIZONTAL)
    {
        updatePositionHorizontal(ii, screenScale, direction, position);
    }
    else
    {
        updatePositionVertical(ii, screenScale, direction, position);
    }
}

//===========================================================================//
void BoxArtList::updatePositionHorizontal(size_t ii,
                                          double screenScale,
                                          double direction,
                                          double& position)
{
    const double halfSize = mGames[ii].sprite->getScaledSize().x() / 2.0;
    position += (halfSize * direction);
    mGames[ii].sprite->setPosition(math::Vector2F(
            position, mLayout.boxPosition * screenScale));
    mGames[ii].sprite->updateTransform(mParent);
    position += (halfSize * direction);
    position += (mLayout.boxSpacing * screenScale) * direction;
}

//===========================================================================//
void BoxArtList::updatePositionVertical(size_t ii,
                                        double screenScale,
                                        double direction,
                                        double& position)
{
    const double halfSize = mGames[ii].sprite->getScaledSize().y() / 2.0;
    position += (halfSize * direction);
    mGames[ii].sprite->setPosition(math::Vector2F(
            mLayout.boxPosition * screenScale, position));
    mGames[ii].sprite->updateTransform(mParent);
    position += (halfSize * direction);
    position += (mLayout.boxSpacing * screenScale) * direction;
}
}
}
