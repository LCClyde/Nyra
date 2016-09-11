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
#include <nyra/math/Matrix3x3.h>
#include <nyra/math/Conversions.h>
#include <gmtl/Generate.h>

namespace nyra
{
namespace math
{
//===========================================================================//
Matrix3x3::Matrix3x3(float a11, float a12, float a13,
                     float a21, float a22, float a23,
                     float a31, float a32, float a33)
{
    (*this)(0, 0) = a11;
    (*this)(0, 1) = a12;
    (*this)(0, 2) = a13;

    (*this)(1, 0) = a21;
    (*this)(1, 1) = a22;
    (*this)(1, 2) = a23;

    (*this)(2, 0) = a31;
    (*this)(2, 1) = a32;
    (*this)(2, 2) = a33;
}

//===========================================================================//
Matrix3x3::Matrix3x3(const Matrix<float, 3, 3>& other)
{
    mMatrix = other.getNative();
}

//===========================================================================//
void Matrix3x3::transform(const Vector2F& position,
                          const Vector2F& scale,
                          float rotation,
                          const Vector2F& pivot)
{
    // TODO: SFML does this as a single assignment to a 3x3 matrix. I need to
    //       test what kind of performance gain that gives. I would rather
    //       not maintain the linear algebra.
    gmtl::Matrix<float, 3, 3> pivotMatrix;
    gmtl::setTrans(pivotMatrix, pivot.getNative());

    gmtl::Matrix<float, 3, 3> translationMatrix;
    gmtl::setTrans(translationMatrix, position.getNative());

    gmtl::Matrix<float, 3, 3> scaleMatrix;
    gmtl::setScale(scaleMatrix, scale.getNative());

    gmtl::Matrix<float, 3, 3> rotationMatrix;
    gmtl::EulerAngle<float, gmtl::XYZ> eulerRotation(
            0.0f, 0.0f, degreesToRadians(rotation));
    gmtl::setRot(rotationMatrix, eulerRotation);
    mMatrix = translationMatrix * rotationMatrix * scaleMatrix * pivotMatrix;
}
}
}
