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
#include <nyra/img/BlobInstruction.h>

namespace nyra
{
namespace img
{
//===========================================================================//
BlobInstruction::BlobInstruction(BlobInstruction::Type type,
                                 const math::Vector2F& point,
                                 const math::Vector2F& bezier1,
                                 const math::Vector2F& bezier2) :
    type(type),
    point(point),
    bezier1(bezier1),
    bezier2(bezier2)
{
}

//===========================================================================//
BlobInstruction createBlobStart(const math::Vector2F& point)
{
    return BlobInstruction(BlobInstruction::START,
                           point,
                           math::Vector2F(0.0f, 0.0f),
                           math::Vector2F(0.0f, 0.0f));
}

//===========================================================================//
BlobInstruction createBlobLine(const math::Vector2F& point)
{
    return BlobInstruction(BlobInstruction::LINE,
                           point,
                           math::Vector2F(0.0f, 0.0f),
                           math::Vector2F(0.0f, 0.0f));
}

//===========================================================================//
BlobInstruction createBlobCurve(const math::Vector2F& point,
                                const math::Vector2F& bezier1,
                                const math::Vector2F& bezier2)
{
    return BlobInstruction(BlobInstruction::CURVE,
                           point,
                           bezier1,
                           bezier2);
}
}
}
