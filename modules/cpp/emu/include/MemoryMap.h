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
#ifndef __NYRA_EMU_MEMORY_MAP_H__
#define __NYRA_EMU_MEMORY_MAP_H__

#include <nyra/emu/Memory.h>

namespace nyra
{
namespace emu
{
/*
 *  \class MemoryMap
 *  \brief Holds banks of memory which can then be read as it it was one
 *         contiguous buffer.
 */
template <typename WordT>
class MemoryMap
{
private:
    struct MemoryHandle
    {
        MemoryHandle(size_t offset, std::shared_ptr<Memory<WordT> > memory) :
            memory(memory),
            offset(offset)
        {
            if (!memory.get())
            {
                throw std::runtime_error("Invalid memory bank.");
            }
        }

        inline bool operator<(const MemoryHandle& other) const
        {
            return offset < other.offset;
        }

        // Non const to implement default constructors.
        // The higher level value will be const so this is okay.
        // TODO: Make these const and manually implement, move, copy,
        //       and assignment.
        std::shared_ptr<Memory<WordT> > memory;
        size_t offset;
    };

public:
    /*
     *  \func setMemoryBank
     *  \brief Adds a memory bank into the map. It is the user's job to
     *         ensure banks do not cross. If they do the behavior is
     *         undefined.
     *
     *  \param memoryOffset The starting address of the memory.
     *  \param memory The memory object that will go into this address.
     */
    inline void setMemoryBank(size_t memoryOffset,
                              std::shared_ptr<Memory<WordT> > memory)
    {
        mMemory.push_back(MemoryHandle(memoryOffset, memory));
    }

    /*
     *  \func writeWord
     *  \brief Write a single byte into MemoryMap.
     *
     *  \param address The global address to write to
     *  \param value The value to write.
     */
    inline void writeWord(size_t address, WordT value)
    {
        getMemoryBank(address).memory->writeWord(address, value);
    }

    /*
     *  \func readWord
     *  \brief Reads a single word from global memory.
     *
     *  \param address The global address to read from.
     *  \return The value at that address.
     */
    inline WordT readWord(size_t address) const
    {
        return getMemoryBank(address).memory->readWord(address);
    }

    /*
     *  \func readLong
     *  \brief Reads a single long from global memory. This properly
     *         handles reaching the end of a bank.
     *
     *  \param address The global address to read from.
     *  \return The value at that address.
     */
    typename Memory<WordT>::LongT readLong(size_t address) const
    {
        size_t modAddress = address;
        const MemoryHandle* handle = &getMemoryBank(modAddress);
        const uint16_t ret = handle->memory->readByte(modAddress);

        // Check if this is zero page
        // TODO: Is this logic correct for VRAM as well?
        if (address >= 0x0100)
        {
            modAddress = address + 1;
            handle = &getMemoryBank(modAddress);
        }
        else
        {
            modAddress = (modAddress + 1) & 0xFF;
        }
        return (handle->memory->readByte(modAddress) << 8) | ret;
    }

    /*
     *  \func lockLookUpTable
     *  \brief This locks in the memory banks into a look up table. This must
     *         be called after the banks have been initialized.
     *         TODO: Remove this and find a way to handle everything
     *         internally.
     */
    void lockLookUpTable()
    {
        mLookUpTable.clear();
        std::sort(mMemory.begin(), mMemory.end());

        for (size_t ii = 0; ii < mMemory.size(); ++ii)
        {
            for (size_t jj = 0; jj < mMemory[ii].memory->getSize(); ++jj)
            {
                mLookUpTable.push_back(ii);
            }
        }
    }

private:
    const MemoryHandle& getMemoryBank(size_t& address) const
    {
        const MemoryHandle& handle = mMemory[mLookUpTable[address]];
        address -= handle.offset;
        return handle;
    }

    std::vector<MemoryHandle> mMemory;
    std::vector<size_t> mLookUpTable;
};
}
}

#endif
