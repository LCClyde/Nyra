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
#ifndef __NYRA_MATH_POLYNOMIAL_H__
#define __NYRA_MATH_POLYNOMIAL_H__

#include <cstddef>
#include <vector>
#include <ostream>

namespace nyra
{
namespace math
{
/*
 *  \class Polynomial
 *  \brief A simple representation of a N order polynomial.
 */
class Polynomial
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an empty polynomial.
     */
    Polynomial() = default;

    /*
     *  \func Constructor
     *  \brief Creates a polynomial with a certain order. The starting
     *         value of all coefficients will be 0.
     *
     *  \param order The desired polynomial order
     */
    Polynomial(size_t order);

    /*
     *  \func set
     *  \brief Sets the value of a coefficient at an order. If the polynomial
     *         is not high enough order, it will be increased in order.
     *
     *  \param order The order to set.
     *  \param value The value to set.
     */
    void set(size_t order, double value);

    /*
     *  \func getCoefficient
     *  \brief Gets the coefficient at a certain order.
     *
     *  \param order The order to get
     *  \return The value of the coefficient.
     */
    double getCoefficient(size_t order) const
    {
        if (order == 0 && mCoefficients.empty())
        {
            return 0.0;
        }

        return mCoefficients[order];
    }

    /*
     *  \func getOrder
     *  \brief Gets the current order.
     *
     *  \return The order. An empty polynomial returns 0 (this means a
     *          constant term 0).
     */
    size_t getOrder() const
    {
        return mCoefficients.empty() ? 0 : mCoefficients.size() - 1;
    }

    /*
     *  \func Functor
     *  \brief Evaluates the polynomial at a certain value.
     *
     *  \param x The value to evaluate at.
     *  \return The result.
     */
    double operator()(double x) const;

private:
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);

    std::vector<double> mCoefficients;
};
}
}

#endif
