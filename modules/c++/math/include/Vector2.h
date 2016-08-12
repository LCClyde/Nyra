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
#ifndef __NYRA_MATH_VECTOR_2_H__
#define __NYRA_MATH_VECTOR_2_H__

#include <ostream>
#include <cmath>

namespace nyra
{
namespace math
{
/*
 *  \class Vector2Impl
 *  \brief A two dimensional vector. This can be used for 2D position or scale.
 *         Common types are typenamed for easier use.
 *
 *  \tparam TypeT The data type for elements.
 */
template <typename TypeT>
class Vector2Impl
{
public:
    /*
     *  \fn Constructor
     *  \brief Default constructor
     */
    Vector2Impl() :
        x(0.0),
        y(0.0)
    {
    }

    /*
     *  \fn Constructor
     *  \brief Constructs a vector from X and Y values.
     *
     *  \param x The starting x value.
     *  \param y The starting y value.
     */
    Vector2Impl(const TypeT& x, const TypeT& y) :
        x(x),
        y(y)
    {
    }

    /*
     *  \fn Constructor
     *  \brief Constructs a vector from another vector. This can be used
     *         to copy from 3rd party vectors.
     *
     *  \tparam VectorT The vector type to copy from. This must have public
     *          x and y members.
     *  \param vector The vector to copy.
     */
    template <typename VectorT>
    Vector2Impl(const VectorT& vector) :
        x(static_cast<TypeT>(vector.x)),
        y(static_cast<TypeT>(vector.y))
    {
    }

    /*
     *  \fn ToThirdParty
     *  \brief Converts a Vector2 into another 3rd party vector type.
     *
     *  \tparam ThirdPartyT The vector type to copy. This must have public
     *          x and y members.
     *  \return An instance of the 3rd party vector that acts a copy of this.
     */
    template <typename ThirdPartyT>
    ThirdPartyT toThirdParty() const
    {
        ThirdPartyT ret;
        ret.x = x;
        ret.y = y;
        return ret;
    }

    /*
     *  \fn Equality Operator
     *  \brief Checks if each element of each vector are equal.
     *
     *  \param other The vector to check against.
     *  \return True if the vectors are equal.
     */
    bool operator==(const Vector2Impl<TypeT>& other) const
    {
        return x == other.x && y == other.y;
    }

    /*
     *  \fn Inequality Operator
     *  \brief Checks if any value in either vector are not equal.
     *
     *  \param other The vector to check against.
     *  \return True if the vectors are not equal.
     */
    bool operator!=(const Vector2Impl<TypeT>& other) const
    {
        return !(*this == other);
    }

    /*
     *  \fn Addition Assignment Operator
     *  \brief Adds each element of the vectors together.
     *
     *  \param other The vector to add.
     *  \return The original vector with the other vector added to it.
     */
    Vector2Impl<TypeT>& operator+=(const Vector2Impl<TypeT>& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    /*
     *  \fn Subtraction Assignment Operator
     *  \brief Subtracts each element of the vectors.
     *
     *  \param other The vector to subtract.
     *  \return The original vector with the other vector subtracted from it.
     */
    Vector2Impl<TypeT>& operator-=(const Vector2Impl<TypeT>& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    /*
     *  \fn Multiplication Assignment Operator
     *  \brief Multiplies each element of the vectors together.
     *
     *  \param other The vector to multiply by.
     *  \return The original vector with the other vector multiplied by it.
     */
    Vector2Impl<TypeT>& operator*=(const Vector2Impl<TypeT>& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    /*
     *  \fn Division Assignment Operator
     *  \brief Divides each element of the vectors.
     *
     *  \param other The vector to divide.
     *  \return The original vector with the other vector divided from it.
     */
    Vector2Impl<TypeT>& operator/=(const Vector2Impl<TypeT>& other)
    {
        x /= static_cast<double>(other.x);
        y /= static_cast<double>(other.y);
        return *this;
    }

    /*
     *  \fn Addition Assignment Operator
     *  \brief Adds a passed in value to each element in the vector.
     *
     *  \tparam ValueT The value data type.
     *  \param value The value to add.
     *  \return The original vector with the value added to it.
     */
    template <typename ValueT>
    Vector2Impl<TypeT>& operator+=(const ValueT& value)
    {
        x += value;
        y += value;
        return *this;
    }

    /*
     *  \fn Subtraction Assignment Operator
     *  \brief Subtracts a passed in value from each element in the vector.
     *
     *  \tparam ValueT The value data type.
     *  \param value The value to subtract.
     *  \return The original vector with the value subtracted from it.
     */
    template <typename ValueT>
    Vector2Impl<TypeT>& operator-=(const ValueT& value)
    {
        x -= value;
        y -= value;
        return *this;
    }

    /*
     *  \fn Multiplication Assignment Operator
     *  \brief Multiplies each element in the vector by a passed in value.
     *
     *  \param value The value to multiply by.
     *  \return The original vector with the value multiplied by it.
     */
    Vector2Impl<TypeT>& operator*=(double value)
    {
        x *= value;
        y *= value;
        return *this;
    }

    /*
     *  \fn Division Assignment Operator
     *  \brief Divides each element in a vector by a passed in value.
     *
     *  \param value The value to divide by.
     *  \return The original vector divided by the value.
     */
    Vector2Impl<TypeT>& operator/=(double value)
    {
        x /= value;
        y /= value;
        return *this;
    }

    /*
     *  \fn Addition Operator
     *  \brief Adds two vectors together, element by element.
     *
     *  \param other The other vector to add. Note this is passed in by
     *         value since the operator will need to return by value
     *         anyways.
     *  \return A new vector which is both vectors added together.
     */
    Vector2Impl<TypeT> operator+(Vector2Impl<TypeT> other) const
    {
        other += (*this);
        return other;
    }

    /*
     *  \fn Subtraction Operator
     *  \brief Subtracts two vectors, element by element.
     *
     *  \param other The other vector to subtract. Note this is passed in by
     *         value since the operator will need to return by value
     *         anyways.
     *  \return A new vector which is the difference between the vectors.
     */
    Vector2Impl<TypeT> operator-(Vector2Impl<TypeT> other) const
    {
        other -= (*this);
        return other;
    }

    /*
     *  \fn Multiplcation Operator
     *  \brief Multiplies two vectors together, element by element.
     *
     *  \param other The other vector to multiply by. Note this is passed in by
     *         value since the operator will need to return by value
     *         anyways.
     *  \return A new vector which is product of the vectors.
     */
    Vector2Impl<TypeT> operator*(Vector2Impl<TypeT> other) const
    {
        other *= (*this);
        return other;
    }

    /*
     *  \fn Division Operator
     *  \brief Divides two vectors, element by element.
     *
     *  \param other The other vector to divide. In this case the other
     *         vector is not passed in by value because we need to copy this
     *         vector to get the divisor correct.
     *  \return A new vector which is the division of the vectors.
     */
    Vector2Impl<TypeT> operator/(const Vector2Impl<TypeT>& other) const
    {
        Vector2Impl<TypeT> ret(*this);
        ret /= other;
        return ret;
    }

    /*
     *  \fn Addition Operator
     *  \brief Adds a scalar to each element of a vector.
     *
     *  \tparam ValueT The data type of the value.
     *  \param value The value to add to each element.
     *  \return A new vector which has the value added to each element.
     */
    template <typename ValueT>
    Vector2Impl<TypeT> operator+(const ValueT& value) const
    {
        Vector2Impl<TypeT> ret(*this);
        ret += value;
        return ret;
    }

    /*
     *  \fn Subtraction Operator
     *  \brief Subtracts a scalar from each element of a vector.
     *
     *  \tparam ValueT The data type of the value.
     *  \param value The value to subtract from each element.
     *  \return A new vector which has the value subtracted from each element.
     */
    template <typename ValueT>
    Vector2Impl<TypeT> operator-(const ValueT& value) const
    {
        Vector2Impl<TypeT> ret(*this);
        ret -= value;
        return ret;
    }

    /*
     *  \fn Multiplication Operator
     *  \brief Multiplies each element by a scalar.
     *
     *  \param value The value to multiply each element by.
     *  \return A new vector which is multiplied by the scalar.
     */
    Vector2Impl<TypeT> operator*(double value) const
    {
        Vector2Impl<TypeT> ret(*this);
        ret *= value;
        return ret;
    }

    /*
     *  \fn Division Operator
     *  \brief Divides each element by a scalar.
     *
     *  \param value The value to divide each element by.
     *  \return A new vector which is divided by the scalar.
     */
    Vector2Impl<TypeT> operator/(double value) const
    {
        Vector2Impl<TypeT> ret(*this);
        ret /= value;
        return ret;
    }

    /*
     *  \fn sum
     *  \brief Adds all elements in a vector together into one value.
     *
     *  \return The sum of all the elements.
     */
    TypeT sum() const
    {
        return x + y;
    }

    /*
     *  \fn product
     *  \brief Multiples all the elements in a vector together.
     *
     *  \return The product of all the elements.
     */
    TypeT product() const
    {
        return x * y;
    }

    /*
     *  \fn sumSquares
     *  \brief Adds the squares of all the elements together.
     *
     *  \return The sum of all the squares of the elements.
     */
    TypeT sumSquares() const
    {
        return (x * x) + (y * y);
    }

    /*
     *  \fn Length
     *  \brief Calculates the magnitude of a vector. If you just need a
     *         comparison between two lengths then LengthSquared is slightly
     *         more efficient.
     *
     *  \return The length of the vector.
     */
    double length() const
    {
        return std::sqrt(static_cast<double>(sumSquares()));
    }

    /*
     *  \fn LengthSquared
     *  \brief Calculates the magnitude of the vector without the final square
     *         root. Use this instead of Length if you just need to compare
     *         two lengths.
     *
     *  \return The length of the vector squared.
     */
    double lengthSquared() const
    {
        return sumSquares();
    }

    /*
     *  \fn Normalize
     *  \brief Normalizes a vector so it has a length of 1.
     */
    void normalize()
    {
        (*this) /= length();
    }

    /*
     *  \var x
     *  \brief Represents the first element of the vector.
     */
    TypeT x;

    /*
     *  \var y
     *  \brief Represents the second element of the vector.
     */
    TypeT y;

    template<class ArchiveT>
    void serialize(ArchiveT& archive, const unsigned int version)
    {
        archive & x;
        archive & y;
    }
};

/*
 *  \fn Output Stream Operator
 *  \brief Prints a vector.
 *
 *  \tparam TypeT The element type of the vector.
 *  \param os The output stream.
 *  \param vector The vector to print.
 *  \return The updated stream.
 */
template <typename TypeT>
std::ostream& operator<<(std::ostream& os, const Vector2Impl<TypeT>& vector)
{
    os << "x=" << vector.x << " y=" << vector.y;
    return os;
}

typedef Vector2Impl<float> Vector2F;
typedef Vector2Impl<int32_t> Vector2I;
typedef Vector2Impl<uint32_t> Vector2U;
typedef Vector2Impl<double> Vector2D;
typedef Vector2Impl<float> Vector2;
}
}

#endif
