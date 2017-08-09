/*
 * Copyright (c) 2017 Clyde Stanfield
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
#ifndef __NYRA_MEM_BUFFER_2D_H__
#define __NYRA_MEM_BUFFER_2D_H__

#include <vector>
#include <nyra/math/Vector2.h>

namespace nyra
{
namespace mem
{
/*
 *  \class Buffer2D
 *  \brief A buffer that can hold a two dimensional array of a set size.
 *
 *  \tparam TypeT The buffer element type..
 */
template <typename TypeT>
class Buffer2D
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an empty buffer.
     *
     *  \param size The size of the buffer. x is columns, y is rows.
     */
    Buffer2D(const math::Vector2U& size) :
        mSize(size),
        mBuffer(size.product(), 0)
    {
    }

    /*
     *  \func Buffer2D
     *  \brief Creates a buffer from a static 2D array.
     *
     *  \param list The array to initialize from.
     */
    Buffer2D(const std::vector<std::vector<TypeT>>& list) :
        Buffer2D(math::Vector2U(list.begin()->size(), list.size()))
    {
        for (size_t ii = 0; ii < getNumRows(); ++ii)
        {
            for (size_t jj = 0; jj < getNumCols(); ++jj)
            {
                (*this)(jj, ii) = list[ii][jj];
            }
        }
    }

    /*
     *  \func Functor
     *  \brief Gets a value from the buffer.
     *
     *  \param x The x dimension
     *  \param y The y dimension
     *  \return The element
     */
    TypeT& operator()(size_t x, size_t y)
    {
        return mBuffer.at(y * mSize.x + x);
    }

    /*
     *  \func Functor
     *  \brief Gets a value from the buffer.
     *
     *  \param x The x dimension
     *  \param y The y dimension
     *  \return The element
     */
    const TypeT& operator()(size_t x, size_t y) const
    {
        return mBuffer.at(y * mSize.x + x);
    }

    /*
     *  \func Functor
     *  \brief Gets a value from the buffer.
     *
     *  \param index The 1 dimensional index
     *  \return The element
     */
    TypeT& operator()(size_t index)
    {
        return mBuffer[index];
    }

    /*
     *  \func Functor
     *  \brief Gets a value from the buffer.
     *
     *  \param index The 1 dimensional index
     *  \return The element
     */
    const TypeT& operator()(size_t index) const
    {
        return mBuffer[index];
    }

    /*
     *  \func getSize
     *  \brief Gets the size of the buffer
     *
     *  \return The size
     */
    const math::Vector2U& getSize() const
    {
        return mSize;
    }

    /*
     *  \func getNumRows
     *  \brief Gets the number of rows in the buffer
     *
     *  \return The number of rows
     */
    size_t getNumRows() const
    {
        return mSize.y;
    }

    /*
     *  \func getNumCols
     *  \brief Gets the number of columns in the buffer
     *
     *  \return The number of columns
     */
    size_t getNumCols() const
    {
        return mSize.x;
    }

private:
    const math::Vector2U mSize;
    std::vector<TypeT> mBuffer;
};
}
}

#endif
