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
#include <nyra/math/Matrix4x4.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace math
{
TEST(Matrix4x4, Transform)
{
    Matrix4x4 position;
    position.transform(Vector3F(2.0f, 3.0f, 4.0f),
                       Vector3F(1.0f, 1.0f, 1.0f),
                       Vector3F(),
                       Vector3F());
    Matrix4x4 exPosition(1.0f, 0.0f, 0.0f, 2.0f,
                         0.0f, 1.0f, 0.0f, 3.0f,
                         0.0f, 0.0f, 1.0f, 4.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_EQ(exPosition, position);

    Matrix4x4 pivot;
    pivot.transform(Vector3F(),
                    Vector3F(1.0f, 1.0f, 1.0f),
                    Vector3F(),
                    Vector3F(2.0f, 3.0f, 4.0f));
    EXPECT_EQ(exPosition, pivot);

    Matrix4x4 rotation;
    rotation.transform(Vector3F(),
                       Vector3F(1.0f, 1.0f, 1.0f),
                       Vector3F(180.0f, 90.0f, 45.0f),
                       Vector3F());
    Matrix4x4 exRotation(0.0f, 0.0f, 1.0f, 0.0f,
                         -0.707107f, -0.707107f, 0.0f, 0.0f,
                         0.707107f, -0.707107f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_EQ(exRotation, rotation);

    Matrix4x4 scale;
    scale.transform(Vector3F(),
                    Vector3F(2.0f, 3.0f, 4.0f),
                    Vector3F(),
                    Vector3F());
    Matrix4x4 exScale(2.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 3.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 4.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f);
    EXPECT_EQ(exScale, scale);

    // NOTE: Matrix equality checks if the values are close. Because this
    // uses trig the rotation values do not line up to 0.0.
    Matrix4x4 all;
    all.transform(Vector3F(5.0f, 6.0f, 2.0f),
                  Vector3F(2.0f, 3.0f, 4.0f),
                  Vector3F(180.0f, 90.0f, 45.0f),
                  Vector3F(10.0f, 20.0f, 15.0f));
    Matrix4x4 exAll(0.0f, 0.0f, 4.0f, 65.0f,
                    -1.41421f, -2.12132f, 0.0f, -50.5685f,
                    1.41421f, -2.12132f, 0.0f, -26.2843f,
                    0.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_EQ(exAll, all);
}

TEST(Matrix4x4, Archive)
{
    Matrix4x4 input(1.0f, 2.0f, 3.0f, 4.0f,
                    4.0f, 5.0f, 6.0f, 7.0f,
                    7.0f, 8.0f, 9.0f, 10.0f,
                    8.0f, 9.0f, 10.0f, 11.0f);
    EXPECT_EQ(input, test::archive(input));
}

TEST(Matrix4x4, Stdout)
{
    Matrix4x4 input(1.0f, 2.0f, 3.0f, 4.0f,
                    4.0f, 5.0f, 6.0f, 7.0f,
                    7.0f, 8.0f, 9.0f, 10.0f,
                    8.0f, 9.0f, 10.0f, 11.0f);
    EXPECT_EQ(test::stdout(input), "[[1, 2, 3, 4],\n"
                                   " [4, 5, 6, 7],\n"
                                   " [7, 8, 9, 10],\n"
                                   " [8, 9, 10, 11]]");
}
}
}

NYRA_TEST()
