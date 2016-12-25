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
#include <nyra/emu/MemoryMap.h>
#include <nyra/emu/nes/Constants.h>
#include <nyra/emu/nes/CPUHelper.h>

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

//===========================================================================//
uint8_t shiftLeft(uint8_t value,
                  bool rotate,
                  std::bitset<FLAG_SIZE>& statusRegister);

//===========================================================================//
void compare(uint8_t value,
             uint8_t reg,
             std::bitset<FLAG_SIZE>& statusRegister);

//===========================================================================//
inline void setRegister(uint8_t value,
                        uint8_t& reg,
                        std::bitset<FLAG_SIZE>& statusRegister)
{
    statusRegister[SIGN] = (value >= 0x80);
    statusRegister[ZERO] = (value == 0);
    reg = value;
}

//===========================================================================//
void add(uint8_t value, CPURegisters& registers);

//===========================================================================//
inline void pushStack(uint8_t value,
                      MemoryMap& ram,
                      uint8_t& stackPointer)
{
    ram.writeWord(static_cast<size_t>(stackPointer | 0x100), value);
    --stackPointer;
}

//===========================================================================//
inline uint8_t popStack(MemoryMap& ram, uint8_t& stackPointer)
{
    ++stackPointer;
    return ram.readWord(static_cast<size_t>(stackPointer | 0x100));
}
}
}
}

#endif
