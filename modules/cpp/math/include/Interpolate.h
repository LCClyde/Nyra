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
#ifndef __NYRA_MATH_INTERPOLATE_H__
#define __NYRA_MATH_INTERPOLATE_H__

namespace nyra
{
namespace math
{
/*
 *  \func linearInterpolate
 *  \brief Interpolates linearly between a start and an end.
 *
 *  \tparam T The data type to interpolate.
 *  \param start The starting value
 *  \param end The ending value
 *  \param delta The amount from 0 - 1 to interpolate. A value of 0 will return
 *         start. A value of 1 will return end.
 *  \return The interpolated value.
 */
template <typename T>
T linearInterpolate(const T& start, const T& end, double delta)
{
    return start + delta * (end - start);
}
}
}

#endif
