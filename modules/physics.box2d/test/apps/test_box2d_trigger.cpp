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
#include <nyra/test/Test.h>
#include <nyra/physics/box2d/World.h>

namespace
{
nyra::physics::Body2D* enterBody = nullptr;
nyra::physics::Body2D* exitBody = nullptr;

void testOnEnter(nyra::physics::Body2D& body)
{
    if (enterBody)
    {
        throw std::runtime_error("Enter called twice");
    }

    enterBody = &body;
}

void testOnExit(nyra::physics::Body2D& body)
{
    if (exitBody)
    {
        throw std::runtime_error("Exit called twice");
    }

    exitBody = &body;
}
}

namespace nyra
{
namespace physics
{
namespace box2d
{
TEST(Trigger, Interact)
{
    const double radius = 1.0;
    const double boxSize = 10.0;

    World world(64.0, 0.0, 60.0);
    math::Transform2D transform;
    transform.setPosition(math::Vector2F(-100.0f, 0.0f));
    std::unique_ptr<Body2D> body = world.createBody(
            DYNAMIC, 1, transform, 1.0, 0.3);
    body->addCircle(radius, math::Vector2F());
    body->setVelocity(math::Vector2F(100.0f, 0.0f));
    body->update();

    math::Transform2D triggerTransform;
    std::unique_ptr<Trigger2D> trigger = world.createTrigger(
            STATIC, 1, triggerTransform);
    triggerTransform.setPosition(math::Vector2F());
    trigger->addBox(math::Vector2F(boxSize, boxSize), math::Vector2F());
    trigger->onEnter = testOnEnter;
    trigger->onExit = testOnExit;

    // It takes one extra frame to actually see the exit message.
    bool hitExitOnce = false;

    for (size_t ii = 0; ii < 60; ++ii)
    {
        world.update(1.0 / 30.0);
        body->update();
        const double xPosition = transform.getPosition().x;

        if (xPosition < -(radius + boxSize / 2.0))
        {
            EXPECT_EQ(reinterpret_cast<size_t>(nullptr),
                      reinterpret_cast<size_t>(enterBody));
            EXPECT_EQ(reinterpret_cast<size_t>(nullptr),
                      reinterpret_cast<size_t>(exitBody));
        }
        else if (xPosition > radius + boxSize / 2.0)
        {
            EXPECT_EQ(reinterpret_cast<size_t>(body.get()),
                      reinterpret_cast<size_t>(enterBody));
            if (hitExitOnce)
            {
                EXPECT_EQ(reinterpret_cast<size_t>(body.get()),
                          reinterpret_cast<size_t>(exitBody));
            }
            else
            {
                EXPECT_EQ(reinterpret_cast<size_t>(nullptr),
                          reinterpret_cast<size_t>(exitBody));
            }
            hitExitOnce = true;
        }
        else
        {
            EXPECT_EQ(reinterpret_cast<size_t>(body.get()),
                      reinterpret_cast<size_t>(enterBody));
            EXPECT_EQ(reinterpret_cast<size_t>(nullptr),
                      reinterpret_cast<size_t>(exitBody));
        }

        transform.resetDirty();
    }

}
}
}
}

NYRA_TEST()
