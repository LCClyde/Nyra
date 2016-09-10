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

#include <nyra/math/Vector.h>

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
    Vector2() = default;

    Vector2(const TypeT& x, const TypeT& y)
    {
        this->x() = x;
        this->y() = y;
    }

    /*
     *  \var x
     *  \brief Represents the first element of the vector.
     */
    TypeT& x()
    {
        return (*this)[0];
    }

    const TypeT& x() const
    {
        return (*this)[0];
    }

    /*
     *  \var y
     *  \brief Represents the second element of the vector.
     */
    TypeT& y()
    {
        return (*this)[1];
    }

    const TypeT& y() const
    {
        return (*this)[1];
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
std::ostream& operator<<(std::ostream& os, const Vector2<TypeT>& vector)
{
    os << "x=" << vector.x() << " y=" << vector.y();
    return os;
}

typedef Vector2<float> Vector2F;
typedef Vector2<int32_t> Vector2I;
typedef Vector2<uint32_t> Vector2U;
typedef Vector2<double> Vector2D;
}
}

#endif
