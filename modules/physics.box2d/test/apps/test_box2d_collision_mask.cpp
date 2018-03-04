/*
 * Copyright (c) 2018 Clyde Stanfield
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

namespace nyra
{
namespace physics
{
namespace box2d
{
TEST(CollisionMask, Collisions)
{
    World world(64.0, 0.0, 60.0);

    // Create the collision wall
    math::Transform2D wallTransform;
    std::unique_ptr<Body2D> wall = world.createBody(
            STATIC, 1, wallTransform, 1.0, 0.3);
    wall->addBox(math::Vector2F(10.0f, 100.0f),
                 math::Vector2F());

    // Create ball 1
    math::Transform2D ball1Transform;
    ball1Transform.setPosition(math::Vector2F(-20.0f, -20.0f));
    std::unique_ptr<Body2D> ball1 = world.createBody(
            DYNAMIC, 1, ball1Transform, 1.0, 0.3);
    ball1->addCircle(1.0f, math::Vector2F());
    ball1->setVelocity(math::Vector2F(10.0f, 0.0f));

    // Create ball 2
    math::Transform2D ball2Transform;
    ball2Transform.setPosition(math::Vector2F(-20.0f, 20.0f));
    std::unique_ptr<Body2D> ball2 = world.createBody(
            DYNAMIC, 2, ball2Transform, 1.0, 0.3);
    ball2->addCircle(1.0f, math::Vector2F());
    ball2->setVelocity(math::Vector2F(10.0f, 0.0f));

    for (size_t ii = 0; ii < 60; ++ii)
    {
        world.update(1.0 / 10.0);
        ball1->update();
        ball1Transform.resetDirty();

        ball2->update();
        ball2Transform.resetDirty();
    }

    // Ball one should collide and thus cannot pass
    EXPECT_LE(ball1Transform.getPosition().x, -6.0);

    // Ball two did not collide
    EXPECT_GE(ball2Transform.getPosition().x, 6.0);
}
}
}
}

NYRA_TEST()
