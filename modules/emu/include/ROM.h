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
#ifndef __NYRA_EMU_ROM_H__
#define __NYRA_EMU_ROM_H__

#include <memory>
#include <nyra/emu/Memory.h>

namespace nyra
{
namespace emu
{
/*
 *  \class ROM
 *  \brief Exposes read only memory.
 *
 *  \tparam WordT The type to represent a single word
 */
template <typename WordT>
class ROM : public Memory<WordT>
{
public:
    /*
     *  \func Constructor (buffer)
     *  \brief Creates a Memory object from an existing buffer. The object
     *         does not take ownership unless you tell it to do so.
     *         This will accept the buffer as is. It will not modify any
     *         values until explicitly told to do so.
     *
     *  \param buffer The buffer of memory.
     *  \param size The size of the buffer.
     *  \param takeOwnership If this is true the ROM class will handle
     *         freeing this buffer.
     */
    ROM(const WordT* buffer,
        size_t size,
        bool takeOwnership = false) :
        Memory<WordT>(size),
        mBufferInternal(takeOwnership ? buffer : nullptr),
        mBuffer(buffer)
    {
    }

    /*
     *  \func Destructor
     *  \brief Base class destructor
     */
    virtual ~ROM() = default;

    /*
     *  \func readWord
     *  \brief Reads a single word from the memory structure.
     *         This cannot be const because some special registers
     *         modify flags during read.
     *
     *  \param address The address to read from.
     *  \return The value at the address
     */
    WordT readWord(size_t address) override
    {
        return mBuffer[address];
    }

    /*
     *  \func getAddressRef
     *  \brief Gets the reference at the address.
     *
     *  \param address The address to read from.
     *  \return The reference at the address
     */
    const WordT& getAddressRef(size_t address) const
    {
        return mBuffer[address];
    }

protected:
    const std::unique_ptr<const WordT[]> mBufferInternal;
    const WordT* const mBuffer;
};
}
}

#endif
