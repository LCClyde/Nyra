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
#ifndef __NYRA_CORE_FPS_H__
#define __NYRA_CORE_FPS_H__

#include <stddef.h>

namespace nyra
{
namespace core
{
/*
 *  \class FPS
 *  \brief Used to track frames per second and time between frames.
 */
class FPS
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the FPS object. In general the FPS object will need
     *         two cycles before it gives meaningful information.
     */
    FPS();

    /*
     *  \func Functor
     *  \brief Gets the delta time and updates the FPS.
     *
     *  \return The time seconds since the last call.
     */
    double operator()();

    /*
     *  \func getFPS
     *  \brief Gets the number of frames in the last second. The first second
     *         will read 0 FPS.
     *
     *  \return The number of frames in the last seconds.
     */
    size_t getFPS() const
    {
        return mFPS;
    }

private:
    size_t mPrevTime;
    size_t mFPS;
    double mElapsed;
    size_t mFrameCount;

};
}
}

#endif
