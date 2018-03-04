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
#include <nyra/math/Conversions.h>
#include <nyra/math/Vector3.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace math
{
TEST(Conversions, Angles)
{
    const double degrees = 180.0;
    const double radians = M_PI;
    EXPECT_EQ(degrees, radiansToDegrees(radians));
    EXPECT_EQ(radians, degreesToRadians(degrees));

    EXPECT_EQ(0.0, normalizeAngle(0.0));
    EXPECT_EQ(180.0, normalizeAngle(180.0));
    EXPECT_EQ(0.0, normalizeAngle(360.0));
    EXPECT_EQ(1.0, normalizeAngle(361.0));
    EXPECT_EQ(40.125, normalizeAngle(400.125));
    EXPECT_EQ(45.0, normalizeAngle(765.0));
    EXPECT_EQ(315.0, normalizeAngle(-45.0));
}

TEST(Conversions, Vector)
{
    Vector3D vec;
    vec[0] = 370.0;
    vec[1] = 380.0;
    vec[2] = 45.0;
    Vector3D expected(10.0, 20.0, 45.0);
    EXPECT_EQ(expected, normalizeAngle(vec));
}
}
}

NYRA_TEST()
