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
#include <limits>
#include <nyra/test/Test.h>
#include <nyra/emu/nes/Mode6502.h>
#include <nyra/emu/MemoryMap.h>
#include <nyra/emu/RAM.h>

namespace
{
static const size_t MAX_VALUE = 64;
static const size_t MEM_SIZE = std::numeric_limits<uint16_t>::max() + 1;

uint8_t makeWord(size_t ii)
{
    return ii %  MAX_VALUE;
}

uint16_t makeLong(size_t ii)
{
    const uint8_t high = (ii + 1) % MAX_VALUE;
    const uint8_t low = ii % MAX_VALUE;
    const uint16_t results = ((high << 8) | low);
    return results;
}
}

namespace nyra
{
namespace emu
{
namespace nes
{
//===========================================================================//
class Test6502Modes : public ::testing::Test
{
public:
    void SetUp() override
    {
        memory.setMemoryBank(0, std::shared_ptr<emu::RAM<uint8_t> >(
                new emu::RAM<uint8_t>(MEM_SIZE)));
        memory.lockLookUpTable();

        for(size_t ii = 0; ii < MEM_SIZE; ++ii)
        {
            memory.writeWord(ii, makeWord(ii));
        }
    }

protected:
    emu::MemoryMap<uint8_t> memory;
    CPURegisters registers;
    CPUArgs args;
    CPUInfo info;
};

//===========================================================================//
TEST_F(Test6502Modes, Accumulator)
{

    ModeAccumulator mode;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        registers.accumulator = ii;
        mode(args, registers, memory, info);
        EXPECT_EQ(ii, mode.getArg());
        EXPECT_EQ(ii, mode.getValue());
    }

}

//===========================================================================//
TEST_F(Test6502Modes, AbsoluteNoOutput)
{
    ModeAbsolute<false> mode;

    for (size_t ii = 0; ii < 1024; ++ii)
    {
        args.darg = ii;
        mode(args, registers, memory, info);
        EXPECT_EQ(ii, mode.getArg());
        EXPECT_EQ(static_cast<size_t>(0), mode.getValue());
    }

}

//===========================================================================//
TEST_F(Test6502Modes, AbsoluteWithOutput)
{
    ModeAbsolute<true> mode;

    // Loop one less position to keep things in the valid range
    for (size_t ii = 0; ii < 1024; ++ii)
    {
        args.darg = ii;
        mode(args, registers, memory, info);
        EXPECT_EQ(ii, mode.getArg());
        EXPECT_EQ(makeWord(ii), mode.getValue());
    }

}

//===========================================================================//
TEST_F(Test6502Modes, Indirect)
{

    ModeIndirect mode;

    for (size_t ii = 0; ii < 1024; ++ii)
    {
        args.darg = ii;
        mode(args, registers, memory, info);
        const uint16_t expected = ((ii == 0xFF) ? MAX_VALUE - 1 : makeLong(ii));
        EXPECT_EQ(expected, mode.getArg());
    }
}

//===========================================================================//
TEST_F(Test6502Modes, IndirectX)
{
    ModeIndirectX mode;

    for (size_t ii = 0; ii < 256; ii += 7)
    {
        for (size_t x = 0; x < 256; ++x)
        {
            args.arg1 = ii;
            registers.xIndex = x;
            mode(args, registers, memory, info);
            const uint16_t expected = makeLong((ii + x) & 0xFF);
            EXPECT_EQ(expected, mode.getArg());
            EXPECT_EQ(makeWord(expected), mode.getValue());
        }
    }
}

//===========================================================================//
TEST_F(Test6502Modes, ZeroPageX)
{
    ModeZeroPageX mode;

    for (size_t ii = 0; ii < 256; ii += 7)
    {
        for (size_t x = 0; x < 256; ++x)
        {
            args.arg1 = ii;
            registers.xIndex = x;
            mode(args, registers, memory, info);
            const uint8_t expectedArg = (ii + x) & 0xFF;
            const uint8_t expectedVal = makeWord(expectedArg);
            EXPECT_EQ(expectedArg, mode.getArg());
            EXPECT_EQ(expectedVal, mode.getValue());
        }
    }
}

//===========================================================================//
TEST_F(Test6502Modes, ZeroPageY)
{
    ModeZeroPageY mode;

    for (size_t ii = 0; ii < 256; ii += 7)
    {
        for (size_t y = 0; y < 256; ++y)
        {
            args.arg1 = ii;
            registers.yIndex = y;
            mode(args, registers, memory, info);
            const uint8_t expectedArg = (ii + y) & 0xFF;
            const uint8_t expectedVal = makeWord(expectedArg);
            EXPECT_EQ(expectedArg, mode.getArg());
            EXPECT_EQ(expectedVal, mode.getValue());
        }
    }
}

//===========================================================================//
TEST_F(Test6502Modes, AbsoluteX)
{
    ModeAbsoluteX<false> mode;

    for (size_t ii = 0; ii < 1024; ii += 17)
    {
        for (size_t x = 0; x < 256; ++x)
        {
            args.darg = ii;
            registers.xIndex = x;
            mode(args, registers, memory, info);
            const uint16_t expected = ii + x;
            EXPECT_EQ(expected, mode.getArg());
            EXPECT_EQ(makeWord(expected), mode.getValue());
        }
    }
}

//===========================================================================//
TEST_F(Test6502Modes, AbsoluteY)
{
    ModeAbsoluteY<false> mode;

    for (size_t ii = 0; ii < 1024; ii += 17)
    {
        for (size_t y = 0; y < 256; ++y)
        {
            args.darg = ii;
            registers.yIndex = y;
            mode(args, registers, memory, info);
            const uint16_t expected = ii + y;
            EXPECT_EQ(expected, mode.getArg());
            EXPECT_EQ(makeWord(expected), mode.getValue());
        }
    }
}

//===========================================================================//
TEST_F(Test6502Modes, IndirectY)
{
    ModeIndirectY<false> mode;

    for (size_t ii = 0; ii < 256; ii += 7)
    {
        for (size_t y = 0; y < 256; ++y)
        {
            args.arg1 = ii;
            registers.yIndex = y;
            mode(args, registers, memory, info);
            const uint16_t expectedArg = makeLong(ii) + y;
            EXPECT_EQ(expectedArg, mode.getArg());
            EXPECT_EQ(makeWord(expectedArg), mode.getValue());
        }
    }
}

//===========================================================================//
TEST_F(Test6502Modes, Relative)
{
    ModeRelative mode;
    info.programCounter = 2048;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.arg1 = ii;
        mode(args, registers, memory, info);
        const uint16_t expected = static_cast<int8_t>(ii) + 2050;
        EXPECT_EQ(expected, mode.getArg());
    }
}

//===========================================================================//
TEST_F(Test6502Modes, ZeroPage)
{
    ModeZeroPage mode;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.arg1 = ii;
        mode(args, registers, memory, info);
        EXPECT_EQ(ii, mode.getArg());
        EXPECT_EQ(makeWord(ii), mode.getValue());
    }
}

//===========================================================================//
TEST_F(Test6502Modes, Immediate)
{
    ModeImmediate mode;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.arg1 = ii;
        mode(args, registers, memory, info);
        EXPECT_EQ(ii, mode.getArg());
        EXPECT_EQ(ii, mode.getValue());
    }
}

//===========================================================================//
TEST_F(Test6502Modes, Impied)
{
    ModeImplied mode;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.arg1 = ii;
        mode(args, registers, memory, info);
        EXPECT_EQ(static_cast<uint8_t>(0), mode.getArg());
        EXPECT_EQ(static_cast<uint8_t>(0), mode.getValue());
    }
}
}
}
}

NYRA_TEST()
