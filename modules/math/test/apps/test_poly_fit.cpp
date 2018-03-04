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
#include <nyra/math/PolyFit.h>
#include <nyra/test/Test.h>

namespace
{
class TestPolyFit
{
public:
    TestPolyFit(const std::vector<double>& coefs) :
        mX(100),
        mY(mX.size())
    {
        for (size_t ii = 0; ii < coefs.size(); ++ii)
        {
            mPoly.set(ii, coefs[ii]);
        }

        for (size_t ii = 0; ii < mX.size(); ++ii)
        {
            mX[ii] = -(mX.size() / 2.0) + ii;
            mY[ii] = mPoly(mX[ii]);
        }

        mResults = nyra::math::polyFit(mX, mY, mPoly.getOrder());
    }

    size_t size() const
    {
        return mX.size();
    }

    double expected(size_t ii) const
    {
        return mY[ii];
    }

    double actual(size_t ii) const
    {
        return mResults(mX[ii]);
    }

private:
    nyra::math::Polynomial mPoly;
    nyra::math::Polynomial mResults;
    std::vector<double> mX;
    std::vector<double> mY;
};
}

namespace nyra
{
namespace math
{
TEST(PolyFit, Constant)
{
    TestPolyFit test({459.765});

    for (size_t ii = 0; ii < test.size(); ++ii)
    {
        EXPECT_NEAR(test.expected(ii),
                    test.actual(ii),
                    0.0001);
    }
}

TEST(PolyFit, Linear)
{
    TestPolyFit test({2.25, 1.67});

    for (size_t ii = 0; ii < test.size(); ++ii)
    {
        EXPECT_NEAR(test.expected(ii),
                    test.actual(ii),
                    0.0001);
    }
}

TEST(PolyFit, Quadratic)
{
    TestPolyFit test({-87.4, 10.125, 2.9});

    for (size_t ii = 0; ii < test.size(); ++ii)
    {
        EXPECT_NEAR(test.expected(ii),
                    test.actual(ii),
                    0.0001);
    }
}

TEST(PolyFit, Cubic)
{
    TestPolyFit test({-12.5, -6.7, -2.1, 0.4});

    for (size_t ii = 0; ii < test.size(); ++ii)
    {
        EXPECT_NEAR(test.expected(ii),
                    test.actual(ii),
                    0.0001);
    }
}

TEST(PolyFit, Crazy)
{
    std::vector<double> coefs;

    // This is an attempt to try to keep the output values sane.
    double val = 1E-35;
    for (size_t ii = 0; ii < 25; ++ii)
    {
        coefs.push_back(val);
        val *= -1.0;
    }
    TestPolyFit test(coefs);

    for (size_t ii = 0; ii < test.size(); ++ii)
    {
        EXPECT_NEAR(test.expected(ii),
                    test.actual(ii),
                    0.1);
    }
}
}
}

NYRA_TEST()
