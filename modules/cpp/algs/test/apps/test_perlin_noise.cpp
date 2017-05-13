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
#include <nyra/algs/PerlinNoise.h>
#include <nyra/img/Image.h>
#include <nyra/test/Image.h>

namespace nyra
{
namespace algs
{
TEST(PerlinNoise, Smoothness)
{
    const PerlinNoise noise(FRACTAL_BROWNIAN_MOTION, 0.01, 2.0, 0.5, 3, 0);

    const size_t SIZE = 32;
    const double threshold = 0.1;
    for (size_t x = 1; x < SIZE - 1; ++x)
    {
        for (size_t y = 1; y < SIZE - 1; ++y)
        {
            const double value = noise(x, y);
            for (size_t xx = 0; xx < 2; ++xx)
            {
                for (size_t yy = 0; yy < 2; ++yy)
                {
                    EXPECT_LT(std::abs(noise(xx, yy) - value), threshold);
                }
            }
        }
    }
}

TEST(PerlinNoise, Image)
{
    const PerlinNoise noise(FRACTAL_BROWNIAN_MOTION, 0.02, 2.0, 0.5, 5, 1337);
    img::Image image(noise, math::Vector2U(512, 512), -1.0, 1.0);
    EXPECT_TRUE(test::compareImage(image, "test_perlin.png"));
}
}
}

NYRA_TEST()
