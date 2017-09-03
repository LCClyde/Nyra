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
#include <nyra/anim/Frame.h>

namespace nyra
{
namespace anim
{
//===========================================================================//
Frame::Frame(size_t startFrame,
             size_t endFrame,
             double duration,
             Animation::PlayType playType,
             const math::Vector2U& numTiles,
             graphics::Sprite& sprite) :
    mSize(sprite.getSize().x / numTiles.x,
          sprite.getSize().y / numTiles.y),
    mSprite(sprite),
    mCurrentFrame(-1),
    mInterpolate(0,
                 endFrame - startFrame + 1,
                 duration,
                 playType,
                 mCurrentFrame)
{
    for (size_t ii = startFrame; ii < endFrame + 1; ++ii)
    {
        const size_t row = ii / numTiles.x;
        const size_t col = ii % numTiles.x;
        math::Vector2U frame(col * mSize.x,
                             row * mSize.y);
        mFrames.push_back(frame);
    }
}

//===========================================================================//
void Frame::update(double deltaTime)
{
    size_t prev = mCurrentFrame;
    mInterpolate.update(deltaTime);

    // It is possible for the current frame to go one passed the valid
    // frames. This would only occur if the time lines up perfectly
    // which in practice will never occur, but let's account for it
    // anyways.
    mCurrentFrame = std::min(mCurrentFrame, mFrames.size() - 1);

    if (mCurrentFrame != prev)
    {
        mSprite.setFrame(mFrames[mCurrentFrame], mSize);
    }
}

//===========================================================================//
void Frame::reset()
{
    mCurrentFrame = -1;
    Animation::reset();
}
}
}
