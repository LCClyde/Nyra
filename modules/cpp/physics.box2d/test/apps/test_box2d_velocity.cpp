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
TEST(Velocity, SetGet)
{
    World world(64.0, 0.0, 60.0);
    math::Transform2D transform;
    std::unique_ptr<Body2D> body = world.createBody(
            DYNAMIC, transform, 1.0, 0.3);
    body->setVelocity(math::Vector2F(5.0f, 3.0f));
    transform.resetDirty();

    for (size_t ii = 0; ii < 60; ++ii)
    {
        world.update(1.0 / 60.0);
        const math::Vector2F prev = transform.getPosition();
        body->update();
        transform.resetDirty();
        EXPECT_LT(prev.x, transform.getPosition().x);
        EXPECT_LT(prev.y, transform.getPosition().y);
    }

    EXPECT_NEAR(5.0f, transform.getPosition().x, 0.01);
    EXPECT_NEAR(3.0f, transform.getPosition().y, 0.01);
}
}
}
}

NYRA_TEST()
