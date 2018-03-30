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
#include <nyra/map/Noise.h>
#include <nyra/test/Test.h>

namespace
{
//===========================================================================//
static double minVal = 0.0;
static double maxVal = 0.0;

void resetMinMax()
{
    minVal = std::numeric_limits<double>::max();
    maxVal = -std::numeric_limits<double>::max();
}

//===========================================================================//
class XNoise
{
public:
    double operator()(double x, double y)
    {
        minVal = std::min(minVal, x);
        maxVal = std::max(minVal, x);
        return x;
    }
};

//===========================================================================//
class YNoise
{
public:
    double operator()(double x, double y)
    {
        minVal = std::min(minVal, y);
        maxVal = std::max(minVal, y);
        return y;
    }
};

//===========================================================================//
nyra::img::Color calcPixel(double value)
{
    return nyra::img::Color(value, value, value);
}
}

namespace nyra
{
namespace map
{
//===========================================================================//
TEST(Noise, ImageResizing)
{
    math::Vector2U size = DEFAULT_SIZE / 100;

    Noise<XNoise> xNoise(new XNoise());
    resetMinMax();
    xNoise.getImage(size, PixFunc(calcPixel));
    EXPECT_EQ(0, minVal);
    EXPECT_EQ(DEFAULT_SIZE.x - 1, maxVal);

    Noise<YNoise> yNoise(new YNoise());
    resetMinMax();
    yNoise.getImage(size, PixFunc(calcPixel));
    EXPECT_EQ(0, minVal);
    EXPECT_EQ(DEFAULT_SIZE.y - 1, maxVal);
}

//===========================================================================//
TEST(Noise, MinMax)
{
    Noise<XNoise> xNoise(new XNoise());
    const auto minMax = xNoise.getMinMax();

    EXPECT_EQ(0.0, minMax.first);
    EXPECT_EQ(DEFAULT_SIZE.x - 1, minMax.second);
}

//===========================================================================//
TEST(Noise, PercentAt)
{
    Noise<XNoise> xNoise(new XNoise());
    for (double ii = 0; ii <= 1.0; ii += 0.1)
    {
        const double val = xNoise.getValueAtPercent(ii);

        // Just make sure it is close. It won't be perfect because
        // the percent is measured on a downsampled map.
        EXPECT_NEAR(255.0 * ii, val, 2.0);
    }
}
}
}

NYRA_TEST()
