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
#ifndef __NYRA_MATH_CONVERSIONS_H__
#define __NYRA_MATH_CONVERSIONS_H__

#include <math.h>
#include <nyra/math/Vector.h>
#include <nyra/math/Vector3.h>
#include <gmtl/Generate.h>

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

/*
 *  \func normalizeAngle
 *  \brief Normalizes between [0.0 - 360.0)
 *
 *  \param value The starting value
 */
inline double normalizeAngle(double value)
{
    value = fmod(value, 360);
    if (value < 0)
    {
        value += 360;
    }
    return value;
}

/*
 *  \func normalizeAngle
 *  \brief Normalizes a vector of angles between [0.0 - 360.0)
 *
 *  \tparam TypeT The data type of the vector
 *  \tparam SizeT The size of the vector
 *  \param value The starting value
 */
template <typename TypeT, size_t SizeT>
Vector<TypeT, SizeT> normalizeAngle(Vector<TypeT, SizeT> value)
{
    for (size_t ii = 0; ii < SizeT; ++ii)
    {
        value[ii] = normalizeAngle(value[ii]);
    }
    return value;
}

/*
 *  \func eulerToQuaternion
 *  \brief Converts Euler angles to quaternions
 *
 *  \param euler The input euler angles
 *  \return The 4D quaternion
 */
Vector<float, 4> eulerToQuaternion(const Vector3F& euler);
}
}

#endif
