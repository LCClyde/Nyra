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
#include <nyra/emu/nes/Mode6502.h>

namespace nyra
{
namespace emu
{
namespace nes
{
//===========================================================================//
ModeAccumulator::ModeAccumulator() :
    Mode(false, false)
{
}

//===========================================================================//
ModeIndirect::ModeIndirect() :
    Mode(true, true),
    mOrigArg(0),
    mCorrectArg(0)
{
}

//===========================================================================//
void ModeIndirect::operator()(const CPUArgs& args,
                              const CPURegisters& ,
                              const emu::MemoryMap<uint8_t>& memory,
                              CPUInfo& )
{
    mOrigArg = args.darg;
    mCorrectArg = memory.readLong(mOrigArg);

    // There is a bug in 6502. If we try to get the address at 0xXXFF,
    // it does not go to the next digit properly.
    if (args.arg1 == 0xFF)
    {
        const uint8_t high = memory.readWord(args.darg);
        const uint16_t low = memory.readWord(args.arg2 << 8);
        mArg = (low << 8) | high;
    }
    else
    {
        mArg = mCorrectArg;
    }
}

//===========================================================================//
ModeIndirectX::ModeIndirectX() :
    Mode(true, false),
    mOrigArg(0),
    mModArg(0)
{
}

//===========================================================================//
ModeZeroPageN::ModeZeroPageN(char index) :
    Mode(true, false),
    mOrigArg(0),
    mIndex(index)
{
}

//===========================================================================//
ModeZeroPageX::ModeZeroPageX() :
    ModeZeroPageN('X')
{
}

//===========================================================================//
ModeZeroPageY::ModeZeroPageY() :
    ModeZeroPageN('Y')
{
}

//===========================================================================//
ModeRelative::ModeRelative() :
    Mode(true, false)
{
}

//===========================================================================//
ModeZeroPage::ModeZeroPage() :
    Mode(true, false)
{
}

//===========================================================================//
ModeImmediate::ModeImmediate() :
    Mode(true, false)
{
}

//===========================================================================//
ModeImplied::ModeImplied() :
    Mode(false, false)
{
}

//===========================================================================//
std::string ModeImplied::toString() const
{
    return "";
}
}
}
}
