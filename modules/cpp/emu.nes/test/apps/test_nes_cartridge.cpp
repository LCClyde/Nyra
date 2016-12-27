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
#include <nyra/emu/nes/Cartridge.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace emu
{
namespace nes
{
TEST(Cartridge, Read)
{
    Cartridge cart(core::path::join(core::DATA_PATH, "roms/nestest.nes"));
    const Header& header = cart.getHeader();
    EXPECT_EQ("NES", header.getNESIdentifier());
    EXPECT_EQ(static_cast<size_t>(1), header.getProgRomSize());
    EXPECT_EQ(static_cast<size_t>(1), header.getChrRomSize());
    EXPECT_EQ(static_cast<size_t>(0), header.getMapperNumber());
    EXPECT_FALSE(header.getIsFourScreenMode());
    EXPECT_FALSE(header.getHasTrainer());
    EXPECT_FALSE(header.getHasBatteryBack());
    EXPECT_EQ(HORIZONTAL, header.getMirroring());
    EXPECT_FALSE(header.getIsPlayChoice10());
    EXPECT_FALSE(header.getIsVsUnisystem());
    EXPECT_FALSE(header.getIsNes2_0());

    EXPECT_EQ(header.getProgRomSize(), cart.getProgROM().size());
    EXPECT_EQ(header.getChrRomSize() * 2, cart.getChrROM().size());
}
}
}
}

NYRA_TEST()
