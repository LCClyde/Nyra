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
#include <nyra/math/Conversions.h>
#include <gmtl/Generate.h>

namespace nyra
{
namespace math
{
//===========================================================================//
Matrix4x4::Matrix4x4(float a11, float a12, float a13, float a14,
                     float a21, float a22, float a23, float a24,
                     float a31, float a32, float a33, float a34,
                     float a41, float a42, float a43, float a44)
{
    (*this)(0, 0) = a11;
    (*this)(0, 1) = a12;
    (*this)(0, 2) = a13;
    (*this)(0, 3) = a14;

    (*this)(1, 0) = a21;
    (*this)(1, 1) = a22;
    (*this)(1, 2) = a23;
    (*this)(1, 3) = a24;

    (*this)(2, 0) = a31;
    (*this)(2, 1) = a32;
    (*this)(2, 2) = a33;
    (*this)(2, 3) = a34;

    (*this)(3, 0) = a41;
    (*this)(3, 1) = a42;
    (*this)(3, 2) = a43;
    (*this)(3, 3) = a44;
}

//===========================================================================//
Matrix4x4::Matrix4x4(const Matrix<float, 4, 4>& other)
{
    mMatrix = other.getNative();
}

//===========================================================================//
void Matrix4x4::transform(const Vector3F& position,
                          const Vector3F& scale,
                          const Vector3F& rotation,
                          const Vector3F& pivot)
{
    gmtl::Matrix<float, 4, 4> pivotMatrix;
    gmtl::setTrans(pivotMatrix, pivot.getNative());

    gmtl::Matrix<float, 4, 4> translationMatrix;
    gmtl::setTrans(translationMatrix, position.getNative());

    gmtl::Matrix<float, 4, 4> scaleMatrix;
    gmtl::setScale(scaleMatrix, scale.getNative());

    gmtl::Matrix<float, 4, 4> rotationMatrix;
    gmtl::EulerAngle<float, gmtl::XYZ> eulerRotation(
            degreesToRadians(rotation.x),
            degreesToRadians(rotation.y),
            degreesToRadians(rotation.z));
    gmtl::setRot(rotationMatrix, eulerRotation);

    mMatrix = translationMatrix * rotationMatrix * scaleMatrix * pivotMatrix;
}
}
}
