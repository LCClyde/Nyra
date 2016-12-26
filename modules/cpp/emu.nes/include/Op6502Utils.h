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
#ifndef __NYRA_EMU_NES_OP_6502_UTILS_H__
#define __NYRA_EMU_NES_OP_6502_UTILS_H__

#include <stdint.h>
#include <bitset>
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
 *  \func shiftRight
 *  \brief Shifts all bits in the value to the right.
 *
 *  \param value The value to shift.
 *  \param rotate Should the value wrap?
 *  \param statusRegister Sets the carry bit if necessary.
 */
uint8_t shiftRight(uint8_t value,
                   bool rotate,
                   std::bitset<FLAG_SIZE>& statusRegister);
/*
 *  \func shiftLeft
 *  \brief Shifts all bits in the value to the left.
 *
 *  \param value The value to shift.
 *  \param rotate Should the value wrap?
 *  \param statusRegister Sets the carry bit if necessary.
 */
uint8_t shiftLeft(uint8_t value,
                  bool rotate,
                  std::bitset<FLAG_SIZE>& statusRegister);

/*
 *  \func compare
 *  \brief Sets all flags used when comparing one value to another.
 *
 *  \param value The value to compare
 *  \param reg The register to compare against
 *  \statusRegister The register to set flags to.
 */
void compare(uint8_t value,
             uint8_t reg,
             std::bitset<FLAG_SIZE>& statusRegister);

/*
 *  \func setRegister
 *  \brief Sets flags in the status register based on the state of values
 *         going into a register.
 *
 *  \param value The value being set
 *  \param reg The register being set
 *  \param statusRegister The register to set flags to.
 */
inline void setRegister(uint8_t value,
                        uint8_t& reg,
                        std::bitset<FLAG_SIZE>& statusRegister)
{
    statusRegister[SIGN] = (value >= 0x80);
    statusRegister[ZERO] = (value == 0);
    reg = value;
}

/*
 *  \func add
 *  \brief Adds values to the accumulator
 *
 *  \param value The value to add
 *  \param registers The CPU registers. This will use the accumulator and
 *         modify the status register.
 */
void add(uint8_t value, CPURegisters& registers);

/*
 *  \func pushStack
 *  \brief Pushes a value to the stack
 *
 *  \param value The value to push
 *  \param ram The memory to write to
 *  \param stackPointer The location to write to. This will be decremented.
 */
inline void pushStack(uint8_t value,
                      MemoryMap& ram,
                      uint8_t& stackPointer)
{
    ram.writeWord(static_cast<size_t>(stackPointer | 0x100), value);
    --stackPointer;
}

/*
 *  \func popStack
 *  \brief Pulls a value off the stack
 *
 *  \param ram The memory to read from
 *  \param stackPointer The location to read. This will be incremented.
 *  \return The value that was on the stack.
 */
inline uint8_t popStack(MemoryMap& ram, uint8_t& stackPointer)
{
    ++stackPointer;
    return ram.readWord(static_cast<size_t>(stackPointer | 0x100));
}

//===========================================================================//
class OpBranch : public OpCode
{
public:
    OpBranch(const std::string& name,
             const std::string& extendedName,
             uint8_t opcode);

private:
    virtual bool branchArg(
            const std::bitset<8>& statusRegister) const = 0;

    void op(CPURegisters& registers,
            CPUInfo& info,
            MemoryMap& )
    {
        if (branchArg(registers.statusRegister))
        {
            info.programCounter = mMode->getArg();
            info.cycles += 3;
        }
        else
        {
            info.programCounter += 2;
        }
    }

};
}
}
}

#endif
