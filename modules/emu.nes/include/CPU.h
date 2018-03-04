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
#ifndef __NYRA_EMU_NES_CPU_H__
#define __NYRA_EMU_NES_CPU_H__

#include <stdint.h>
#include <nyra/emu/nes/Constants.h>
#include <nyra/emu/nes/CPUHelper.h>
#include <nyra/emu/nes/OpCode.h>

namespace nyra
{
namespace emu
{
namespace nes
{
/*
 *  \class CPU
 *  \brief Emulates the 6502 central processing unit. Run tick to process
 *         an opcode.
 *  TODO: This could be generalized for any CPU. It would need to be setup
 *        to allow the number of bits to be set, probably through a template.
 */
class CPU
{
public:
    /*
     *  \func Constructor (address)
     *  \brief Creates a CPU object with a starting memory address.
     *
     *  \param startAddress The location to start reading opcodes from.
     *  TODO: Should this also have a version that takes in a MemoryMap and
     *        resolves the startAddress itself?
     */
    CPU(uint16_t startAddress);

    /*
     *  \func tick
     *  \brief Processes a single opcode.
     *
     *  \param memory All the available memory as swappable banks.
     */
    void processScanline(MemoryMap& memory);

    /*
     *  \func getInfo
     *  \brief Returns the CPU implementation info.
     *
     *  \return The CPUInfo object
     */
    inline const CPUInfo& getInfo() const
    {
        return mInfo;
    }

    /*
     *  \func getInfo
     *  \brief Returns the CPU implementation info.
     *
     *  \return The CPUInfo object
     */
    inline CPUInfo& getInfo()
    {
        return mInfo;
    }

private:
    void getOpInfo(size_t address,
                   MemoryMap& memory)
    {
        mArgs.opcode = memory.readWord(address);
        mArgs.arg1 = memory.readWord(address + 1);
        mArgs.arg2 = memory.readWord(address + 2);
        mArgs.darg = memory.readLong(address + 1);
    }

    static const size_t INTERRUPT_OPCODE;
    CPURegisters mRegisters;
    CPUInfo mInfo;
    CPUArgs mArgs;
    OpCodeArray mOpCodes;
};
}
}
}

#endif
