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
#include <nyra/math/Transform2D.h>

namespace nyra
{
namespace math
{
//===========================================================================//
Transform2D::Transform2D() :
    mScale(1.0f, 1.0f),
    mPivot(0.5f, 0.5f),
    mRotation(0.0f),
    mDirty(false)
{
}

//===========================================================================//
void Transform2D::update(const Transform2D& parent)
{
    if (mDirty)
    {
        mLocal.transform(mPosition,
                         mScale,
                         mRotation,
                         Vector2F(mPivot.x() * mSize.x(),
                                  mPivot.y() * mSize.y()));
    }

    // We could optimize out this matrix transform but you can get into
    // strange situations where it you optimize it out by accident if you
    // change the parent to a stable matrix.
    mGlobal = mLocal * parent.mGlobal;
    mDirty = false;
}

//===========================================================================//
std::ostream& operator<<(std::ostream& os,
                         const Transform2D& transform)
{
    os << "Position: " << transform.getPosition() << "\n"
       << "Scale: " << transform.getScale() << "\n"
       << "Rotation: " << transform.getRotation() << "\n"
       << "Pivot: " << transform.getPivot();
    return os;
}
}
}
