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
#ifndef __NYRA_MATH_MATRIX_H__
#define __NYRA_MATH_MATRIX_H__

#include <nyra/math/Vector2.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>

namespace nyra
{
namespace math
{
/*
 *  \class Matrix
 *  \brief A templated matrix class for any type with any size. In general
 *         this should not be used. Instead use the fixed size matrices. By
 *         default this will give you an identity matrix.
 *
 *  \tparam TypeT The data type of each element
 *  \tparam Rows The number of rows
 *  \tparam Cols The number of columns
 */
template<typename TypeT, size_t Rows, size_t Cols>
class Matrix
{
public:
    /*
     *  \func Destructor
     *  \brief Necessary for correct inheritance
     */
    virtual ~Matrix() = default;

    /*
     *  \func getSize
     *  \brief Gets the size of the matrix as cols / rows
     *
     *  \return The size
     */
    Vector2U getSize() const
    {
        return Vector2U(Cols, Rows);
    }

    /*
     *  \func Equality Operator
     *  \brief Checks if two matrices are equal.
     *
     *  \param other The matrix to check against
     *  \return true if the matrices have all the same values.
     */
    bool operator==(const Matrix<TypeT, Rows, Cols>& other) const
    {
        return gmtl::isEqual(mMatrix,
                             other.mMatrix,
                             static_cast<TypeT>(0.00001));
    }

    /*
     *  \func InEquality Operator
     *  \brief Checks if two matrices are not equal.
     *
     *  \param other The matrix to check against
     *  \return true if the matrices have any different values.
     */
    bool operator!=(const Matrix<TypeT, Rows, Cols>& other) const
    {
        return !((*this) == other);
    }

    /*
     *  \func Functor
     *  \brief Gets an element from the matrix
     *
     *  \param row The desired row
     *  \param col The desired column
     *  \return The element
     */
    const TypeT& operator()(size_t row, size_t col) const
    {
        return mMatrix[row][col];
    }

    /*
     *  \func Functor
     *  \brief Gets an element from the matrix
     *
     *  \param row The desired row
     *  \param col The desired column
     *  \return The element
     */
    TypeT& operator()(size_t row, size_t col)
    {
        mMatrix.setState(gmtl::Matrix<TypeT, Rows, Cols>::FULL);
        return mMatrix[row][col];
    }

    /*
     *  \func Multiply Assign
     *  \brief Multiplies a matrix in this matrix
     *
     *  \tparam OtherRows The number of rows in the other matrix
     *  \tparam OtherCols The number of columns in the other matrix
     *  \param other The matrix to multiple
     *  \return The updated matrix
     */
    template <size_t OtherRows, size_t OtherCols>
    Matrix<TypeT, Rows, Cols>& operator*=(
            const Matrix<TypeT, OtherRows, OtherCols>& other)
    {
        mMatrix *= other.mMatrix;
        return *this;
    }

    /*
     *  \func Multiply
     *  \brief Multiplies two matrices together
     *
     *  \tparam OtherRows The number of rows in the other matrix
     *  \tparam OtherCols The number of columns in the other matrix
     *  \param other The matrix to multiply
     *  \return The product matrix
     */
    template <size_t OtherRows, size_t OtherCols>
    Matrix<TypeT, Rows, Cols> operator*(
            Matrix<TypeT, OtherRows, OtherCols> other) const
    {
        other *= (*this);
        return other;
    }

    /*
     *  \func getNative
     *  \brief Returns the GMTL object
     *
     *  \return The GMTL object
     */
    const gmtl::Matrix<TypeT, Rows, Cols>& getNative() const
    {
        return mMatrix;
    }

    /*
     *  \func getNative
     *  \brief Returns the GMTL object
     *
     *  \return The GMTL object
     */
    gmtl::Matrix<TypeT, Rows, Cols>& getNative()
    {
        return mMatrix;
    }

private:
    NYRA_SERIALIZE()

    template<class ArchiveT>
    void serialize(ArchiveT& archive, const unsigned int version)
    {
        for (size_t ii = 0; ii < Rows; ++ii)
        {
            for (size_t jj = 0; jj < Cols; ++jj)
            {
                archive & (*this)(ii, jj);
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const Matrix<TypeT, Rows, Cols>& matrix)
    {
        const Vector2U size = matrix.getSize();
        for (size_t ii = 0; ii < size.y(); ++ii)
        {
            if (ii == 0)
            {
                os << "[";
            }
            else
            {
                os << " ";
            }
            os << "[";
            for (size_t jj = 0; jj < size.x(); ++jj)
            {
                if (jj != 0)
                {
                    os << ", ";
                }
                os << matrix(ii, jj);
            }
            os << "]";
            if (ii < size.y() - 1)
            {
                os << ",\n";
            }
            else
            {
                os << "]";
            }
        }
        return os;
    }

protected:
    gmtl::Matrix<TypeT, Rows, Cols> mMatrix;
};
}
}

#endif

