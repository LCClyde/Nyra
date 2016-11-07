/*
 * Copyright (c) 2016 Clyde Stanfield
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
#include <nyra/anim/Animation.h>
#include <nyra/test/Test.h>

namespace
{
class MockAnimation : public nyra::anim::Animation
{
public:
    MockAnimation(nyra::anim::Animation::PlayType playType) :
        normTime(0.0)
    {
        initialize(10.0, playType);
    }

    void update(double deltaTime)
    {
        normTime = normalizeTime(deltaTime);
    }

    double normTime;
};
}

namespace nyra
{
namespace anim
{
TEST(Animation, Once)
{
    MockAnimation animation(Animation::ONCE);

    for (size_t ii = 0; ii < 100; ++ii)
    {
        animation.update(0.1);
        EXPECT_NEAR((ii + 1) / 100.0, animation.normTime, 0.0001);
    }

    // If I keep updating I should remain at 1.0
    for (size_t ii = 0; ii < 10; ++ii)
    {
        animation.update(0.1);
        EXPECT_NEAR(1.0, animation.normTime, 0.0001);
    }
}

TEST(Animation, Loop)
{
    MockAnimation animation(Animation::LOOP);

    for (size_t ii = 0; ii < 100; ++ii)
    {
        animation.update(0.1);
        EXPECT_NEAR((ii + 1) / 100.0, animation.normTime, 0.0001);
    }

    // If I keep updating it should loop
    for (size_t ii = 0; ii < 100; ++ii)
    {
        animation.update(0.1);
        EXPECT_NEAR((ii + 1) / 100.0, animation.normTime, 0.0001);
    }
}

TEST(Animation, PingPong)
{
    MockAnimation animation(Animation::PING_PONG);

    // Ping
    for (size_t ii = 0; ii < 100; ++ii)
    {
        animation.update(0.1);
        EXPECT_NEAR((ii + 1) / 100.0, animation.normTime, 0.0001);
    }

    // Pong
    for (size_t ii = 0; ii < 100; ++ii)
    {
        animation.update(0.1);
        EXPECT_NEAR(1.0 - (ii + 1) / 100.0, animation.normTime, 0.0001);
    }

    // Ping
    for (size_t ii = 0; ii < 100; ++ii)
    {
        animation.update(0.1);
        EXPECT_NEAR((ii + 1) / 100.0, animation.normTime, 0.0001);
    }

    // Pong
    for (size_t ii = 0; ii < 100; ++ii)
    {
        animation.update(0.1);
        EXPECT_NEAR(1.0 - (ii + 1) / 100.0, animation.normTime, 0.0001);
    }
}
}
}

NYRA_TEST()
