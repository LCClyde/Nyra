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
#include <nyra/math/Matrix.h>
#include <nyra/test/Test.h>

namespace
{
nyra::math::Matrix<float, 3, 3> get()
{
    nyra::math::Matrix<float, 3, 3> matrix;
    for (size_t ii = 0; ii < 3; ++ii)
    {
        for (size_t jj = 0; jj < 3; ++jj)
        {
            matrix(ii, jj) = (ii * 3) + jj + 1;
        }
    }
    return matrix;
}
}

namespace nyra
{
namespace math
{
TEST(Matrix, Construction)
{
    const Matrix<float, 3, 3> matrix;
    EXPECT_EQ(Vector2U(3, 3), matrix.getSize());
    for (size_t ii = 0; ii < 3; ++ii)
    {
        for (size_t jj = 0; jj < 3; ++jj)
        {
            EXPECT_EQ(matrix(ii, jj), ii == jj ? 1.0f: 0.0f);
        }
    }
}

TEST(Matrix, Multiply)
{
    Matrix<float, 3, 3> m1 = get();
    Matrix<float, 3, 3> m2 = get();
    Matrix<float, 3, 3> ans;
    ans(0, 0) = 30.0f;
    ans(0, 1) = 36.0f;
    ans(0, 2) = 42.0f;

    ans(1, 0) = 66.0f;
    ans(1, 1) = 81.0f;
    ans(1, 2) = 96.0f;

    ans(2, 0) = 102.0f;
    ans(2, 1) = 126.0f;
    ans(2, 2) = 150.0f;

    EXPECT_EQ(m1 * m2, ans);
    m1 *= m2;
    EXPECT_EQ(m1, ans);
}

TEST(Matrix, Archive)
{
    Matrix<float, 3, 3> input = get();
    EXPECT_EQ(input, test::archive(input));
}

TEST(Matrix, Stdout)
{
    Matrix<float, 3, 3> input = get();
    EXPECT_EQ(test::stdout(input), "[[1, 2, 3],\n"
                                   " [4, 5, 6],\n"
                                   " [7, 8, 9]]");
}
}
}

NYRA_TEST()
