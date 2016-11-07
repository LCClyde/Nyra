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
#include <nyra/anim/Animation.h>
#include <algorithm>

namespace nyra
{
namespace anim
{
//===========================================================================//
void Animation::initialize(double duration,
                           PlayType playType)
{
    mPlayType = playType;
    mDuration = duration;
    mElapsed = 0.0;
    mPingPong = PING;
}

//===========================================================================//
double Animation::normalizeTime(double deltaTime)
{
    switch (mPlayType)
    {
    case ONCE:
        mElapsed += deltaTime;
        mElapsed = std::min(mElapsed, mDuration);
        break;
    case LOOP:
        mElapsed += deltaTime;
        while (mElapsed > mDuration)
        {
            mElapsed -= mDuration;
        }
        break;
    case PING_PONG:
        while (deltaTime)
        {
            if (mPingPong == PING)
            {
                updatePing(deltaTime);
            }
            else
            {
                updatePong(deltaTime);
            }
        }
        break;
    }

    return mElapsed / mDuration;
}

//===========================================================================//
void Animation::updatePing(double& deltaTime)
{
    mElapsed += deltaTime;
    if (mElapsed > mDuration)
    {
        mPingPong = PONG;
        deltaTime = mElapsed - mDuration;
        mElapsed = mDuration;
    }
    else
    {
        deltaTime = 0.0;
    }
}

//===========================================================================//
void Animation::updatePong(double& deltaTime)
{
    mElapsed -= deltaTime;
    if (mElapsed < 0.0)
    {
        mPingPong = PING;
        deltaTime = -mElapsed;
        mElapsed = 0.0;
    }
    else
    {
        deltaTime = 0.0;
    }
}
}
}
