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
#ifndef __NYRA_MATH_CONVERSIONS_H__
#define __NYRA_MATH_CONVERSIONS_H__

#include <math.h>

namespace nyra
{
namespace math
{
/*
 *  \func degreesToRadians
 *  \brief Converts degrees to radians
 *
 *  \param degrees The angle in degrees
 *  \return The angle in radians
 */
inline double degreesToRadians(double degrees)
{
    return degrees * (M_PI / 180.0);
}

/*
 *  \func radiansToDegrees
 *  \brief Converts radians to degrees
 *
 *  \param radians
 *  \return The angle in degrees
 */
inline double radiansToDegrees(double radians)
{
    return radians * (180.0 / M_PI);
}
}
}

#endif
