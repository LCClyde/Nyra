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
#include <nyra/emu/nes/Op6502Utils.h>
#include <nyra/emu/nes/Mode6502.h>

namespace nyra
{
namespace emu
{
namespace nes
{
//===========================================================================//
uint8_t shiftRight(uint8_t value,
                   bool rotate,
                   std::bitset<FLAG_SIZE>& statusRegister)
{
    uint8_t ret = value >> 1;
    if (rotate)
    {
        ret |= (statusRegister[CARRY] << 7);
    }
    statusRegister[CARRY] = (value & 0x01) != 0;
    return ret;
}

//===========================================================================//
uint8_t shiftLeft(uint8_t value,
                  bool rotate,
                  std::bitset<FLAG_SIZE>& statusRegister)
{
    uint8_t ret = value << 1;
    if (rotate)
    {
        ret |= static_cast<uint8_t>(
                statusRegister[CARRY]);
    }
    statusRegister[CARRY] = (value & 0x80) != 0;
    return ret;
}

//===========================================================================//
void compare(uint8_t value,
             uint8_t reg,
             std::bitset<FLAG_SIZE>& statusRegister)
{
    statusRegister[CARRY] = reg >= value;
    statusRegister[ZERO] = reg == value;
    statusRegister[SIGN] =
            static_cast<uint8_t>(reg - value) >= 0x80;
}

//===========================================================================//
void add(uint8_t value, CPURegisters& registers)
{
    const size_t sum = registers.accumulator + value +
            registers.statusRegister[CARRY];
    registers.statusRegister[OFLOW] =
            ((registers.accumulator ^ sum) & (value ^ sum) & 0x80) != 0;
    registers.statusRegister[CARRY] = (sum > 0xFF) != 0;
    setRegister(static_cast<uint8_t>(sum),
                registers.accumulator, registers.statusRegister);
}

//===========================================================================//
OpBranch::OpBranch(const std::string& name,
                   const std::string& extendedName,
                   uint8_t opcode) :
    OpCode(name, extendedName, opcode,
           0, 2, new ModeRelative())
{
}
}
}
}
