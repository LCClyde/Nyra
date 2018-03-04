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
#ifndef __NYRA_PHYSICS_BOX_2D_TRIGGER_H__
#define __NYRA_PHYSICS_BOX_2D_TRIGGER_H__

#include <nyra/physics/Trigger.h>
#include <nyra/physics/box2d/Body.h>

namespace nyra
{
namespace physics
{
namespace box2d
{
/*
 *  \class Trigger
 *  \brief Creates a collision volume that sends events on enter and exit
 */
class Trigger : public physics::Trigger2D, public box2d::Body
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a trigger object
     *
     *  \param type The physics type
     *  \param mask The collision mask
     *  \param transform The transform the body is in charge of
     *  \param world The box2d world
     */
    Trigger(Type type,
            uint64_t mask,
            math::Transform2D& transform,
            World& world);

    /*
     *  \func onEnterMessage
     *  \brief Call when a body enters the trigger.
     *
     *  \param body The body that entered
     */
    void onEnterMessage(box2d::Body& body);

    /*
     *  \func onExitMessage
     *  \brief Call when a body exits the trigger.
     *
     *  \param body The body that exited
     */
    void onExitMessage(box2d::Body& body);

private:
    bool mTriggered;
};
}
}
}

#endif
