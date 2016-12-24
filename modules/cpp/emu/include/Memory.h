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
#ifndef __NYRA_EMU_MEMORY_H__
#define __NYRA_EMU_MEMORY_H__

#include <stdexcept>
#include <nyra/emu/MemoryType.h>

namespace nyra
{
namespace emu
{
/*
 *  \class Memory
 *  \brief A generalized memory access class. Long term this is meant to
 *         be very reusable for any general memory configuration.
 *  TODO: Add endianess support
 *  TODO: Should this have logic to throw when an index is out of bounds?
 *
 *  \tparam WordT The type to represent a single word
 */
template <typename WordT>
class Memory
{
public:
    /*
     *  \type LongT
     *  \brief The double sized Word type.
     */
    typedef typename LongType<WordT>::LongT LongT;

    /*
     *  \func Constructor
     *  \brief Sets up the Memory object.
     *
     *  \param size The number of addresses in the Memory.
     */
    Memory(size_t size) :
        mSize(size)
    {
    }

    /*
     *  \func Destructor
     *  \brief Base class destructor
     */
    virtual ~Memory() = default;

    /*
     *  \func writeWord
     *  \brief Writes a single word into memory at any address.
     *
     *  \param address The address to write to to.
     *  \param value The 1 byte value to write.
     *  \throw If this is called from a ROM object, it will throw.
     */
    virtual void writeWord(size_t address,
                           WordT value)
    {
        throw std::runtime_error("Cannot write to ram");
    }

    /*
     *  \func readWord
     *  \brief Reads a single word from the memory structure.
     *         This cannot be const because some special registers
     *         modify flags during read.
     *
     *  \param address The address to read from.
     *  \return The value at the address
     */
    virtual WordT readWord(size_t address)
    {
        throw std::runtime_error("Cannot read word from ram");
    }

    /*
     *  \func readLong
     *  \brief - Reads a single long from the memory structure.
     *  TODO: This is setup for a little endian system. We need a big
     *        endian version as well.
     *
     *  \param address The address to read from.
     *  \return The value at the address
     */
    virtual LongT readLong(size_t address)
    {
        throw std::runtime_error("Cannot read long from ram");
    }

    /*
     *  \func getSize
     *  \brief Returns the size of the memory buffer.
     *
     *  \return The size of the memory in Words
     */
    inline size_t getSize() const
    {
        return mSize;
    }

protected:
    const size_t mSize;
};
}
}

#endif
