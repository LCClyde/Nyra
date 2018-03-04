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
#ifndef __NYRA_EMU_RAM_H__
#define __NYRA_EMU_RAM_H__

#include <memory>
#include <nyra/emu/ROM.h>

namespace nyra
{
namespace emu
{
/*
 *  \class RAM
 *  \brief Exposes random access memory.
 *
 *  \tparam WordT The type to represent a single word
 */
template <typename WordT>
class RAM : public ROM<WordT>
{
public:
    /*
     *  \func Constructor (const buffer)
     *  \brief Creates a RAM object from an existing buffer. To allow the
     *         the buffer to be writeable this does a copy of the buffer.
     *
     *  \param buffer The buffer for the RAM.
     *  \param size The size of the buffer.
     */
    RAM(const WordT* buffer,
        size_t size) :
        ROM<WordT>(
                allocationTransitionBuffer(size, buffer), size, true),
        // This is a legitimate use of const cast because we know we passed in
        // a non const buffer we just created. The Memory makes it const but
        // we still need access to it with the modifiers we passed it in with.
        mRAMBuffer(const_cast<uint8_t*>(this->mBuffer))
    {
    }

    /*
     *  \func Constructor (buffer)
     *  \brief Creates a RAM object from an existing buffer. The RAM object
     *         does not take ownership unless you tell it to do so.
     *
     *  \param buffer The buffer for the RAM.
     *  \param size The size of the buffer.
     *  \param takeOwnership If this is true the RAM class will handle
     *         freeing this buffer.
     */
    RAM(WordT* buffer,
        size_t size,
        bool takeOwnership = false) :
        ROM<WordT>(buffer, size, takeOwnership),
        mRAMBuffer(buffer)

    {
    }

    /*
     *  \func Constructor (size)
     *  \brief Creates and allocates a new piece of memory. This can then be
     *         placed in a memory map to be used in a larger application.
     *         Memory will start zero'd out.
     *  \TODO: Make this threadsafe
     *
     *  \param size The size in bytes of the memory.
     */
    RAM(size_t size) :
        ROM<WordT>(
                allocationTransitionBuffer(size, nullptr), size, true),
        // This is a legitimate use of const cast because we know we passed in
        // a non const buffer we just created. The Memory makes it const but
        // we still need access to it with the modifiers we passed it in with.
        mRAMBuffer(const_cast<uint8_t*>(this->mBuffer))
    {
    }

    /*
     *  \func writeByte
     *  \brief Writes a single word into memory at any address.
     *
     *  \param address The address to write to word at.
     *  \param value The value to write.
     */
    void writeWord(size_t address,
                   WordT value) override
    {
        mRAMBuffer[address] = value;
    }

private:
    static uint8_t* allocationTransitionBuffer(size_t size,
                                               const WordT* copyFrom)
    {
        WordT* ret = new WordT[size];
        if (copyFrom)
        {
            std::copy(copyFrom, copyFrom + size, ret);
        }
        else
        {
            std::fill_n(ret, size, 0);
        }

        return ret;
    }

    WordT* const mRAMBuffer;
};
}
}

#endif
