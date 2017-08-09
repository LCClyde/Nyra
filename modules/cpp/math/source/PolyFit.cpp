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
#include <cmath>
#include <stdint.h>

namespace nyra
{
namespace math
{
//===========================================================================//
// TODO: Clean this up a lot.
Polynomial polyFit(const std::vector<double>& x,
                   const std::vector<double>& y,
                   size_t order)
{
    Polynomial poly(order);
    const size_t numPoints = x.size();

    std::vector<double> X(2 * order + 1, 0.0);
    for (size_t ii = 0; ii < X.size(); ++ii)
    {
        for (size_t jj = 0; jj < numPoints; ++jj)
        {
            X[ii] = X[ii] + std::pow(x[jj], ii);
        }
    }

    std::vector<std::vector<double>>B(order + 1);
    for (size_t ii = 0; ii < B.size(); ++ii)
    {
        B[ii].resize(order + 2);
    }

    for (size_t ii = 0; ii <= order; ++ii)
    {
        for (size_t jj = 0; jj <= order; ++jj)
        {
            B[ii][jj] = X[ii + jj];
        }
    }

    std::vector<double> Y(order + 1, 0.0);
    for (size_t ii = 0;ii < Y.size(); ++ii)
    {
        for (size_t jj = 0; jj < numPoints; ++jj)
        {
            Y[ii] = Y[ii] + std::pow(x[jj], ii) * y[jj];
        }
    }

    for (size_t ii = 0; ii <= order; ++ii)
    {
        B[ii][order + 1] = Y[ii];
    }

    ++order;

    for (size_t ii = 0; ii < order; ++ii)
    {
        for (size_t kk = ii + 1; kk < order; ++kk)
        {
            if (B[ii][ii] < B[kk][ii])
            {
                for (size_t jj = 0; jj <= order; ++jj)
                {
                    std::swap(B[ii][jj], B[kk][jj]);
                }
            }
        }
    }

    for (size_t ii = 0; ii < order - 1; ++ii)
    {
        for (size_t kk = ii + 1; kk < order; ++kk)
        {
            double t = B[kk][ii] / B[ii][ii];
            for (size_t jj = 0; jj <= order; ++jj)
            {
                B[kk][jj] = B[kk][jj] - t * B[ii][jj];
            }
        }
    }

    for (int64_t ii = order - 1; ii >= 0; --ii)
    {
        poly.set(ii, B[ii][order]);
        for (size_t jj = 0; jj < order; ++jj)
        {
            if (jj != static_cast<size_t>(ii))
            {
                poly.set(ii, poly.getCoefficient(ii) -
                        B[ii][jj] * poly.getCoefficient(jj));
            }
        }
        poly.set(ii, poly.getCoefficient(ii) / B[ii][ii]);
    }

    return poly;
}
}
}
