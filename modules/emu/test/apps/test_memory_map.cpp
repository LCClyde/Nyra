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
#include <nyra/emu/MemoryMap.h>
#include <nyra/emu/RAM.h>

namespace nyra
{
namespace emu
{
TEST(MemoryMap, Values)
{
    const size_t NUM_BANKS = 11;
    const size_t BANK_SIZE = 17;
    MemoryMap<uint8_t> memMap;
    for (size_t ii = 0; ii < NUM_BANKS; ++ii)
    {
        std::shared_ptr<RAM<uint8_t> > bank(new RAM<uint8_t>(BANK_SIZE));
        memMap.setMemoryBank(ii * BANK_SIZE, bank);
    }
    memMap.lockLookUpTable();

    for (size_t ii = 0; ii < NUM_BANKS * BANK_SIZE; ++ii)
    {
        memMap.writeWord(ii, ii);
    }

    for (size_t ii = 0; ii < NUM_BANKS * BANK_SIZE; ++ii)
    {
        EXPECT_EQ(ii, memMap.readWord(ii));
    }

    // Test a few long values
    EXPECT_EQ(static_cast<uint16_t>(0x0201), memMap.readLong(1));
    EXPECT_EQ(static_cast<uint16_t>(0x0302), memMap.readLong(2));
    EXPECT_EQ(static_cast<uint16_t>(0x0908), memMap.readLong(8));
    EXPECT_EQ(static_cast<uint16_t>(0x0B0A), memMap.readLong(10));
    EXPECT_EQ(static_cast<uint16_t>(0x0C0B), memMap.readLong(11));
    EXPECT_EQ(static_cast<uint16_t>(0x0D0C), memMap.readLong(12));
    EXPECT_EQ(static_cast<uint16_t>(0x0E0D), memMap.readLong(13));
}
}
}

NYRA_TEST()
