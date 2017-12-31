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
#include <nyra/physics/box2d/World.h>
#include <nyra/physics/box2d/Body.h>
#include <nyra/physics/box2d/Trigger.h>

namespace
{
class ContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact)
    {
        b2Fixture* fixA = contact->GetFixtureA();
        b2Fixture* fixB = contact->GetFixtureB();

        if (fixA->IsSensor() && !fixB->IsSensor())
        {
            sendEnterMessage(fixA->GetUserData(), fixB->GetUserData());
        }
        else if (fixB->IsSensor() && !fixA->IsSensor())
        {
            sendEnterMessage(fixB->GetUserData(), fixA->GetUserData());
        }
    }

    void EndContact(b2Contact* contact)
    {
        b2Fixture* fixA = contact->GetFixtureA();
        b2Fixture* fixB = contact->GetFixtureB();

        if (fixA->IsSensor() && !fixB->IsSensor())
        {
            sendExitMessage(fixA->GetUserData(), fixB->GetUserData());
        }
        else if (fixB->IsSensor() && !fixA->IsSensor())
        {
            sendExitMessage(fixB->GetUserData(), fixA->GetUserData());
        }
    }

private:
    void sendEnterMessage(void* trigger, void* body)
    {
        nyra::physics::box2d::Trigger* triggerPtr =
                dynamic_cast<nyra::physics::box2d::Trigger*>(
                reinterpret_cast<nyra::physics::box2d::Body*>(
                        trigger));
        nyra::physics::box2d::Body* bodyPtr =
                reinterpret_cast<nyra::physics::box2d::Body*>(
                        body);
        triggerPtr->onEnterMessage(*bodyPtr);
    }

    void sendExitMessage(void* trigger, void* body)
    {
        nyra::physics::box2d::Trigger* triggerPtr =
                dynamic_cast<nyra::physics::box2d::Trigger*>(
                reinterpret_cast<nyra::physics::box2d::Body*>(
                        trigger));
        nyra::physics::box2d::Body* bodyPtr =
                reinterpret_cast<nyra::physics::box2d::Body*>(
                        body);
        triggerPtr->onExitMessage(*bodyPtr);
    }
};
}

namespace nyra
{
namespace physics
{
namespace box2d
{
//===========================================================================//
World::World(double pixelsToMeters,
             double gravity,
             double fps) :
    World2D(pixelsToMeters, fps),
    mWorld(b2Vec2(0.0f, -gravity * PIXELS_TO_METERS)),
    mVelocityIterations(8),
    mPositionIterations(3)
{
    static ContactListener contactListener;
    mWorld.SetContactListener(&contactListener);
    mWorld.SetAllowSleeping(false);
}

//===========================================================================//
void World::updateImpl(double delta)
{
    mWorld.Step(delta,
                mVelocityIterations,
                mPositionIterations);
}

//===========================================================================//
std::unique_ptr<Body2D>
World::createBody(Type type,
                  math::Transform2D& transform,
                  double density,
                  double friction)
{
    std::unique_ptr<Body2D> body(
            new Body(type,
                     transform,
                     *this,
                     density,
                     friction));
    return body;
}

//===========================================================================//
std::unique_ptr<Trigger2D>
World::createTrigger(Type type,
                     math::Transform2D& transform)
{
    std::unique_ptr<Trigger2D> trigger(
            new box2d::Trigger(type, transform, *this));
    return trigger;
}
}
}
}
