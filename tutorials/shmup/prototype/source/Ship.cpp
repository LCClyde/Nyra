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
#include <Ship.h>

//===========================================================================//
Ship::Ship(const std::string& filename,
           int rows,
           int columns,
           float x,
           float y,
           float rotation) :
    Actor(filename, rows, columns, x, y, rotation),
    mShootDelay(0.0f),
    mPrevTime(0.0f),
    mState(OFF_SCREEN)
{
}

//===========================================================================//
void Ship::update(float delta)
{
    switch (mState)
    {
    case OFF_SCREEN:
        Actor::updateOnScreen();

        if (isOnScreen())
        {
            setState(ACTIVE);
        }
        break;
    case ACTIVE:
        if (!isOnScreen())
        {
            setState(DEAD);
        }

        updateImpl(delta);

        mPrevTime += delta;
        if (mPrevTime >= mShootDelay)
        {
            mShootDelay = fire();
            mPrevTime = 0.0f;
        }

        Actor::update(delta);
        break;

    case DEAD:
        break;
    }
}

//===========================================================================//
void Ship::hit()
{
    hide();
}
