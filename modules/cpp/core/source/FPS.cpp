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
#include <nyra/core/FPS.h>
#include <nyra/core/Time.h>

namespace nyra
{
namespace core
{
//===========================================================================//
FPS::FPS() :
    mPrevTime(epoch()),
    mFPS(0),
    mElapsed(0.0),
    mFrameCount(0)
{
}

//===========================================================================//
double FPS::operator()()
{
    size_t currentTime = epoch();
    size_t diff = currentTime - mPrevTime;
    double seconds = diff / 1000.0;
    mPrevTime = currentTime;

    mElapsed += seconds;
    ++mFrameCount;

    if (mElapsed >= 1.0)
    {
        mFPS = mFrameCount;
        mFrameCount = 0;
        mElapsed = 0.0;
    }

    return seconds;
}
}
}
