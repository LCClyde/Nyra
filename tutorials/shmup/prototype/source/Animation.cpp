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
#include <iostream>
#include "Animation.h"

Animation::Animation(int rows,
                     int columns,
                     int start,
                     int end,
                     float time,
                     bool looping,
                     sf::Sprite& sprite) :
    mRows(rows),
    mColumns(columns),
    mStart(start),
    mEnd(end),
    mTimePerFrame(time / (mRows * mColumns)),
    mCurrentTime(0.0f),
    mCurrentFrame(mStart),
    mSprite(&sprite),
    mRectWidth(sprite.getTexture()->getSize().x / mColumns),
    mRectHeight(sprite.getTexture()->getSize().y / mRows),
    mDirection(end > start ? 1 : -1),
    mLooping(looping)
{
}

void Animation::reset()
{
    mCurrentTime = 0.0f;
    mCurrentFrame = mStart;
    setRect();
}

void Animation::update(float delta)
{
    if (mCurrentFrame == mEnd && !mLooping)
    {
        return;
    }

    mCurrentTime += delta;
    if (mCurrentTime > mTimePerFrame)
    {
        mCurrentTime = 0.0f;
        mCurrentFrame += mDirection;

        if (mLooping && mCurrentFrame > mEnd)
        {
            mCurrentFrame = mStart;
        }

        setRect();
    }
}

void Animation::setRect()
{
    const int row = mCurrentFrame % mRows;
    const int col = mCurrentFrame / mRows;
    sf::IntRect rect(col * mRectWidth,
                     row * mRectHeight,
                     mRectWidth,
                     mRectHeight);
    mSprite->setTextureRect(rect);
}
