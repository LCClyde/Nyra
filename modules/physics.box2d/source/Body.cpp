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
#include <nyra/physics/box2d/Body.h>
#include <nyra/math/Transform.h>

namespace nyra
{
namespace physics
{
namespace box2d
{
//===========================================================================//
Body::Body(Type type,
           uint64_t mask,
           math::Transform2D& transform,
           World& world,
           double density,
           double friction) :
    Body2D(type, mask, transform),
    mWorld(world),
    mDensity(density),
    mFriction(friction),
    mTrigger(false)
{
    b2BodyDef bodyDef;

    switch (type)
    {
    case DYNAMIC:
        bodyDef.type = b2_dynamicBody;
        break;
    case CHARACTER:
        bodyDef.type = b2_dynamicBody;
        bodyDef.fixedRotation = true;
        break;
    case STATIC:
        bodyDef.type = b2_staticBody;
        break;
    }

    bodyDef.position.Set(0.0f, 0.0f);
    mBody = mWorld.getWorld().CreateBody(&bodyDef);
}

//===========================================================================//
Body::~Body()
{
    mWorld.getWorld().DestroyBody(mBody);
}

//===========================================================================//
void Body::addCircle(double radius,
                     const math::Vector2F& offset)
{
    b2CircleShape shape;
    shape.m_radius = radius * mWorld.PIXELS_TO_METERS;
    shape.m_p.x = offset.x * mWorld.PIXELS_TO_METERS;
    shape.m_p.y = offset.y * mWorld.PIXELS_TO_METERS;
    addShape(shape);
}

//===========================================================================//
void Body::addBox(const math::Vector2F& size,
                  const math::Vector2F& offset)
{
    b2PolygonShape shape;
    b2Vec2 center(offset.x * mWorld.PIXELS_TO_METERS,
                  offset.y * mWorld.PIXELS_TO_METERS);
    shape.SetAsBox(size.x / 2.0 * mWorld.PIXELS_TO_METERS,
                   size.y / 2.0 * mWorld.PIXELS_TO_METERS,
                   center, 0.0f);
    addShape(shape);
}

//===========================================================================//
void Body::addShape(const b2Shape& shape)
{
    b2FixtureDef fixture;
    fixture.filter.maskBits = mMask;
    fixture.userData = this;
    fixture.shape = &shape;
    fixture.density = mDensity;
    fixture.friction = mFriction;
    fixture.isSensor = mTrigger;

    mBody->CreateFixture(&fixture);
}

//===========================================================================//
void Body::update()
{
    if (mTransform.isDirty())
    {
        mBody->SetTransform(b2Vec2(
                mTransform.getPosition().x * mWorld.PIXELS_TO_METERS,
                mTransform.getPosition().y * mWorld.PIXELS_TO_METERS),
                        math::degreesToRadians(mTransform.getRotation()));
    }
    else
    {
        const auto& pos = mBody->GetPosition();
        mTransform.setPosition(math::Vector2F(
                pos.x * mWorld.METERS_TO_PIXELS,
                pos.y * mWorld.METERS_TO_PIXELS));
        const double rotation = mBody->GetAngle();
        mTransform.setRotation(math::radiansToDegrees(rotation));
    }
}

//===========================================================================//
math::Vector2F Body::getVelocity() const
{
    const auto& vel = mBody->GetLinearVelocity();
    return math::Vector2F(vel.x * mWorld.METERS_TO_PIXELS,
                          vel.y * mWorld.METERS_TO_PIXELS);
}

//===========================================================================//
void Body::setVelocity(const math::Vector2F& velocity)
{
    mBody->SetLinearVelocity(b2Vec2(
            velocity.x * mWorld.PIXELS_TO_METERS,
            velocity.y * mWorld.PIXELS_TO_METERS));
}
}
}
}
