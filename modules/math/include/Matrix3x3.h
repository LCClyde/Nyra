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
#ifndef __NYRA_MATH_MATRIX_3X3_H__
#define __NYRA_MATH_MATRIX_3X3_H__

#include <nyra/math/Matrix.h>
#include <nyra/math/Vector2.h>

namespace nyra
{
namespace math
{
/*
 *  \class Matrix3x3
 *  \brief Matrix used for 2D transforms
 */
class Matrix3x3 : public Matrix<float, 3, 3>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an identity matrix.
     */
    Matrix3x3() = default;

    /*
     *  \func Constructor
     *  \brief Creates a matrix with known values
     *
     *  \param a11 row 1 column 1
     *  \param a12 row 1 column 2
     *  \param a13 row 1 column 3
     *  \param a21 row 2 column 1
     *  \param a22 row 2 column 2
     *  \param a23 row 2 column 3
     *  \param a31 row 3 column 1
     *  \param a32 row 3 column 2
     *  \param a33 row 3 column 3
     */
    Matrix3x3(float a11, float a12, float a13,
              float a21, float a22, float a23,
              float a31, float a32, float a33);

    /*
     *  \func Constructor
     *  \brief Copy constructs from the base class.
     *
     *  \param other The matrix to copy
     */
    Matrix3x3(const Matrix<float, 3, 3>& other);

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
    void transform(const Vector2F& position,
                   const Vector2F& scale,
                   float rotation,
                   const Vector2F& pivot);
};
}
}

#endif
