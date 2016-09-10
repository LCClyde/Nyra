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
#ifndef __NYRA_MATH_VECTOR_H__
#define __NYRA_MATH_VECTOR_H__

#include <nyra/core/Archive.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <stddef.h>

namespace nyra
{
namespace math
{
/*
 *  \class Vector
 *  \brief A two dimensional vector. This can be used for 2D position or scale.
 *         Common types are typenamed for easier use.
 *
 *  \tparam TypeT The data type for elements.
 */
template <typename TypeT, size_t SizeT>
class Vector
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up a zero'd vector
     */
    Vector() = default;

    /*
     *  \func Constructor
     *  \brief Constructs a vector from another vector. This can be used
     *         to copy from 3rd party vectors.
     *
     *  \tparam VectorT The vector type to copy from. This must have public
     *          x and y members.
     *  \param vector The vector to copy.
     */
    Vector(const Vector<TypeT, SizeT>& vector) :
        mVec(vector.mVec)
    {
    }

    /*
     *  \func Destructor
     *  \brief Necessary for inheritance
     */
    virtual ~Vector() = default;

    /*
     *  \func Equality Operator
     *  \brief Checks if each element of each vector are equal.
     *
     *  \param other The vector to check against.
     *  \return True if the vectors are equal.
     */
    bool operator==(const Vector<TypeT, SizeT>& other) const
    {
        return mVec == other.mVec;
    }

    /*
     *  \func Inequality Operator
     *  \brief Checks if any value in either vector are not equal.
     *
     *  \param other The vector to check against.
     *  \return True if the vectors are not equal.
     */
    bool operator!=(const Vector<TypeT, SizeT>& other) const
    {
        return !(*this == other);
    }

    /*
     *  \func Addition Assignment Operator
     *  \brief Adds each element of the vectors together.
     *
     *  \param other The vector to add.
     *  \return The original vector with the other vector added to it.
     */
    Vector<TypeT, SizeT>& operator+=(const Vector<TypeT, SizeT>& other)
    {
        mVec += other.mVec;
        return *this;
    }

    /*
     *  \func Subtraction Assignment Operator
     *  \brief Subtracts each element of the vectors.
     *
     *  \param other The vector to subtract.
     *  \return The original vector with the other vector subtracted from it.
     */
    Vector<TypeT, SizeT>& operator-=(const Vector<TypeT, SizeT>& other)
    {
        mVec -= other.mVec;
        return *this;
    }

    /*
     *  \func Multiplication Assignment Operator
     *  \brief Multiplies each element in the vector by a passed in value.
     *
     *  \param value The value to multiply by.
     *  \return The original vector with the value multiplied by it.
     */
    Vector<TypeT, SizeT>& operator*=(double value)
    {
        mVec *= value;
        return *this;
    }

    /*
     *  \func Division Assignment Operator
     *  \brief Divides each element in a vector by a passed in value.
     *
     *  \param value The value to divide by.
     *  \return The original vector divided by the value.
     */
    Vector<TypeT, SizeT>& operator/=(double value)
    {
        mVec /= value;
        return *this;
    }

    /*
     *  \func Addition Operator
     *  \brief Adds two vectors together, element by element.
     *
     *  \param other The other vector to add. Note this is passed in by
     *         value since the operator will need to return by value
     *         anyways.
     *  \return A new vector which is both vectors added together.
     */
    Vector<TypeT, SizeT> operator+(Vector<TypeT, SizeT> other) const
    {
        other += (*this);
        return other;
    }

    /*
     *  \func Subtraction Operator
     *  \brief Subtracts two vectors, element by element.
     *
     *  \param other The other vector to subtract. Note this is passed in by
     *         value since the operator will need to return by value
     *         anyways.
     *  \return A new vector which is the difference between the vectors.
     */
    Vector<TypeT, SizeT> operator-(Vector<TypeT, SizeT> other) const
    {
        other -= (*this);
        return other;
    }

    /*
     *  \func Multiplication Operator
     *  \brief Multiplies each element by a scalar.
     *
     *  \param value The value to multiply each element by.
     *  \return A new vector which is multiplied by the scalar.
     */
    Vector<TypeT, SizeT> operator*(double value) const
    {
        Vector<TypeT, SizeT> ret(*this);
        ret *= value;
        return ret;
    }

    /*
     *  \func Division Operator
     *  \brief Divides each element by a scalar.
     *
     *  \param value The value to divide each element by.
     *  \return A new vector which is divided by the scalar.
     */
    Vector<TypeT, SizeT> operator/(double value) const
    {
        Vector<TypeT, SizeT> ret(*this);
        ret /= value;
        return ret;
    }

    /*
     *  \func Index Operator
     *  \brief Gets the value at an index
     *
     *  \param index The index of the value
     *  \return The element at the index
     */
    const TypeT& operator[](size_t index) const
    {
        return mVec[index];
    }

    /*
     *  \func Index Operator
     *  \brief Gets the value at an index
     *
     *  \param index The index of the value
     *  \return The element at the index
     */
    TypeT& operator[](size_t index)
    {
        return mVec[index];
    }

    /*
     *  \func sum
     *  \brief Adds all elements in a vector together into one value.
     *
     *  \return The sum of all the elements.
     */
    TypeT sum() const
    {
        TypeT ret = 0;
        for (size_t ii = 0; ii < SizeT; ++ii)
        {
            ret += mVec[ii];
        }
        return ret;
    }

    /*
     *  \func product
     *  \brief Multiples all the elements in a vector together.
     *
     *  \return The product of all the elements.
     */
    TypeT product() const
    {
        TypeT ret = mVec[0];
        for (size_t ii = 1; ii < SizeT; ++ii)
        {
            ret *= mVec[ii];
        }
        return ret;
    }

    /*
     *  \func sumSquares
     *  \brief Adds the squares of all the elements together.
     *
     *  \return The sum of all the squares of the elements.
     */
    TypeT sumSquares() const
    {
        return gmtl::lengthSquared(mVec);
    }

    /*
     *  \func Length
     *  \brief Calculates the magnitude of a vector. If you just need a
     *         comparison between two lengths then LengthSquared is slightly
     *         more efficient.
     *
     *  \return The length of the vector.
     */
    double length() const
    {
        return gmtl::length(mVec);
    }

    /*
     *  \func LengthSquared
     *  \brief Calculates the magnitude of the vector without the final square
     *         root. Use this instead of Length if you just need to compare
     *         two lengths.
     *
     *  \return The length of the vector squared.
     */
    double lengthSquared() const
    {
        return gmtl::lengthSquared(mVec);
    }

    /*
     *  \func Normalize
     *  \brief Normalizes a vector so it has a length of 1.
     */
    void normalize()
    {
        gmtl::normalize(mVec);
        (*this) /= length();
    }

    /*
     *  \func dot
     *  \brief Calculates the dot product of the vector
     *
     *  \return The dot product
     */
    double dot(const Vector<TypeT, SizeT>& other) const
    {
        return gmtl::dot(mVec, other.mVec);
    }

    /*
     *  \func getNative
     *  \brief Get the underlying GMTL vector
     *
     *  \return The GMTL vector
     */
    const gmtl::Vec<TypeT, SizeT>& getNative() const
    {
        return mVec;
    }

    /*
     *  \func getNative
     *  \brief Get the underlying GMTL vector
     *
     *  \return The GMTL vector
     */
    gmtl::Vec<TypeT, SizeT>& getNative()
    {
        return mVec;
    }

private:
    NYRA_SERIALIZE()

    template<class ArchiveT>
    void serialize(ArchiveT& archive, const unsigned int version)
    {
        for (size_t ii = 0; ii < SizeT; ++ii)
        {
            archive & mVec[ii];
        }
    }

protected:
    gmtl::Vec<TypeT, SizeT> mVec;
};

/*
 *  \func Output Stream Operator
 *  \brief Prints a vector.
 *
 *  \tparam TypeT The element type of the vector.
 *  \param os The output stream.
 *  \param vector The vector to print.
 *  \return The updated stream.
 */
template <typename TypeT, size_t SizeT>
std::ostream& operator<<(std::ostream& os, const Vector<TypeT, SizeT>& vector)
{
    for (size_t ii = 0; ii < SizeT; ++ii)
    {
        if (ii > 0)
        {
            os << " ";
        }
        os << "vec[" << ii << "]=" << vector[ii];
    }
    return os;
}
}
}

#endif
