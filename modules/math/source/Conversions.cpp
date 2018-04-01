/*
 * Copyright (c) 2018 Clyde Stanfield
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
#include <nyra/math/Conversions.h>

namespace nyra
{
namespace math
{
//===========================================================================//
Vector<float, 4> eulerToQuaternion(const Vector3F& euler)
{
    gmtl::EulerAngleXYZf gEuler(math::degreesToRadians(euler.x),
                                math::degreesToRadians(euler.y),
                                math::degreesToRadians(euler.z));
    gmtl::Quatf quaternion;
    gmtl::set(quaternion, gEuler);

    Vector<float, 4> ret;
    ret[0] = quaternion[0];
    ret[1] = quaternion[1];
    ret[2] = quaternion[2];
    ret[3] = quaternion[3];
    return ret;
}
}
}
