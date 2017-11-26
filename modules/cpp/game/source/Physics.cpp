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
#include <nyra/game/Physics.h>
#include <nyra/game/Types.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace game
{
//===========================================================================//
Physics::Physics(math::Transform2D& transform) :
    mTransform(transform)
{
}

//===========================================================================//
void Physics::addBody(physics::Body<math::Transform2D>* body)
{
    mBody.reset(body);
}

//===========================================================================//
void Physics::addCircleCollision(double radius,
                                 const math::Vector2F& offset)
{
    mBody->addCircle(radius, offset);
    mCollision.push_back(std::unique_ptr<graphics::Renderable2D>(
            new SpriteT(
            core::path::join(core::DATA_PATH,
                             "textures/collision_circle.png"))));
    mCollision.back()->setPosition(offset);
    mCollision.back()->setScale(math::Vector2F(radius / 64.0,
                                               radius / 64.0));
}

//===========================================================================//
void Physics::render(graphics::RenderTarget& target)
{
    for (size_t ii = 0; ii < mCollision.size(); ++ii)
    {
        mCollision[ii]->updateTransform(mTransform);
        mCollision[ii]->render(target);
    }
}

//===========================================================================//
void Physics::update()
{
    if (mBody.get())
    {
        mBody->update();
        mTransform.resetDirty();
    }
}
}
}
