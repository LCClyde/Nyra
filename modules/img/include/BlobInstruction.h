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
#ifndef __NYRA_IMG_BLOB_INSTRUCTION_H__
#define __NYRA_IMG_BLOB_INSTRUCTION_H__

#include <nyra/math/Vector2.h>

namespace nyra
{
namespace img
{
/*
 *  \class BlobInstruction
 *  \brief Used to help create blob objects. A blob is created from this
 *         set of instructions. The starting point of the instruction is
 *         based on the previous instruction. The first instruction should
 *         be of type START.
 *         TODO: It may be better to use polymorphism here, but I don't
 *               know what the virtual function would be unless it assumes
 *               an implementation. Right now I would rather have the
 *               lower level object implement that logic.
 */
struct BlobInstruction
{
public:
    /*
     *  \type Type
     *  \brief Used to keep track of the instruction type.
     */
    enum Type
    {
        START,
        LINE,
        CURVE
    };

    /*
     *  \func Constructor
     *  \brief Sets up an default BlobInstruction.
     */
    BlobInstruction() = default;

    /*
     *  \func Constructor
     *  \brief Sets up the internal structure of the Blob Instruction.
     *
     *  \param type The type of instruction
     *  \param point The end point of the instruction
     *  \param bezier1 The starting bezier point
     *  \param bezier2 The end bezier point
     */
    BlobInstruction(Type type,
                    const math::Vector2F& point,
                    const math::Vector2F& bezier1,
                    const math::Vector2F& bezier2);

    /*
     *  \var type
     *  \brief The type of instruction
     */
    Type type;

    /*
     *  \var point
     *  \brief The ending point.
     */
    math::Vector2F point;

    /*
     *  \var bezier1
     *  \brief The starting bezier point
     */
    math::Vector2F bezier1;

    /*
     *  \var bezier2
     *  \brief The ending bezier point
     */
    math::Vector2F bezier2;
};

/*
 *  \func createBlobStart
 *  \brief Create a starting blob point.
 *
 *  \param point The starting point
 *  \return The created blob instruction
 */
BlobInstruction createBlobStart(const math::Vector2F& point);

/*
 *  \func createBlobLine
 *  \brief Create a line blob instruction
 *
 *  \param point The end point
 *  \return The created blob instruction
 */
BlobInstruction createBlobLine(const math::Vector2F& point);

/*
 *  \func createBlobCurve
 *  \brief Create a curve blob instruction
 *
 *  \param point The end point
 *  \param bezier1 The starting bezier point
 *  \param bezier2 The ending bezier point
 *  \return The created blob instruction
 */
BlobInstruction createBlobCurve(const math::Vector2F& point,
                                const math::Vector2F& bezier1,
                                const math::Vector2F& bezier2);
}
}

#endif
