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
#include <nyra/math/Matrix3x3.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace math
{
TEST(Matrix3x3, Transform)
{
    Matrix3x3 position;
    position.transform(Vector2F(2.0f, 3.0f),
                       Vector2F(1.0f, 1.0f),
                       0.0,
                       Vector2F());
    Matrix3x3 exPosition(1.0f, 0.0f, 2.0f,
                         0.0f, 1.0f, 3.0f,
                         0.0f, 0.0f, 1.0f);
    EXPECT_EQ(exPosition, position);

    Matrix3x3 pivot;
    pivot.transform(Vector2F(),
                    Vector2F(1.0f, 1.0f),
                    0.0,
                    Vector2F(2.0f, 3.0f));
    EXPECT_EQ(exPosition, pivot);

    Matrix3x3 rotation;
    rotation.transform(Vector2F(),
                       Vector2F(1.0f, 1.0f),
                       180.0,
                       Vector2F());
    Matrix3x3 exRotation(-1.0f, 0.0f, 0.0f,
                         0.0f, -1.0f, 0.0f,
                         0.0f,  0.0f, 1.0f);
    EXPECT_EQ(exRotation, rotation);

    Matrix3x3 scale;
    scale.transform(Vector2F(),
                    Vector2F(2.0f, 3.0f),
                    0.0,
                    Vector2F());
    Matrix3x3 exScale(2.0f, 0.0f, 0.0f,
                      0.0f, 3.0f, 0.0f,
                      0.0f, 0.0f, 1.0f);
    EXPECT_EQ(exScale, scale);

    // NOTE: Matrix equality checks if the values are close. Because this
    // uses trig the rotation values do not line up to 0.0.
    Matrix3x3 all;
    all.transform(Vector2F(5.0f, 6.0f),
                  Vector2F(2.0f, 3.0f),
                  180.0,
                  Vector2F(10.0f, 20.0f));
    Matrix3x3 exAll(-2.0f, 0.0f,  -15.0f,
                    0.0f,  -3.0f, -54.0f,
                    0.0f,  0.0f,  1.0f);
    EXPECT_EQ(exAll, all);
}

TEST(Matrix3x3, Archive)
{
    Matrix3x3 input(1.0f, 2.0f, 3.0f,
                    4.0f, 5.0f, 6.0f,
                    7.0f, 8.0f, 9.0f);
    EXPECT_EQ(input, test::archive(input));
}

TEST(Matrix3x3, Stdout)
{
    Matrix3x3 input(1.0f, 2.0f, 3.0f,
                    4.0f, 5.0f, 6.0f,
                    7.0f, 8.0f, 9.0f);
    EXPECT_EQ(test::stdout(input), "[[1, 2, 3],\n"
                                   " [4, 5, 6],\n"
                                   " [7, 8, 9]]");
}
}
}

NYRA_TEST()
