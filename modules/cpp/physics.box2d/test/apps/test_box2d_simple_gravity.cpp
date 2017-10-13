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

namespace nyra
{
namespace physics
{
namespace box2d
{
TEST(Gravity, Fall)
{
    World world(64.0, 10.0, 60.0);
    math::Transform2D transform;
    std::unique_ptr<Body2D> body = world.createBody(
            DYNAMIC, transform, 1.0, 0.3);

    for (size_t ii = 0; ii < 60; ++ii)
    {
        world.update(1.0 / 60.0);
        const float prevY = transform.getPosition().y;
        body->update();

        // We should always be falling
        EXPECT_LT(transform.getPosition().y, prevY);
        transform.updateTransform(math::Transform2D());
    }
}

TEST(Gravity, Ground)
{
    World world(64.0, 10.0, 60.0);
    math::Transform2D transform;
    transform.setPosition(math::Vector2F(0.0f, 20.0f));
    std::unique_ptr<Body2D> body = world.createBody(
            DYNAMIC, transform, 1.0, 0.3);
    body->addCircle(5.0f, math::Vector2F());

    math::Transform2D staticTransform;
    std::unique_ptr<Body2D> staticBody = world.createBody(
            STATIC, staticTransform, 1.0, 0.3);
    staticBody->addBox(math::Vector2F(1000.0f, 10.0f),
                       math::Vector2F());

    // Fall until we hit the box
    float prevY = 0.0f;
    for (size_t ii = 0; ii < 100; ++ii)
    {
        prevY = transform.getPosition().y;
        world.update(1.0 / 60.0);
        body->update();
        transform.updateTransform(math::Transform2D());
    }

    for (size_t ii = 0; ii < 10; ++ii)
    {
        world.update(1.0 / 60.0);
        prevY = transform.getPosition().y;
        body->update();
        transform.updateTransform(math::Transform2D());

        // We should have hit collision. Make sure we are within
        // 1 pixel to the top of the box.
        EXPECT_NEAR(prevY, transform.getPosition().y, 1.0);
    }
}
}
}
}

NYRA_TEST()
