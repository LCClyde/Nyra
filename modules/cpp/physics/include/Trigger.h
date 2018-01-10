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
#ifndef __NYRA_PHYSICS_TRIGGER_H__
#define __NYRA_PHYSICS_TRIGGER_H__

#include <nyra/physics/Body.h>
#include <nyra/core/Event.h>

namespace nyra
{
namespace physics
{
/*
 *  \class Trigger
 *  \brief Creates a collision volume that sends events on enter and exit
 *
 *  \tparam The transform type (2D or 3D)
 */
template <typename TransformT>
class Trigger : public virtual Body<TransformT>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a trigger object
     *
     *  \param type The physics type
     *  \param mask The collision mask
     *  \param transform The transform the body is in charge of
     */
    Trigger(Type type,
            uint64_t mask,
            TransformT& transform) :
        Body<TransformT>(type, mask, transform)
    {
    }

    /*
     *  \func Destructor
     *  \brief Required for inheritance
     */
    virtual ~Trigger() = default;

    /*
     *  \var onEnter
     *  \brief Occurs when an object enters the volume
     *
     *  \param body The body that entered
     */
    core::Event<void(Body<TransformT>& body)> onEnter;

    /*
     *  \var onExit
     *  \brief Occurs when an object exits the volume
     *
     *  \param body The body that exited
     */
    core::Event<void(Body<TransformT>& body)> onExit;
};

typedef Trigger<math::Transform2D> Trigger2D;
typedef Trigger<math::Transform3D> Trigger3D;
}
}

#endif
