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
#ifndef __NYRA_MATH_VECTOR_2_H__
#define __NYRA_MATH_VECTOR_2_H__

#include <nyra/math/Vector.h>
#include <iostream>

namespace nyra
{
namespace math
{
/*
 *  \class Vector2
 *  \brief A two dimensional vector. This can be used for 2D position or scale.
 *         Common types are typenamed for easier use.
 *
 *  \tparam TypeT The data type for elements.
 */
template <typename TypeT>
class Vector2 : public Vector<TypeT, 2>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a default Vector2
     */
    Vector2() :
        x(this->mVec[0]),
        y(this->mVec[1])
    {
    }

    /*
     *  \func Constructor
     *  \brief Sets up a vector with a single value set to every element.
     *
     *  \param value The desired starting value.
     */
    Vector2(const TypeT& value) :
        Vector2()
    {
        x = value;
        y = value;
    }

    /*
     *  \func Constructor
     *  \brief Creates a Vector2 from an x and y value
     *
     *  \param x The desired x value
     *  \param y The desired y value
     */
    Vector2(const TypeT& x, const TypeT& y) :
        Vector2()
    {
        this->x = x;
        this->y = y;
    }

    /*
     *  \func Constructor
     *  \brief Creates a Vector2 from a Vector base object
     *
     *  \tparam OtherT The data type of the other vector
     *  \param vector The vector to copy
     */
    template <typename OtherT>
    Vector2(const Vector<OtherT, 2>& vector) :
        Vector2()
    {
        x = static_cast<TypeT>(vector[0]);
        y = static_cast<TypeT>(vector[1]);
    }

    /*
     *  \func Constructor
     *  \brief Creates a Vector2 from another Vector of the same type. This is
     *         necessary because the templated version does not replace the default.
     *
     *  \param vector The vector to copy
     */
    Vector2(const Vector2<TypeT>& vector) :
        Vector2()
    {
        x = vector.x;
        y = vector.y;
    }

    /*
     *  \func Assignment Operator
     *  \brief Assigns one vector to another
     *
     *  \param other The vector to assign
     *  \return The assigned vector
     */
    Vector2<TypeT>& operator=(const Vector2<TypeT>& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    /*
     *  \var x
     *  \brief The x axis. By convention this can also mean either
     *         columns or width.
     */
    TypeT& x;

    /*
     *  \var y
     *  \brief The y axis. By convention this can also mean either
     *         rows or height.
     */
    TypeT& y;

private:
    friend std::ostream& operator<<(std::ostream& os,
                                    const Vector2<TypeT>& vector)
    {
        os << "x=" << vector.x << " y=" << vector.y;
        return os;
    }
};

typedef Vector2<float> Vector2F;
typedef Vector2<int32_t> Vector2I;
typedef Vector2<uint32_t> Vector2U;
typedef Vector2<double> Vector2D;
}
}

#endif
