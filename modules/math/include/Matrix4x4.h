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
#ifndef __NYRA_MATH_MATRIX_4X4_H__
#define __NYRA_MATH_MATRIX_4X4_H__

#include <nyra/math/Matrix.h>
#include <nyra/math/Vector3.h>

namespace nyra
{
namespace math
{
/*
 *  \class Matrix4x4
 *  \brief Matrix used for 3D transforms
 */
class Matrix4x4 : public Matrix<float, 4, 4>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an identity matrix.
     */
    Matrix4x4() = default;

    /*
     *  \func Constructor
     *  \brief Creates a matrix with known values
     *
     *  \param a11 row 1 column 1
     *  \param a12 row 1 column 2
     *  \param a13 row 1 column 3
     *  \param a14 row 1 column 4
     *  \param a21 row 2 column 1
     *  \param a22 row 2 column 2
     *  \param a23 row 2 column 3
     *  \param a24 row 2 column 4
     *  \param a31 row 3 column 1
     *  \param a32 row 3 column 2
     *  \param a33 row 3 column 3
     *  \param a34 row 3 column 4
     *  \param a41 row 4 column 1
     *  \param a42 row 4 column 2
     *  \param a43 row 4 column 3
     *  \param a44 row 4 column 4
     */
    Matrix4x4(float a11, float a12, float a13, float a14,
              float a21, float a22, float a23, float a24,
              float a31, float a32, float a33, float a34,
              float a41, float a42, float a43, float a44);

    /*
     *  \func Constructor
     *  \brief Copy constructs from the base class.
     *
     *  \param other The matrix to copy
     */
    Matrix4x4(const Matrix<float, 4, 4>& other);

    /*
     *  \func transform
     *  \brief Creates a transform matrix from smaller pieces. Note that this
     *         destroys the current matrix.
     *
     *  \param position The position of the object
     *  \param scale The scale of the object
     *  \param rotation The rotation of the object
     *  \param pivot The pivot point of the object
     */
    void transform(const Vector3F& position,
                   const Vector3F& scale,
                   const Vector3F& rotation,
                   const Vector3F& pivot);
};
}
}

#endif
