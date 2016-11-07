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
#ifndef __NYRA_ANIM_INTERPOLATED_ANIMATION_H__
#define __NYRA_ANIM_INTERPOLATED_ANIMATION_H__

#include <nyra/math/Interpolate.h>
#include <nyra/anim/Animation.h>

namespace nyra
{
namespace anim
{
/*
 *  \class InterpolateBase
 *  \brief Base class for interpolating an animation between two values.
 *
 *  \tparam TypeT The type to interpolate.
 */
template <typename TypeT>
class InterpolateBase : public Animation
{
public:
    /*
     *  \func initialize
     *  \brief Sets up the interpolation information.
     *
     *  \param start The beginning value
     *  \param end The ending value
     *  \param duration The animation duration in seconds.
     *  \param playType How to play the animation
     */
    void initialize(const TypeT& start,
                    const TypeT& end,
                    double duration,
                    Animation::PlayType playType)
    {
        mStart = start;
        mEnd = end;
        Animation::initialize(duration, playType);
    }

    /*
     *  \func interpolate
     *  \brief Gets the interpolate value for the animation.
     *
     *  \param deltaTime The time that has passed since the last animation
     *         update.
     */
    TypeT interpolate(double deltaTime)
    {
        deltaTime = normalizeTime(deltaTime);
        return math::linearInterpolate(mStart, mEnd, deltaTime);
    }

private:
    TypeT mStart;
    TypeT mEnd;
};

/*
 *  \class Interpolate
 *  \brief Creates a simple interpolated animation. This will update a value
 *         based on a time value.
 *
 *  \tparam TypeT The type to interpolate.
 */
template <typename TypeT>
class Interpolate : public InterpolateBase<TypeT>
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up the interpolation information.
     *
     *  \param start The beginning value
     *  \param end The ending value
     *  \param duration The animation duration in seconds.
     *  \param playType How to play the animation
     *  \param value The value to update under the hood.
     */
    Interpolate(const TypeT& start,
                const TypeT& end,
                double duration,
                Animation::PlayType playType,
                TypeT& value)
    {
        initialize(start, end, duration, playType, value);
    }

    /*
     *  \func initialize
     *  \brief Sets up the interpolation information.
     *
     *  \param start The beginning value
     *  \param end The ending value
     *  \param duration The animation duration in seconds.
     *  \param playType How to play the animation
     *  \param value The value to update under the hood.
     */
    void initialize(const TypeT& start,
                    const TypeT& end,
                    double duration,
                    Animation::PlayType playType,
                    TypeT& value)
    {
        InterpolateBase<TypeT>::initialize(start, end, duration, playType);
        mValue = &value;
    }

    /*
     *  \func update
     *  \brief Updates an animation.
     *
     *  \param deltaTime The time that has passed since the last animation
     *         update.
     */
    void update(double deltaTime) override
    {
        (*mValue) = InterpolateBase<TypeT>::interpolate(deltaTime);
    }

private:
    TypeT* mValue;
};
}
}

#endif
