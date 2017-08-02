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
#ifndef __SHMUP_SHIP_H__
#define __SHMUP_SHIP_H__

#include <vector>
#include <memory>
#include <Actor.h>

class Ship : public Actor
{
public:
    enum State
    {
        OFF_SCREEN,
        ACTIVE,
        DEAD
    };

    Ship(const std::string& filename,
         int rows,
         int columns,
         float x,
         float y,
         float rotation);

    virtual ~Ship() = default;

    void update(float delta);

    void setState(State state)
    {
        mState = state;
    }

    virtual void hit();

private:
    virtual void updateImpl(float delta) = 0;

    virtual float fire() = 0;

    float mShootDelay;
    float mPrevTime;
    State mState;
};

#endif
