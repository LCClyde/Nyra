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
    Vector3() :
        x(this->mVec[0]),
        y(this->mVec[1]),
        z(this->mVec[2])
    {
    }

    /*
     *  \func Constructor
     *  \brief Sets up a vector with a single value set to every element.
     *
     *  \param value The desired starting value.
     */
    Vector3(const TypeT& value) :
        Vector3()
    {
        x = value;
        y = value;
        z = value;
    }

    /*
     *  \func Constructor
     *  \brief Creates a Vector3 from an x, y, and z values
     *
     *  \param x The desired x value
     *  \param y The desired y value
     *  \param z The desired z value
     */
    Vector3(const TypeT& x, const TypeT& y, const TypeT& z) :
        Vector3()
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /*
     *  \func Constructor
     *  \brief Creates a Vector3 from a Vector base object
     *
     *  \tparam OtherT The data type of the other vector
     *  \param vector The vector to copy
     */
    template <typename OtherT>
    Vector3(const Vector<OtherT, 3>& vector) :
    Vector3()
    {
        x = static_cast<TypeT>(vector[0]);
        y = static_cast<TypeT>(vector[1]);
        z = static_cast<TypeT>(vector[2]);
    }

    /*
     *  \func Constructor
     *  \brief Creates a Vector3 from another Vector of the same type. This is
     *         necessary because the templated version does not replace the default.
     *
     *  \param vector The vector to copy
     */
    Vector3(const Vector3<TypeT>& vector) :
        Vector3()
    {
        x = vector.x;
        y = vector.y;
        z = vector.z;
    }

    /*
     *  \func Assignment Operator
     *  \brief Assigns one vector to another
     *
     *  \param other The vector to assign
     *  \return The assigned vector
     */
    Vector3<TypeT>& operator=(const Vector3<TypeT>& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    /*
     *  \var x
     *  \brief The x axis.
     */
    TypeT& x;

    /*
     *  \var y
     *  \brief The y axis.
     */
    TypeT& y;

    /*
     *  \var z
     *  \brief The z axis.
     */
    TypeT& z;

private:
    friend std::ostream& operator<<(std::ostream& os,
                                    const Vector3<TypeT>& vector)
    {
        os << "x=" << vector.x << " y=" << vector.y << " z=" << vector.z;
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
