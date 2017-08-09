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
#include <nyra/math/Polynomial.h>
#include <nyra/test/Test.h>

namespace nyra
{
namespace math
{
TEST(Polynomial, Values)
{
    Polynomial poly;
    std::vector<double> results = {0, 0, 0, 0, 0};

    for (int32_t ii = -2, jj = 0; ii < 3; ++ii, ++jj)
    {
        EXPECT_EQ(results[jj], poly(ii));
    }
    EXPECT_EQ(static_cast<size_t>(0), poly.getOrder());
    EXPECT_EQ(0.0, poly.getCoefficient(0));

    const double constantTerm = 13.6;
    poly.set(0, constantTerm);
    for (int32_t ii = -2, jj = 0; ii < 3; ++ii, ++jj)
    {
        results[jj] += constantTerm;
        EXPECT_EQ(results[jj], poly(ii));
    }
    EXPECT_EQ(static_cast<size_t>(0), poly.getOrder());
    EXPECT_EQ(constantTerm, poly.getCoefficient(0));

    const double linearTerm = -0.925;
    poly.set(1, linearTerm);
    for (int32_t ii = -2, jj = 0; ii < 3; ++ii, ++jj)
    {
        results[jj] += linearTerm * ii;
        EXPECT_EQ(results[jj], poly(ii));
    }
    EXPECT_EQ(static_cast<size_t>(1), poly.getOrder());
    EXPECT_EQ(linearTerm, poly.getCoefficient(1));

    const double quadraticTerm = 0.14;
    poly.set(2, quadraticTerm);
    for (int32_t ii = -2, jj = 0; ii < 3; ++ii, ++jj)
    {
        results[jj] += quadraticTerm * ii * ii;
        EXPECT_EQ(results[jj], poly(ii));
    }
    EXPECT_EQ(static_cast<size_t>(2), poly.getOrder());
    EXPECT_EQ(quadraticTerm, poly.getCoefficient(2));

    const double cubicTerm = -0.111;
    poly.set(3, cubicTerm);
    for (int32_t ii = -2, jj = 0; ii < 3; ++ii, ++jj)
    {
        results[jj] += cubicTerm * ii * ii * ii;
        EXPECT_EQ(results[jj], poly(ii));
    }
    EXPECT_EQ(static_cast<size_t>(3), poly.getOrder());
    EXPECT_EQ(cubicTerm, poly.getCoefficient(3));

    const double crazyTerm = 1.34;
    const size_t crazyOrder = 500;
    poly.set(crazyOrder, crazyTerm);
    for (int32_t ii = -2, jj = 0; ii < 3; ++ii, ++jj)
    {
        results[jj] += crazyTerm * std::pow(ii, crazyOrder);
        EXPECT_EQ(results[jj], poly(ii));
    }
    EXPECT_EQ(static_cast<size_t>(crazyOrder), poly.getOrder());

    for (size_t ii = 4; ii < crazyOrder; ++ii)
    {
        EXPECT_EQ(0.0, poly.getCoefficient(ii));
    }
    EXPECT_EQ(crazyTerm, poly.getCoefficient(crazyOrder));
}

TEST(Polynomial, Stdout)
{
    Polynomial input;
    input.set(0, 1);
    input.set(1, 2);
    input.set(2, 3);
    input.set(3, 4);
    EXPECT_EQ(test::stdout(input), "y = 4x^3 + 3x^2 + 2x^1 + 1");
}
}
}

NYRA_TEST()
