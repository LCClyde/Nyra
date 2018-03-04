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
#include <nyra/emu/nes/Header.h>

namespace
{
nyra::emu::nes::Header makeHeader(
        uint8_t progROM,
        uint8_t chrROM,
        uint8_t mapper,
        bool fourScreenMode,
        bool trainer,
        bool batteryBack,
        nyra::emu::nes::Mirroring mirroring,
        bool playChoice10,
        bool vsUnisystem,
        bool nes2_0)
{
    // Other flags are not officially supported.
    // Set them to random values to ensure they don't ruin anything
    std::vector<uint8_t> extra(nyra::emu::nes::Header::getHeaderSize() - 7,
                               rand() % 255);
    std::vector<uint8_t> binary = nyra::emu::nes::Header::createBinary(
            "NES",
            progROM,
            chrROM,
            mapper,
            fourScreenMode,
            trainer,
            batteryBack,
            mirroring,
            playChoice10,
            vsUnisystem,
            nes2_0,
            extra);

    return nyra::emu::nes::Header(binary);
}
}

namespace nyra
{
namespace emu
{
namespace nes
{
TEST(Header, Invalid)
{
    // Invalid because there is not enough data.
    std::vector<uint8_t> binary;
    EXPECT_ANY_THROW(Header header(binary));

    // Invalid because it does not have the write ID.
    binary.resize(Header::getHeaderSize());
    EXPECT_ANY_THROW(Header header(binary));
}

TEST(Header, Values)
{
    // We could check all of these, but skip a few just to speed the
    // testing up. Skipping by a prime number to shuffle the bits more.
    for (size_t prog = 0; prog < 256; prog += 7)
    {
        for (size_t chr = 0; chr < 256; chr += 7)
        {
            for (size_t mapper = 0; mapper < 256; mapper += 7)
            {
                Header header = makeHeader(
                        prog, chr, mapper, false,
                        false, false, HORIZONTAL,
                        false, false, false);
                EXPECT_EQ(prog, header.getProgRomSize());
                EXPECT_EQ(chr, header.getChrRomSize());
                EXPECT_EQ(mapper, header.getMapperNumber());
                EXPECT_FALSE(header.getIsFourScreenMode());
                EXPECT_FALSE(header.getHasTrainer());
                EXPECT_FALSE(header.getHasBatteryBack());
                EXPECT_EQ(HORIZONTAL, header.getMirroring());
                EXPECT_FALSE(header.getIsPlayChoice10());
                EXPECT_FALSE(header.getIsVsUnisystem());
                EXPECT_FALSE(header.getIsNes2_0());
            }
        }
    }
}

TEST(Header, Flags)
{
    bool const bools[] = {false, true};
    for (bool fourScreen : bools)
    {
        for (bool trainer : bools)
        {
            for (bool battery : bools)
            {
                for (bool playChoice : bools)
                {
                    for (bool vs : bools)
                    {
                        for (bool nes2_0 : bools)
                        {
                            for (size_t ii = 0; ii < 2; ++ii)
                            {
                                Mirroring mirror = static_cast<Mirroring>(ii);
                                size_t size = 1;

                                Header header = makeHeader(
                                        size, size, size, fourScreen,
                                        trainer, battery, mirror,
                                        playChoice, vs, nes2_0);
                                EXPECT_EQ(size, header.getProgRomSize());
                                EXPECT_EQ(size, header.getChrRomSize());
                                EXPECT_EQ(size, header.getMapperNumber());
                                EXPECT_EQ(fourScreen, header.getIsFourScreenMode());
                                EXPECT_EQ(trainer, header.getHasTrainer());
                                EXPECT_EQ(battery, header.getHasBatteryBack());
                                EXPECT_EQ(mirror, header.getMirroring());
                                EXPECT_EQ(playChoice, header.getIsPlayChoice10());
                                EXPECT_EQ(vs, header.getIsVsUnisystem());
                                EXPECT_EQ(nes2_0, header.getIsNes2_0());
                            }
                        }
                    }
                }
            }
        }
    }
}

TEST(Header, Archive)
{
    Header header = makeHeader(
            2, 3, 10, false,
            false, true, VERTICAL,
            false, false, false);
    Header archived = test::archive(header);
    EXPECT_EQ(header, archived);
}

TEST(Header, Stdout)
{
    Header header = makeHeader(
            2, 3, 10, false,
            false, true, VERTICAL,
            false, false, false);
    const std::string expected(
            "NES Identifier:      NES\n"
            "Prog Size:           2\n"
            "Chr Rom Size:        3\n"
            "Mapper Number:       10\n"
            "Four Screen Mode:    No\n"
            "Trainer:             No\n"
            "Battery Back:        Yes\n"
            "Mirroring:           VERTICAL\n"
            "PlayChoice-10:       No\n"
            "VS System:           No\n"
            "NES 2.0:             No");
    EXPECT_EQ(expected, test::stdout(header));
}
}
}
}

NYRA_TEST()
