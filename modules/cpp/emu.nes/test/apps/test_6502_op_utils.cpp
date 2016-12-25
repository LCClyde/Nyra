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
#include <vector>
#include <nyra/test/Test.h>
#include <nyra/emu/nes/Op6502Utils.h>

namespace
{
static std::vector<uint8_t> globalValues;

static const std::vector<uint8_t>& getValues()
{
    if (globalValues.empty())
    {
        for (size_t ii = 0; ii < 256; ++ii)
        {
            globalValues.push_back(ii);
        }
    }
    return globalValues;
}
}

namespace nyra
{
namespace emu
{
namespace nes
{
TEST(OpUtils, ShiftRight)
{
    const std::vector<uint8_t>& values = getValues();
    std::bitset<FLAG_SIZE> statusRegister;

    // Test no rotate
    for (size_t ii = 0; ii < values.size(); ++ii)
    {
        const uint8_t value = shiftRight(values[ii], false, statusRegister);
        const uint8_t expected = (values[ii] >> 1);
        EXPECT_EQ(expected, value);

        // If the value was odd, there was a carry
        const bool carry = (values[ii] % 2) != 0;
        EXPECT_EQ(carry, statusRegister[CARRY]);
    }

    // Test rotate without carry flag
    for (size_t ii = 0; ii < values.size(); ++ii)
    {
        // If the carry is false than nothing will rotate
        statusRegister[CARRY] = false;
        const uint8_t value = shiftRight(values[ii], true, statusRegister);
        const uint8_t expected = values[ii] >> 1;

        EXPECT_EQ(expected, value);

        // If the value was odd, there was a carry
        const bool carry = (values[ii] % 2) != 0;
        EXPECT_EQ(carry, statusRegister[CARRY]);
    }

    // Test rotate with carry flag
    for (size_t ii = 0; ii < values.size(); ++ii)
    {
        // If the carry is false than nothing will rotate
        statusRegister[CARRY] = true;
        const uint8_t value = shiftRight(values[ii], true, statusRegister);
        const uint8_t expected = (values[ii] >> 1) + 128;

        EXPECT_EQ(expected, value);

        // If the value was odd, there was a carry
        const bool carry = (values[ii] % 2) != 0;
        EXPECT_EQ(carry, statusRegister[CARRY]);
    }
}

TEST(OpUtils, ShiftLeft)
{
    const std::vector<uint8_t>& values = getValues();
    std::bitset<FLAG_SIZE> statusRegister;

    // Test no rotate
    for (size_t ii = 0; ii < values.size(); ++ii)
    {
        const uint8_t value = shiftLeft(values[ii], false, statusRegister);
        const uint8_t expected = (values[ii] << 1);
        EXPECT_EQ(expected, value);

        // If the value was odd, there was a carry
        const bool carry = (values[ii] >= 128);
        EXPECT_EQ(carry, statusRegister[CARRY]);
    }

    // Test rotate without carry flag
    for (size_t ii = 0; ii < values.size(); ++ii)
    {
        // If the carry is false than nothing will rotate
        statusRegister[CARRY] = false;
        const uint8_t value = shiftLeft(values[ii], true, statusRegister);
        const uint8_t expected = (values[ii] << 1);

        EXPECT_EQ(expected, value);

        // If the value was odd, there was a carry
        const bool carry = (values[ii] >= 128);
        EXPECT_EQ(carry, statusRegister[CARRY]);
    }

    // Test rotate with carry flag
    for (size_t ii = 0; ii < values.size(); ++ii)
    {
        // If the carry is false than nothing will rotate
        statusRegister[CARRY] = true;
        const uint8_t value = shiftLeft(values[ii], true, statusRegister);
        const uint8_t expected = (values[ii] << 1) + 1;

        EXPECT_EQ(expected, value);

        // If the value was odd, there was a carry
        const bool carry = (values[ii] >= 128);
        EXPECT_EQ(carry, statusRegister[CARRY]);
    }
}

TEST(OpUtils, Compare)
{
    const std::vector<uint8_t>& values = getValues();
    const std::vector<uint8_t>& regs = getValues();
    std::bitset<FLAG_SIZE> statusRegister;

    for (uint8_t value : values)
    {
        for (uint8_t reg :  regs)
        {
            compare(value, reg, statusRegister);
            EXPECT_EQ(reg == value, statusRegister[ZERO]);
            EXPECT_EQ(reg >= value, statusRegister[CARRY]);
            EXPECT_EQ(static_cast<int8_t>(reg - value) < 0,
                      statusRegister[SIGN]);
        }
    }
}

TEST(OpUtils, SetRegister)
{
    const std::vector<uint8_t>& values = getValues();
    uint8_t reg;
    std::bitset<FLAG_SIZE> statusRegister;

    for (uint8_t value : values)
    {
        setRegister(value, reg, statusRegister);
        EXPECT_EQ(value == 0, statusRegister[ZERO]);
        EXPECT_EQ(static_cast<int8_t>(value) < 0, statusRegister[SIGN]);
        EXPECT_EQ(value, reg);
    }
}


TEST(OpUtils, Add)
{
    const std::vector<uint8_t>& values = getValues();
    CPURegisters registers;

    for (uint8_t value : values)
    {
        for (size_t ii = 0; ii < 256; ++ii)
        {
            // Add without carry
            registers.accumulator = ii;
            registers.statusRegister[CARRY] = false;
            add(value, registers);
            const uint8_t sum1 = ii + value;
            EXPECT_EQ(sum1, registers.accumulator);
            EXPECT_EQ(sum1 == 0, registers.statusRegister[ZERO]);
            EXPECT_EQ(ii + value > sum1, registers.statusRegister[CARRY]);
            EXPECT_EQ(static_cast<int8_t>(sum1) < 0,
                      registers.statusRegister[SIGN]);
            const bool oflow1 = ((ii ^ (ii + value)) &
                        (value ^ (ii + value)) & 0x80) != 0;
            EXPECT_EQ(oflow1, registers.statusRegister[OFLOW]);

            // Add with carry
            registers.accumulator = ii;
            registers.statusRegister[CARRY] = true;
            add(value, registers);
            const uint8_t sum2 = ii + value + 1;
            EXPECT_EQ(sum2, registers.accumulator);
            EXPECT_EQ(sum2 == 0, registers.statusRegister[ZERO]);
            EXPECT_EQ(ii + value + 1 > sum2, registers.statusRegister[CARRY]);
            EXPECT_EQ(static_cast<int8_t>(sum2) < 0,
                      registers.statusRegister[SIGN]);
            const bool oflow2 = ((ii ^ (ii + value + 1)) &
                        (value ^ (ii + value + 1)) & 0x80) != 0;
            EXPECT_EQ(oflow2, registers.statusRegister[OFLOW]);
        }
    }
}

TEST(OpUtils, Stack)
{
    const std::vector<uint8_t>& values = getValues();

    MemoryMap memory;
    memory.setMemoryBank(0, std::shared_ptr<emu::RAM<uint8_t> >(
            new emu::RAM<uint8_t>(0x200)));
    memory.lockLookUpTable();
    uint8_t stackPointer = 0xFF;

    for (size_t ii = 0; ii < values.size() - 1; ++ii)
    {
        EXPECT_EQ(0xFF - ii, stackPointer);
        pushStack(values[ii], memory, stackPointer);
        EXPECT_EQ(static_cast<uint8_t>(0xFF - ii - 1), stackPointer);
    }

    for (size_t ii = 0; ii < values.size() - 1; ++ii)
    {
        EXPECT_EQ(ii, stackPointer);
        const uint8_t value = popStack(memory, stackPointer);
        EXPECT_EQ(0xFE - ii, value);
        EXPECT_EQ(static_cast<uint8_t>(ii + 1), stackPointer);
    }
}
}
}
}

NYRA_TEST()
