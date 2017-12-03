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
#ifndef __NYRA_PHSYICS_BODY_H__
#define __NYRA_PHSYICS_BODY_H__

#include <nyra/math/Transform.h>

namespace nyra
{
namespace physics
{
/*
 *  \enum Type
 *  \brief Describes the physics type of a body
 *      DYNAMIC - Moves with physics
 *      STATIC - Collision only (does not move)
 */
enum Type
{
    DYNAMIC,
    STATIC,
    CHARACTER
};

/*
 *  \class Body
 *  \brief A physics body object
 *
 *  \tparam TransformT The transform type (2D or 3D)
 */
template <typename TransformT>
class Body
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a body object
     *
     *  \param type The physics type
     *  \param transform The transform the body is in charge of
     */
    Body(Type type,
         TransformT& transform) :
        mType(type),
        mTransform(transform),
        mUserData(nullptr)
    {
    }

    /*
     *  \func Destructor
     *  \brief Required for inheritance
     */
    virtual ~Body() = default;

    /*
     *  \func addCircle
     *  \brief Adds circle collision
     *
     *  \param radius The radius of the circle
     *         (pixels in 2D, meters is 3D)
     *  \param offset The offset of the circle
     *         (pixels in 2D, meters is 3D)
     */
    virtual void addCircle(double radius,
                           const typename TransformT::Position& offset) = 0;

    /*
     *  \func addBox
     *  \brief Adds box collision
     *
     *  \param size The size of the box
     *         (pixels in 2D, meters is 3D)
     *  \param offset The offset of the circle
     *         (pixels in 2D, meters is 3D)
     */
    virtual void addBox(const typename TransformT::Size& size,
                        const typename TransformT::Position& offset) = 0;

    /*
     *  \func update
     *  \brief Updates the body.
     */
    virtual void update() = 0;

    /*
     *  \func getVelocity
     *  \brief Gets the current linear velocity of the body
     *
     *  \return The velocity vector
     */
    virtual typename TransformT::Position getVelocity() const = 0;

    /*
     *  \func setVelocity
     *  \brief Sets the linear velocity
     *
     *  \param velocity The desired velocity
     */
    virtual void setVelocity(
            const typename TransformT::Position& velocity) = 0;

    /*
     *  \func getUserData
     *  \brief Returns some user defined pointer.
     *
     *  \return The data
     */
    void* getUserData() const
    {
        return mUserData;
    }

    /*
     *  \func setUserData
     *  \brief Sets some user defined pointer that can be obtained later.
     *
     *  \param data The data to store.
     */
    void setUserData(void* data)
    {
        mUserData = data;
    }

protected:
    Type mType;
    TransformT& mTransform;
    void* mUserData;
};

typedef Body<math::Transform2D> Body2D;
typedef Body<math::Transform3D> Body3D;
}
}

#endif
