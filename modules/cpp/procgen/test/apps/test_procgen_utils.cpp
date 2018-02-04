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
#include <nyra/procgen/Utils.h>

namespace
{
class Noise
{
public:
    double operator()(double x, double y) const
    {
        const double idx = (static_cast<size_t>(
                y * nyra::procgen::DEFAULT_SIZE.x + x) % 11);
        return idx;
    }
};
}

namespace nyra
{
namespace procgen
{
TEST(Utils, MinMax)
{
    Noise noise;
    const auto minMax = getMinMax(noise);
    EXPECT_EQ(0, minMax.first);
    EXPECT_EQ(10, minMax.second);
}

TEST(Utils, Percent)
{
    Noise noise;

    for (double ii = 0.0; ii <= 1.0; ii += 0.1)
    {
        EXPECT_NEAR(ii * 10, getValueAtPercent(noise, ii), 0.001);
    }
}
}
}

NYRA_TEST()
