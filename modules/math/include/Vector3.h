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
#ifndef __NYRA_MATH_VECTOR_3_H__
#define __NYRA_MATH_VECTOR_3_H__

#include <nyra/math/Vector.h>

namespace nyra
{
namespace math
{
/*
 *  \class Vector3
 *  \brief A three dimensional vector. This can be used for 3D pos, rot, scale.
 *         Common types are typenamed for easier use.
 *
 *  \tparam TypeT The data type for elements.
 */
template <typename TypeT>
class Vector3 : public Vector<TypeT, 3>
{
public:
    /*
     *  \func Constructor
     *  \brief Creates a default Vector3
     */
    Vector3() = default;

    /*
     *  \func Constructor
     *  \brief Sets up a vector with a single value set to every element.
     *
     *  \param value The desired starting value.
     */
    Vector3(const TypeT& value)
    {
        this->x() = value;
        this->y() = value;
        this->z() = value;
    }

    /*
     *  \func Constructor
     *  \brief Creates a Vector3 from an x, y, and z values
     *
     *  \param x The desired x value
     *  \param y The desired y value
     *  \param z The desired z value
     */
    Vector3(const TypeT& x, const TypeT& y, const TypeT& z)
    {
        this->x() = x;
        this->y() = y;
        this->z() = z;
    }

    /*
     *  \func Constructor
     *  \brief Creates a Vector3 from a Vector base object
     *
     *  \tparam OtherT The data type of the other vector
     *  \param vector The vector to copy
     */
    template <typename OtherT>
    Vector3(const Vector<OtherT, 3>& vector)
    {
        x() = static_cast<TypeT>(vector[0]);
        y() = static_cast<TypeT>(vector[1]);
        z() = static_cast<TypeT>(vector[2]);
    }

    /*
     *  \func x
     *  \brief Represents the first element of the vector.
     *
     *  \return The x value
     */
    TypeT& x()
    {
        return (*this)[0];
    }

    /*
     *  \func x
     *  \brief Represents the first element of the vector.
     *
     *  \return The x value
     */
    const TypeT& x() const
    {
        return (*this)[0];
    }

    /*
     *  \func y
     *  \brief Represents the second element of the vector.
     *
     *  \return The y value
     */
    TypeT& y()
    {
        return (*this)[1];
    }

    /*
     *  \func y
     *  \brief Represents the second element of the vector.
     *
     *  \return The y value
     */
    const TypeT& y() const
    {
        return (*this)[1];
    }

    /*
     *  \func z
     *  \brief Represents the third element of the vector.
     *
     *  \return The z value
     */
    TypeT& z()
    {
        return (*this)[2];
    }

    /*
     *  \func z
     *  \brief Represents the third element of the vector.
     *
     *  \return The z value
     */
    const TypeT& z() const
    {
        return (*this)[2];
    }

private:
    friend std::ostream& operator<<(std::ostream& os,
                                    const Vector3<TypeT>& vector)
    {
        os << "x=" << vector.x() << " y=" << vector.y() << " z=" << vector.z();
        return os;
    }
};

typedef Vector3<float> Vector3F;
typedef Vector3<int32_t> Vector3I;
typedef Vector3<uint32_t> Vector3U;
typedef Vector3<double> Vector3D;
}
}

#endif
