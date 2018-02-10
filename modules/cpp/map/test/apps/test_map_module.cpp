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
#include <nyra/map/Module.h>
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
    double operator()(double x, double y) const
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
    double operator()(double x, double y) const
    {
        minVal = std::min(minVal, y);
        maxVal = std::max(minVal, y);
        return y;
    }
};

//===========================================================================//
template<typename T>
class TestModule : public nyra::map::Module<T>
{
public:
    TestModule() :
        nyra::map::Module<T>(new T())
    {
    }

private:
    nyra::img::Color calcPixel(double value)
    {
        return nyra::img::Color(value, value, value, 255);
    }
};
}

namespace nyra
{
namespace map
{
//===========================================================================//
TEST(Module, ImageResizing)
{
    math::Vector2U size = DEFAULT_SIZE / 100;

    TestModule<XNoise> xMod;
    resetMinMax();
    xMod.getImage(size);
    EXPECT_EQ(0, minVal);
    EXPECT_EQ(DEFAULT_SIZE.x - 1, maxVal);

    TestModule<YNoise> yMod;
    resetMinMax();
    yMod.getImage(size);
    EXPECT_EQ(0, minVal);
    EXPECT_EQ(DEFAULT_SIZE.y - 1, maxVal);
}
}
}

NYRA_TEST()
