/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
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
#include <nyra/math/Vector.h>
#include <nyra/test/Test.h>

namespace
{
nyra::math::Vector<float, 2> get2(float x, float y)
{
    nyra::math::Vector<float, 2> ret;
    ret[0] = x;
    ret[1] = y;
    return ret;
}
}

namespace nyra
{
namespace math
{
TEST(Vector2, Equality)
{
    // Equality
    const Vector<float, 2> vec = get2(4.25f, 9.75f);
    EXPECT_TRUE(vec == vec);
    EXPECT_TRUE(vec == get2(4.25f, 9.75f));
    EXPECT_FALSE(vec == get2(0.0f, 0.0f));
    EXPECT_FALSE(vec == get2(4.25f, 0.0f));
    EXPECT_FALSE(vec == get2(0.0f, 9.75f));

    // Inequality
    EXPECT_FALSE(vec != vec);
    EXPECT_FALSE(vec != get2(4.25f, 9.75f));
    EXPECT_TRUE(vec != get2(0.0f, 0.0f));
    EXPECT_TRUE(vec != get2(4.25f, 0.0f));
    EXPECT_TRUE(vec != get2(0.0f, 9.75f));
}

TEST(Vector2, Assignment)
{
    Vector<float, 2> vec = get2(10.0f, 20.0f);
    const Vector<float, 2> assigned = vec;
    EXPECT_EQ(assigned, vec);
    vec += vec;
    EXPECT_EQ(vec, get2(20.0f, 40.0f));
    vec -= assigned;
    EXPECT_EQ(vec, get2(10.0f, 20.0f));
    vec *= 2.0;
    EXPECT_EQ(vec, get2(20.0f, 40.0f));
    vec /= 2.0;
    EXPECT_EQ(vec, get2(10.0f, 20.0f));
}

TEST(Vector2, Operators)
{
    const Vector<float, 2> vec = get2(10.0f, 20.0f);
    EXPECT_EQ(vec + vec, get2(20.0f, 40.0f));
    EXPECT_EQ(vec - vec, get2(0.0f, 0.0f));
    EXPECT_EQ(vec * 2.0, get2(20.0f, 40.0f));
    EXPECT_EQ(vec / 2.0, get2(5.0f, 10.0f));
}

TEST(Vector2, Calculations)
{
    Vector<float, 2> vec = get2(10.0f, 20.0f);
    EXPECT_EQ(vec.sum(), 30.0f);
    EXPECT_EQ(vec.product(), 200.0f);
    EXPECT_EQ(vec.sumSquares(), 500.0f);
    EXPECT_NEAR(vec.length(), 22.360679, 0.000001);
    EXPECT_DOUBLE_EQ(vec.lengthSquared(), 500.0f);
    EXPECT_DOUBLE_EQ(vec.dot(get2(20.0f, 10.0f)), 400.0f);
    vec.normalize();
    EXPECT_FLOAT_EQ(vec.length(), 1.0f);
}

TEST(Vector2, Archive)
{
    Vector<float, 2> input = get2(1.234f, 5.678);
    Vector<float, 2> output =
            nyra::test::archive<Vector<float, 2> >(input);
    EXPECT_EQ(input, output);
}

TEST(Vector2, Stdout)
{
    Vector<float, 2> input = get2(1.234f, 5.678);
    std::string out = nyra::test::stdout(input);
    EXPECT_EQ(out, "vec[0]=1.234 vec[1]=5.678");
}
}
}

NYRA_TEST()
