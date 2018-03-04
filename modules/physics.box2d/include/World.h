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
#ifndef __NYRA_PHYSICS_BOX_2D_WORLD_H__
#define __NYRA_PHYSICS_BOX_2D_WORLD_H__

#include <Box2D/Box2D.h>
#include <nyra/physics/World.h>
#include <nyra/math/Transform.h>

namespace nyra
{
namespace physics
{
namespace box2d
{

/*
 *  \class World
 *  \brief Object that holds onto the global physics properties
 */
class World : public World2D
{
public:
    /*
     *  \func Constructor
     *  \brief Creates the world
     *
     *  \param pixelsToMeters Conversion from pixels to meters for
     *         2D world.
     *  \param gravity The downward gravity acceleration in pixels
     *  \param fps The target frames per second
     */
    World(double pixelsPerMeter,
          double gravity,
          double fps);

    /*
     *  \func createBody
     *  \brief Creates a physics body
     *
     *  \param type The physics type
     *  \param mask The collision mask
     *  \param transform The transform to update
     *  \param density The objects density
     *  \param friction Friction to apply to movement
     *  \return The body
     */
    std::unique_ptr<Body2D>
    createBody(Type type,
               uint64_t mask,
               math::Transform2D& transform,
               double density,
               double friction) override;

    /*
     *  \func createTrigger
     *  \brief Creates a trigger
     *
     *  \param type The physics type
     *  \param mask The collision mask
     *  \param transform The transform to update
     *  \return The trigger
     */
    std::unique_ptr<Trigger2D>
    createTrigger(Type type,
                  uint64_t mask,
                  math::Transform2D& transform) override;

    /*
     *  \func getWorld
     *  \brief Gets the Box2D world object
     *
     *  \return The Box2D world
     */
    b2World& getWorld()
    {
        return mWorld;
    }

private:
    void updateImpl(double delta) override;

    b2World mWorld;
    const int32_t mVelocityIterations;
    const int32_t mPositionIterations;
};
}
}
}

#endif
