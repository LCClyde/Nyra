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
#include <nyra/test/Test.h>
#include <nyra/emu/nes/Op6502.h>

namespace
{
static const size_t MAX_VALUE = 32;
static const size_t MEM_SIZE = std::numeric_limits<uint16_t>::max() + 1;

uint8_t makeWord(size_t ii)
{
    return ii %  MAX_VALUE;
}
}

namespace nyra
{
namespace emu
{
namespace nes
{
//===========================================================================//
class MockMode : public Mode
{
public:
    MockMode() :
        Mode(false, false)
    {
    }

    void operator()(const CPUArgs& args,
                    const CPURegisters& ,
                    const emu::MemoryMap<uint8_t>& ,
                    CPUInfo& )
    {
        mArg = args.darg;
        mValue = args.darg;
    }
};

//===========================================================================//
class Test6502Ops : public ::testing::Test
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
TEST_F(Test6502Ops, NUL)
{
    OpNUL op(0);
    EXPECT_ANY_THROW(op(args, registers, info, memory));
}

//===========================================================================//
TEST_F(Test6502Ops, JMP)
{
    OpJMP<MockMode> op(0, 0);

    for (size_t ii = 0; ii < 1024; ++ii)
    {
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(ii, info.programCounter);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, LDX)
{
    OpLDX<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(ii, registers.xIndex);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, LDY)
{
    OpLDY<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(ii, registers.yIndex);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, LDA)
{
    OpLDA<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(ii, registers.accumulator);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, LSR)
{
    OpLSR<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(ii >> 1), memory.readWord(ii));
    }
}

//===========================================================================//
TEST_F(Test6502Ops, ASL)
{
    OpASL<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(ii << 1), memory.readWord(ii));
    }
}

//===========================================================================//
TEST_F(Test6502Ops, ROR)
{
    OpROR<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.darg = ii;
        registers.statusRegister[CARRY] = true;
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(ii >> 1) + 128, memory.readWord(ii));
    }
}

//===========================================================================//
TEST_F(Test6502Ops, ROL)
{
    OpROL<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.darg = ii;
        registers.statusRegister[CARRY] = true;
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(ii << 1) + 1, memory.readWord(ii));
    }
}

//===========================================================================//
TEST_F(Test6502Ops, STA)
{
    OpSTA<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 1024; ++ii)
    {
        registers.accumulator = ii;
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(ii), memory.readWord(ii));
    }
}

//===========================================================================//
TEST_F(Test6502Ops, STX)
{
    OpSTX<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 1024; ++ii)
    {
        registers.xIndex = ii;
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(ii), memory.readWord(ii));
    }
}

//===========================================================================//
TEST_F(Test6502Ops, STY)
{
    OpSTY<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 1024; ++ii)
    {
        registers.yIndex = ii;
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(ii), memory.readWord(ii));
    }
}

//===========================================================================//
TEST_F(Test6502Ops, JSR_RTS)
{
    OpJSR jsr;
    OpRTS rts;
    registers.stackPointer = 0xFF;

    for (size_t ii = 0; ii < 1024; ++ii)
    {
        args.darg = ii;
        info.programCounter = ii + 1000;
        jsr(args, registers, info, memory);
        EXPECT_EQ(ii, info.programCounter);
        rts(args, registers, info, memory);
        EXPECT_EQ(ii + 1000 + 3, info.programCounter);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, JMI_RTI)
{
    OpJMI jmi;
    OpRTI rti;
    registers.stackPointer = 0xFF;

    for (size_t ii = 0; ii < 1024; ++ii)
    {
        args.darg = ii;
        info.programCounter = ii + 1000;
        jmi(args, registers, info, memory);
        EXPECT_EQ(ii, info.programCounter);
        rti(args, registers, info, memory);
        EXPECT_EQ(ii + 1000, info.programCounter);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, NOP)
{
    OpNOP op;
    EXPECT_NO_THROW(op(args, registers, info, memory));
}

//===========================================================================//
TEST_F(Test6502Ops, INY)
{
    OpINY op;
    registers.yIndex = 0;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(ii + 1), registers.yIndex);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, INX)
{
    OpINX op;
    registers.xIndex = 0;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(ii + 1), registers.xIndex);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, INC)
{
    OpINC<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(ii + 1), memory.readWord(ii));
    }
}

//===========================================================================//
TEST_F(Test6502Ops, DEC)
{
    OpDEC<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(ii - 1), memory.readWord(ii));
    }
}

//===========================================================================//
TEST_F(Test6502Ops, DEY)
{
    OpDEY op;
    registers.yIndex = 255;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(254 - ii), registers.yIndex);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, DEX)
{
    OpDEX op;
    registers.xIndex = 255;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        op(args, registers, info, memory);
        EXPECT_EQ(static_cast<uint8_t>(254 - ii), registers.xIndex);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, TAX)
{
    OpTAX op;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        registers.accumulator = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(ii, registers.xIndex);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, TXA)
{
    OpTXA op;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        registers.xIndex = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(ii, registers.accumulator);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, TAY)
{
    OpTAY op;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        registers.accumulator = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(ii, registers.yIndex);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, TYA)
{
    OpTYA op;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        registers.yIndex = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(ii, registers.accumulator);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, SEC)
{
    OpSEC op;
    EXPECT_FALSE(registers.statusRegister[CARRY]);
    op(args, registers, info, memory);
    EXPECT_TRUE(registers.statusRegister[CARRY]);
}

//===========================================================================//
TEST_F(Test6502Ops, CLC)
{
    OpCLC op;
    registers.statusRegister[CARRY] = true;
    EXPECT_TRUE(registers.statusRegister[CARRY]);
    op(args, registers, info, memory);
    EXPECT_FALSE(registers.statusRegister[CARRY]);
}

//===========================================================================//
TEST_F(Test6502Ops, CLV)
{
    OpCLV op;
    registers.statusRegister[OFLOW] = true;
    EXPECT_TRUE(registers.statusRegister[OFLOW]);
    op(args, registers, info, memory);
    EXPECT_FALSE(registers.statusRegister[OFLOW]);
}

//===========================================================================//
TEST_F(Test6502Ops, SEI)
{
    OpSEI op;
    registers.statusRegister[INTERRUPT] = false;
    EXPECT_FALSE(registers.statusRegister[INTERRUPT]);
    op(args, registers, info, memory);
    EXPECT_TRUE(registers.statusRegister[INTERRUPT]);
}

//===========================================================================//
TEST_F(Test6502Ops, SED)
{
    OpSED op;
    EXPECT_FALSE(registers.statusRegister[DECIMAL]);
    op(args, registers, info, memory);
    EXPECT_TRUE(registers.statusRegister[DECIMAL]);
}

//===========================================================================//
TEST_F(Test6502Ops, CLD)
{
    OpCLD op;
    registers.statusRegister[DECIMAL] = true;
    EXPECT_TRUE(registers.statusRegister[DECIMAL]);
    op(args, registers, info, memory);
    EXPECT_FALSE(registers.statusRegister[DECIMAL]);
}

//===========================================================================//
TEST_F(Test6502Ops, TSX)
{
    OpTSX op;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        registers.stackPointer = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(ii, registers.xIndex);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, TXS)
{
    OpTXS op;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        registers.xIndex = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(ii, registers.stackPointer);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, PLA)
{
    OpPLA op;
    registers.stackPointer = 0xFF;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        pushStack(ii, memory, registers.stackPointer);
        op(args, registers, info, memory);
        EXPECT_EQ(ii, registers.accumulator);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, PHA)
{
    OpPHA op;
    registers.stackPointer = 0xFF;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        registers.accumulator = ii;
        op(args, registers, info, memory);
        EXPECT_EQ(ii, popStack(memory, registers.stackPointer));
    }
}

//===========================================================================//
TEST_F(Test6502Ops, PLP)
{
    OpPLP op;
    registers.stackPointer = 0xFF;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        pushStack(ii, memory, registers.stackPointer);
        op(args, registers, info, memory);
        const uint8_t expected = ((ii | (1 << IGNORE)) & ~(1 << STACK));
        EXPECT_EQ(expected, registers.statusRegister.to_ulong());
    }
}

//===========================================================================//
TEST_F(Test6502Ops, PHP)
{
    OpPHP op;
    registers.stackPointer = 0xFF;

    for (size_t ii = 0; ii < 256; ++ii)
    {
        registers.statusRegister = ii;\
        op(args, registers, info, memory);
        const uint8_t expected =  ii | (1 << STACK);
        EXPECT_EQ(expected, popStack(memory, registers.stackPointer));
    }
}

//===========================================================================//
TEST_F(Test6502Ops, BCS)
{
    OpBCS op;

    registers.statusRegister[CARRY] = false;
    info.programCounter = 1000;
    args.arg1 = 100;
    op(args, registers, info, memory);
    EXPECT_EQ(1002, info.programCounter);

    registers.statusRegister[CARRY] = true;
    info.programCounter = 1000;
    op(args, registers, info, memory);
    EXPECT_EQ(1102, info.programCounter);
}

//===========================================================================//
TEST_F(Test6502Ops, BEQ)
{
    OpBEQ op;

    registers.statusRegister[ZERO] = false;
    info.programCounter = 1000;
    args.arg1 = 100;
    op(args, registers, info, memory);
    EXPECT_EQ(1002, info.programCounter);

    registers.statusRegister[ZERO] = true;
    info.programCounter = 1000;
    op(args, registers, info, memory);
    EXPECT_EQ(1102, info.programCounter);
}

//===========================================================================//
TEST_F(Test6502Ops, BNE)
{
    OpBNE op;

    registers.statusRegister[ZERO] = true;
    info.programCounter = 1000;
    args.arg1 = 100;
    op(args, registers, info, memory);
    EXPECT_EQ(1002, info.programCounter);

    registers.statusRegister[ZERO] = false;
    info.programCounter = 1000;
    op(args, registers, info, memory);
    EXPECT_EQ(1102, info.programCounter);
}

//===========================================================================//
TEST_F(Test6502Ops, BCC)
{
    OpBCC op;

    registers.statusRegister[CARRY] = true;
    info.programCounter = 1000;
    args.arg1 = 100;
    op(args, registers, info, memory);
    EXPECT_EQ(1002, info.programCounter);

    registers.statusRegister[CARRY] = false;
    info.programCounter = 1000;
    op(args, registers, info, memory);
    EXPECT_EQ(1102, info.programCounter);
}

//===========================================================================//
TEST_F(Test6502Ops, BVS)
{
    OpBVS op;

    registers.statusRegister[OFLOW] = false;
    info.programCounter = 1000;
    args.arg1 = 100;
    op(args, registers, info, memory);
    EXPECT_EQ(1002, info.programCounter);

    registers.statusRegister[OFLOW] = true;
    info.programCounter = 1000;
    op(args, registers, info, memory);
    EXPECT_EQ(1102, info.programCounter);
}

//===========================================================================//
TEST_F(Test6502Ops, BVC)
{
    OpBVC op;

    registers.statusRegister[OFLOW] = true;
    info.programCounter = 1000;
    args.arg1 = 100;
    op(args, registers, info, memory);
    EXPECT_EQ(1002, info.programCounter);

    registers.statusRegister[OFLOW] = false;
    info.programCounter = 1000;
    op(args, registers, info, memory);
    EXPECT_EQ(1102, info.programCounter);
}

//===========================================================================//
TEST_F(Test6502Ops, BPL)
{
    OpBPL op;

    registers.statusRegister[SIGN] = true;
    info.programCounter = 1000;
    args.arg1 = 100;
    op(args, registers, info, memory);
    EXPECT_EQ(1002, info.programCounter);

    registers.statusRegister[SIGN] = false;
    info.programCounter = 1000;
    op(args, registers, info, memory);
    EXPECT_EQ(1102, info.programCounter);
}

//===========================================================================//
TEST_F(Test6502Ops, BMI)
{
    OpBMI op;

    registers.statusRegister[SIGN] = false;
    info.programCounter = 1000;
    args.arg1 = 100;
    op(args, registers, info, memory);
    EXPECT_EQ(1002, info.programCounter);

    registers.statusRegister[SIGN] = true;
    info.programCounter = 1000;
    op(args, registers, info, memory);
    EXPECT_EQ(1102, info.programCounter);
}

//===========================================================================//
TEST_F(Test6502Ops, BIT)
{
    OpBIT<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        args.darg = ii;
        op(args, registers, info, memory);
        EXPECT_EQ((ii & registers.accumulator) == 0,
                  registers.statusRegister[ZERO]);
        EXPECT_EQ((ii & (1 << SIGN)) != 0, registers.statusRegister[SIGN]);
        EXPECT_EQ((ii & (1 << OFLOW)) != 0, registers.statusRegister[OFLOW]);
    }
}

//===========================================================================//
TEST_F(Test6502Ops, CMP)
{
    OpCMP<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        for (size_t jj = 0; jj < 256; ++jj)
        {
            args.darg = jj;
            registers.accumulator = ii;
            op(args, registers, info, memory);

            EXPECT_EQ(ii == jj, registers.statusRegister[ZERO]);
            EXPECT_EQ(ii >= jj, registers.statusRegister[CARRY]);
            EXPECT_EQ(static_cast<int8_t>(ii - jj) < 0,
                      registers.statusRegister[SIGN]);
        }
    }
}

//===========================================================================//
TEST_F(Test6502Ops, CPY)
{
    OpCPY<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        for (size_t jj = 0; jj < 256; ++jj)
        {
            args.darg = jj;
            registers.yIndex = ii;
            op(args, registers, info, memory);

            EXPECT_EQ(ii == jj, registers.statusRegister[ZERO]);
            EXPECT_EQ(ii >= jj, registers.statusRegister[CARRY]);
            EXPECT_EQ(static_cast<int8_t>(ii - jj) < 0,
                      registers.statusRegister[SIGN]);
        }
    }
}

//===========================================================================//
TEST_F(Test6502Ops, CPX)
{
    OpCPX<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        for (size_t jj = 0; jj < 256; ++jj)
        {
            args.darg = jj;
            registers.xIndex = ii;
            op(args, registers, info, memory);

            EXPECT_EQ(ii == jj, registers.statusRegister[ZERO]);
            EXPECT_EQ(ii >= jj, registers.statusRegister[CARRY]);
            EXPECT_EQ(static_cast<int8_t>(ii - jj) < 0,
                      registers.statusRegister[SIGN]);
        }
    }
}

//===========================================================================//
TEST_F(Test6502Ops, AND)
{
    OpAND<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        for (size_t jj = 0; jj < 256; ++jj)
        {
            args.darg = jj;
            registers.accumulator = ii;
            op(args, registers, info, memory);
            EXPECT_EQ(ii & jj, registers.accumulator);
        }
    }
}

//===========================================================================//
TEST_F(Test6502Ops, ORA)
{
    OpORA<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        for (size_t jj = 0; jj < 256; ++jj)
        {
            args.darg = jj;
            registers.accumulator = ii;
            op(args, registers, info, memory);
            EXPECT_EQ(ii | jj, registers.accumulator);
        }
    }
}

//===========================================================================//
TEST_F(Test6502Ops, EOR)
{
    OpEOR<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        for (size_t jj = 0; jj < 256; ++jj)
        {
            args.darg = jj;
            registers.accumulator = ii;
            op(args, registers, info, memory);
            EXPECT_EQ(ii ^ jj, registers.accumulator);
        }
    }
}

//===========================================================================//
TEST_F(Test6502Ops, ADC)
{
    OpADC<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        for (size_t jj = 0; jj < 256; ++jj)
        {
            args.darg = jj;
            registers.accumulator = ii;
            registers.statusRegister[CARRY] = false;
            op(args, registers, info, memory);
            EXPECT_EQ(static_cast<uint8_t>(ii + jj), registers.accumulator);
        }
    }
}

//===========================================================================//
TEST_F(Test6502Ops, SBC)
{
    OpSBC<MockMode> op(0, 0, 0);

    for (size_t ii = 0; ii < 256; ++ii)
    {
        for (size_t jj = 0; jj < 256; ++jj)
        {
            args.darg = jj;
            registers.accumulator = ii;
            registers.statusRegister[CARRY] = true;
            op(args, registers, info, memory);
            EXPECT_EQ(static_cast<uint8_t>(ii - jj), registers.accumulator);
        }
    }
}
}
}
}

NYRA_TEST()
