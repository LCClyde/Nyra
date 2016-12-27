/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
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
#include <nyra/core/Path.h>
#include <nyra/core/File.h>

namespace nyra
{
namespace core
{
TEST(File, FileSize)
{
    const std::string pathname = nyra::core::path::join(
        nyra::core::DATA_PATH, "test/test_binary.bin");
    EXPECT_EQ(static_cast<size_t>(12), getFileSize(pathname));
}

TEST(File, Binary)
{
    const std::string pathname = nyra::core::path::join(
        nyra::core::DATA_PATH, "test/test_binary.bin");
    const std::vector<uint8_t> binary(readBinaryFile(pathname));
    EXPECT_EQ('h', binary[0]);
    EXPECT_EQ('e', binary[1]);
    EXPECT_EQ('l', binary[2]);
    EXPECT_EQ('l', binary[3]);
    EXPECT_EQ('o', binary[4]);
    EXPECT_EQ(' ', binary[5]);
    EXPECT_EQ('w', binary[6]);
    EXPECT_EQ('o', binary[7]);
    EXPECT_EQ('r', binary[8]);
    EXPECT_EQ('l', binary[9]);
    EXPECT_EQ('d', binary[10]);
    EXPECT_EQ('\n', binary[11]);

}
}
}

NYRA_TEST()
