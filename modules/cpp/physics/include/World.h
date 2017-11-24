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
#ifndef __NYRA_PHYSICS_WORLD_H__
#define __NYRA_PHYSICS_WORLD_H__

#include <memory>
#include <iostream>
#include <nyra/physics/Body.h>
#include <nyra/physics/Trigger.h>
#include <nyra/math/Transform.h>

namespace nyra
{
namespace physics
{
/*
 *  \class World
 *  \brief Object that holds onto the global physics properties
 *
 *  \tparam TransformT The transform type (2D or 3D)
 */
template <typename TransformT>
class World
{
public:
    /*
     *  \func Constructor
     *  \brief Creates the world
     *
     *  \param pixelsToMeters Conversion from pixels to meters for
     *         2D world.
     *  \param fps The target frames per second
     */
    World(double pixelsToMeters,
          double fps) :
        PIXELS_TO_METERS(1.0 / pixelsToMeters),
        METERS_TO_PIXELS(pixelsToMeters),
        mElapsedTime(0.0),
        mTimeBeforeUpdate(1.0 / fps)
    {
    }

    /*
     *  \func Destructor
     *  \brief Necessary for inheritance
     */
    virtual ~World() = default;

    /*
     *  \func update
     *  \brief Updates the world. This will only when the delta time has
     *         exceeded the FPS.
     *
     *  \param delta The delta time
     *  \return True if an update actually occurred.
     */
    bool update(double delta)
    {
        mElapsedTime += delta;

        bool ticked = false;
        while (mElapsedTime >= mTimeBeforeUpdate)
        {
            updateImpl(mTimeBeforeUpdate);
            mElapsedTime -= mTimeBeforeUpdate;
            ticked = true;
        }

        return ticked;
    }

    /*
     *  \func createBody
     *  \brief Creates a physics body
     *
     *  \param type The physics type
     *  \param transform The transform to update
     *  \param density The objects density
     *  \param friction Friction to apply to movement
     *  \return The body
     */
    virtual std::unique_ptr<Body<TransformT>> createBody(
            Type type,
            TransformT& transform,
            double density,
            double friction) = 0;

    /*
     *  \func createTrigger
     *  \brief Creates a trigger
     *
     *  \param type The physics type
     *  \param transform The transform to update
     *  \return The trigger
     */
    virtual std::unique_ptr<Trigger<TransformT>> createTrigger(
            Type type,
            TransformT& transform) = 0;

    /*
     *  \var PIXELS_TO_METERS
     *  \brief Converts pixels to meters
     */
    const double PIXELS_TO_METERS;

    /*
     *  \var METERS_TO_PIXELS
     *  \brief Converts meters to pixels
     */
    const double METERS_TO_PIXELS;

protected:
    virtual void updateImpl(double delta) = 0;

    double mElapsedTime;
    const double mTimeBeforeUpdate;
};

typedef World<math::Transform2D> World2D;
typedef World<math::Transform3D> World3D;
}
}

#endif
