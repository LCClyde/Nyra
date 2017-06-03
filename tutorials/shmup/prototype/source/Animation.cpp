#include <iostream>
#include "Animation.h"

Animation::Animation(int rows,
                     int columns,
                     int start,
                     int end,
                     float time,
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
    mDirection(end > start ? 1 : -1)
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
    if (mCurrentFrame == mEnd)
    {
        return;
    }

    mCurrentTime += delta;
    if (mCurrentTime > mTimePerFrame)
    {
        mCurrentTime = 0.0f;
        mCurrentFrame += mDirection;
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
